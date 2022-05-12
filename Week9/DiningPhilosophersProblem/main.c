#include <stdio.h>
#include <windows.h>
#include "OSCO.h"

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
HANDLE forks[NUM_DINERS];
HANDLE numEating;
DWORD WINAPI Philosopher(LPVOID lpParam);
CRITICAL_SECTION criticalSection;


int main(int argc, char** argv)
{
	HANDLE philosopherThreads[NUM_DINERS];
	InitializeCriticalSection(&criticalSection);

	printf("Main started. %d philosophers that eat %d times.\n", NUM_DINERS, EAT_TIMES);

	//Create the forks
	numEating = CreateSemaphore(NULL, 0, NUM_DINERS, NULL);
	for (int i = 0; i < NUM_DINERS; i++) {
		forks[i] = CreateSemaphore(NULL, 0, 1, NULL);
	}

	//Create the philosophers and start them up
	int a[NUM_DINERS];
	for (int i = 0; i < NUM_DINERS; i++) {
		a[i] = i;
		philosopherThreads[i] = CreateThread(NULL, 0, Philosopher, &a[i], 0, NULL);

		if (philosopherThreads[i] == NULL)
		{
			printf("Error creating philosopher %d\n", i);
			ExitProcess(3);
		}
	}


	//Wait for all threads to finish
	WaitForMultipleObjects(NUM_DINERS, philosopherThreads, TRUE, 0xFFFFFFFF);

	CloseHandle(numEating);
	for (int i = 0; i < NUM_DINERS; i++) {
		CloseHandle(forks[i]);
	}
	printf("All done!\n");
}

DWORD WINAPI Philosopher(LPVOID lpParam) {
	int philosopherNo = *(int*)lpParam;
	int timesAte = 0;
	DWORD waitResultR;
	DWORD waitResultL;


	while (timesAte < EAT_TIMES) {

		WaitForSingleObject(numEating, 0L);
		EnterCriticalSection(&criticalSection);
		printf("Philosopher %d is thinking...\n", philosopherNo);
		LeaveCriticalSection(&criticalSection);
		Sleep(500);
		waitResultR = WaitForSingleObject(forks[(philosopherNo + 1) % 5], 0L);
		waitResultL = WaitForSingleObject(forks[philosopherNo], 0L);

		EnterCriticalSection(&criticalSection);
		printf("Philosopher %d: Starting to eat for %d. time\n", philosopherNo, timesAte + 1);
		LeaveCriticalSection(&criticalSection);
		Sleep(1000);
		EnterCriticalSection(&criticalSection);
		printf("Philosopher %d: Finished eating for %d. time\n", philosopherNo, timesAte + 1);
		LeaveCriticalSection(&criticalSection);
		timesAte++;

		//Done eating.. releasing semaphores
		ReleaseSemaphore(numEating, 1, NULL);
		ReleaseSemaphore(forks[philosopherNo], 1, NULL);
		ReleaseSemaphore(forks[(philosopherNo + 1) % 5], 1, NULL);
	}
}