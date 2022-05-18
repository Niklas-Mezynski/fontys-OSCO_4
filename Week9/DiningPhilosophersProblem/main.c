#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
// #include "OSCO.h"

/*Philosophers Diner
* ------------------
* The classical philosophers diner problem. They need two forks to eat,
* but they only have one per philosopher. So they need to share. Each
* philosopher needs two forks to eat.
*/

#define NUM_DINERS 5
#define EAT_TIMES 3

/* Our main creates a semaphore for every fork in an unlocked state. One philosopher
*  can immediately grab boh forks and sets up the numEating semaphors to allow (N-1)
*  philsophers to try to grab their forks and start eating.
*/
sem_t forks[NUM_DINERS];
sem_t numEating;
void* Philosopher(void* lpParam);
// CRITICAL_SECTION criticalSection;


int main(int argc, char** argv)
{
	pthread_t philosopherThreads[NUM_DINERS];
	// InitializeCriticalSection(&criticalSection);

	printf("Main started. %d philosophers that eat %d times.\n", NUM_DINERS, EAT_TIMES);

	//Create the forks
	sem_init(&numEating, 0, 2);
	for (int i = 0; i < NUM_DINERS; i++) {
		sem_init(&forks[i], 0, 1);
	}

	//Create the philosophers and start them up
	int a[NUM_DINERS];
	for (int i = 0; i < NUM_DINERS; i++) {
		a[i] = i;
		pthread_create(&philosopherThreads[i], NULL, Philosopher, &a[i]);
		// philosopherThreads[i] = CreateThread(NULL, 0, Philosopher, &a[i], 0, NULL);

		// if (philosopherThreads[i] == NULL)
		// {
		// 	printf("Error creating philosopher %d\n", i);
		// 	ExitProcess(3);
		// }
	}


	//Wait for all threads to finish
	for (int i = 0; i < NUM_DINERS; i++) 
	{
		pthread_join(philosopherThreads[i], NULL);
	}

	sem_destroy(&numEating);
	for (int i = 0; i < NUM_DINERS; i++) {
		sem_destroy(&forks[i]);
	}
	printf("All done!\n");
}

void* Philosopher(void* lpParam) {
	int philosopherNo = *(int*)lpParam;
	int timesAte = 0;

	// WaitForSingleObject(numEating, 0L);
	// EnterCriticalSection(&criticalSection);
	printf("Philosopher %d is thinking...\n", philosopherNo);
	// LeaveCriticalSection(&criticalSection);
	// Sleep(rand_between(250, 1000));
	sleep(1);
	while (timesAte < EAT_TIMES) {
		// waitResultR = WaitForSingleObject(forks[(philosopherNo + 1) % 5], 0L);
		// waitResultL = WaitForSingleObject(forks[philosopherNo], 0L);
		sem_wait(&forks[(philosopherNo + 1) % 5]);
		sem_wait(&forks[philosopherNo]);

		// EnterCriticalSection(&criticalSection);
		printf("Philosopher %d: STARTING to eat for %d. time\n", philosopherNo, timesAte + 1);
		// LeaveCriticalSection(&criticalSection);
		sleep(1);
		// EnterCriticalSection(&criticalSection);
		printf("Philosopher %d: finished eating for %d. time\n", philosopherNo, timesAte + 1);
		// LeaveCriticalSection(&criticalSection);
		timesAte++;

		//Done eating.. releasing semaphores
		// ReleaseSemaphore(numEating, 1, NULL);
		// ReleaseSemaphore(forks[philosopherNo], 1, NULL);
		// ReleaseSemaphore(forks[(philosopherNo + 1) % 5], 1, NULL);
		sem_post(&forks[(philosopherNo + 1) % 5]);
		sem_post(&forks[philosopherNo]);
	}
}