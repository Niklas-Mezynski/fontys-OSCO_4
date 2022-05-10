//#include "ntk_5.4.h"
#include "OSCO.h"
#include <stdio.h>
#include <windows.h>

#define NUM_TOTAL_BUFFERS 5
#define DATA_LENGTH 10

char buffers[NUM_TOTAL_BUFFERS][DATA_LENGTH];	//The shared buffer
HANDLE emptybuffers, fullbuffers;				//Semaphores
int writeI = 0;
int readI = 0;
int readsWrites = 10;
CRITICAL_SECTION criticalSection;

DWORD WINAPI NewWriter(LPVOID lpParam);
DWORD WINAPI NewReader(LPVOID lpParam);

int main(int argc, char** argv)
{
	HANDLE  hThreadArray[2];
	printf("Main started. %d buffers and %d Data.\n", NUM_TOTAL_BUFFERS, DATA_LENGTH);

	InitializeCriticalSection(&criticalSection);

	emptybuffers =  CreateSemaphore(
		NULL,           // default security attributes
		NUM_TOTAL_BUFFERS,  // initial count
		NUM_TOTAL_BUFFERS,  // maximum count
		NULL);
	fullbuffers = CreateSemaphore(
		NULL,           // default security attributes
		0,  // initial count
		NUM_TOTAL_BUFFERS,  // maximum count
		NULL);

	//Start the reader and writer thread
	hThreadArray[0] = CreateThread(NULL, 0, NewWriter, NULL, 0, NULL);
	hThreadArray[1] = CreateThread(NULL, 0, NewReader, NULL, 0, NULL);

	//Wait for all threads to finish
	WaitForMultipleObjects(2, hThreadArray, TRUE, INFINITE);

	// Close all thread handles and free memory allocations.
	for (int i = 0; i < 2; i++)
	{
		CloseHandle(hThreadArray[i]);
	}
	printf("All done!\n");

	return 0;
}

/* Writer
* -------
* This is the routine forked by the writer thread. It will loop until
* all data (DATA_LENGTH) is read. It prepares (Generate a random character) the data to be written, waits for an
* empty buffer and signals that a full buffer is ready to be read.
*/
DWORD WINAPI NewWriter(LPVOID lpParam) {
	DWORD dwWaitResult;
	char rand;
	int writes = 0;

	while (TRUE)
	{
		if (writes >= readsWrites)
			return 0;

		// Try to enter the semaphore gate.
		dwWaitResult = WaitForSingleObject(
			emptybuffers,   // handle to semaphore
			0L);           // zero-second time-out interval

		if (dwWaitResult == WAIT_OBJECT_0)
		{
			EnterCriticalSection(&criticalSection);
			//Produce
			for (int i = 0; i < DATA_LENGTH; i++)
			{
				rand = rand_between('B', 'Y');
				buffers[writeI][i] = rand;
			}
			//Filled one buffer
			printf("Writer wrote to buffer[%d]: %s\n", writeI, buffers[writeI]);
			writeI++;
			writes++;

			// Release the semaphore when task is finished
			if (!ReleaseSemaphore(
				fullbuffers,  // handle to semaphore
				1,            // increase count by one
				NULL))       // not interested in previous count
			{
				printf("ReleaseSemaphore error: %d\n", GetLastError());
			}
			LeaveCriticalSection(&criticalSection);
			Sleep(1000);
		}
	}
}

/*Reader
* ------
* This is the routine forked by the reader thread. It will read until
* all data is read (DATA_LENGTH). It waits until a full buffer is available and then
* reads from it, signals that now an empty buffer is ready and goes off
* to process the data (printf()).
*/
DWORD WINAPI NewReader(LPVOID lpParam) {
	DWORD dwWaitResult;
	char taken;
	int reads = 0;

	while (TRUE)
	{
		if (reads >= readsWrites)
			return 0;

		// Try to enter the semaphore gate.
		dwWaitResult = WaitForSingleObject(
			fullbuffers,   // handle to semaphore
			0L);           // zero-second time-out interval

		if (dwWaitResult == WAIT_OBJECT_0)
		{
			//Take
			//Read one buffer
			printf("Reader read at buffer[%d]: %s\n", writeI - 1, buffers[writeI - 1]);
			//Clear it
			for (int i = 0; i < DATA_LENGTH; i++)
			{
				buffers[writeI][i] = 0;
			}
			writeI--;
			reads++;

			// Release the semaphore when task is finished
			if (!ReleaseSemaphore(
				emptybuffers,  // handle to semaphore
				1,            // increase count by one
				NULL))       // not interested in previous count
			{
				printf("ReleaseSemaphore error: %d\n", GetLastError());
			}
			LeaveCriticalSection(&criticalSection);
			Sleep(1000);
		}
	}
}
