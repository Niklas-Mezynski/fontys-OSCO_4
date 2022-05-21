#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
// #include "OSCO.h"

#define NUM_DINERS 5
#define EAT_TIMES 3

/* Our main creates a semaphore for every fork in an unlocked state. One philosopher
 *  can immediately grab boh forks and sets up the numEating semaphors to allow (N-1)
 *  philsophers to try to grab their forks and start eating.
 */
sem_t forks[NUM_DINERS];
sem_t numEating;
/*Philosophers Diner
 * ------------------
 * The classical philosophers diner problem. They need two forks to eat,
 * but they only have one per philosopher. So they need to share. Each
 * philosopher needs two forks to eat.
 */
void *Philosopher(void *lpParam);

int main(int argc, char **argv)
{
	pthread_t philosopherThreads[NUM_DINERS];
	// InitializeCriticalSection(&criticalSection);

	printf("Main started. %d philosophers that eat %d times.\n", NUM_DINERS, EAT_TIMES);

	// Create the forks
	sem_init(&numEating, 0, 2);
	for (int i = 0; i < NUM_DINERS; i++)
	{
		sem_init(&forks[i], 0, 1);
	}

	// Create the philosophers and start them up
	int a[NUM_DINERS];
	for (int i = 0; i < NUM_DINERS; i++)
	{
		a[i] = i;
		pthread_create(&philosopherThreads[i], NULL, Philosopher, &a[i]);
	}

	// Wait for all threads to finish
	for (int i = 0; i < NUM_DINERS; i++)
	{
		pthread_join(philosopherThreads[i], NULL);
	}

	// Remove the semaphores
	sem_destroy(&numEating);
	for (int i = 0; i < NUM_DINERS; i++)
	{
		sem_destroy(&forks[i]);
	}
	printf("All done!\n");
}

void *Philosopher(void *lpParam)
{
	int philosopherNo = *(int *)lpParam;
	int timesAte = 0;

	while (timesAte < EAT_TIMES)
	{
		printf("Philosopher %d is thinking...\n", philosopherNo + 1);
		usleep(200 * 1000);
		// Wait for the forks to become available
		sem_wait(&forks[(philosopherNo + 1) % 5]);
		sem_wait(&forks[philosopherNo]);

		// Do the eating part
		printf("Philosopher %d: STARTING to eat for %d. time\n", philosopherNo + 1, timesAte + 1);
		// usleep(500 * 1000);
		sleep(1);
		printf("Philosopher %d: finished eating for %d. time\n", philosopherNo + 1, timesAte + 1);
		timesAte++;

		// Done eating.. releasing semaphores
		sem_post(&forks[(philosopherNo + 1) % 5]);
		sem_post(&forks[philosopherNo]);
	}
	printf("Philosopher %d is done. He ate %d times\n", philosopherNo + 1, timesAte + 1);
}