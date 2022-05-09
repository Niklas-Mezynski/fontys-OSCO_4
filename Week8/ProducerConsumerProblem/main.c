//#include "ntk_5.4.h"
#include "OSCO.h"
#include <stdio.h>
#include <windows.h>

#define NUM_TOTAL_BUFFERS 5
#define DATA_LENGTH 10

char buffers[NUM_TOTAL_BUFFERS];            //The shared buffer
HANDLE emptybuffers, fullbuffers;			//Semaphores
int writeI = 0;
int readI = 0;
int readsWrites = 10;

DWORD WINAPI NewWriter(LPVOID lpParam);
DWORD WINAPI NewReader(LPVOID lpParam);

int main(int argc, char** argv)
{
	HANDLE  hThreadArray[2];
	printf("Main started. %d buffers and %d Data.\n", NUM_TOTAL_BUFFERS, DATA_LENGTH);

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
//unsigned __stdcall Writer(void* arg)
//{
//	task* t = (task*)arg;
//	char rand;
//	while (true)
//	{
//		//Produce
//		rand = rand_between('B', 'Y');
//
//		wait_semaphore(&emptybuffers);
//		//Append
//		buffers[writeI] = rand;
//		readI = writeI;
//		writeI = (writeI + 1) % 5;
//		printf("Writer wrote: %c\n", rand);
//		Sleep(1000);
//
//		signal_semaphore(&fullbuffers);
//	}
//}

DWORD WINAPI NewWriter(LPVOID lpParam) {
	DWORD dwWaitResult;
	BOOL bContinue = TRUE;
	char rand;
	int writes = 0;

	while (bContinue)
	{
		if (writes >= readsWrites)
			return 0;

		// Try to enter the semaphore gate.
		dwWaitResult = WaitForSingleObject(
			emptybuffers,   // handle to semaphore
			0L);           // zero-second time-out interval

		if (dwWaitResult == WAIT_OBJECT_0)
		{
			//Produce

			//Append
			/*buffers[writeI] = rand;
			readI = writeI;
			writeI = (writeI + 1) % 5;*/
			
			printf("Writer writing...:");
			for (int i = 0; i < NUM_TOTAL_BUFFERS; i++)
			{
				rand = rand_between('B', 'Y');
				buffers[i] = rand;
				printf(" %c", rand);
				Sleep(1000 / NUM_DISCHARGE_POLICIES);
			}
			printf("\n");
			writes++;

			// Release the semaphore when task is finished
			if (!ReleaseSemaphore(
				emptybuffers,  // handle to semaphore
				1,            // increase count by one
				NULL))       // not interested in previous count
			{
				printf("ReleaseSemaphore error: %d\n", GetLastError());
			}
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
//unsigned __stdcall Reader(void* arg)
//{
//	task* t = (task*)arg;
//	char taken;
//	while (true)
//	{
//		//wait_semaphore(&emptybuffers);
//		wait_semaphore(&fullbuffers);
//		//Take
//		taken = buffers[readI];
//		buffers[readI] = 0;
//		Sleep(1000);
//		signal_semaphore(&emptybuffers);
//		//Consume (print buffer)
//		printf("        Reader read: %c\n", taken);
//	}
//}

DWORD WINAPI NewReader(LPVOID lpParam) {
	DWORD dwWaitResult;
	BOOL bContinue = TRUE;
	char taken;
	int reads = 0;

	while (bContinue)
	{
		if (reads >= readsWrites)
			return 0;

		// Try to enter the semaphore gate.
		dwWaitResult = WaitForSingleObject(
			emptybuffers,   // handle to semaphore
			0L);           // zero-second time-out interval

		if (dwWaitResult == WAIT_OBJECT_0)
		{
			//Take
			//taken = buffers[readI];
			//buffers[readI] = 0;
			//reads++;
			//Sleep(1000);
			////Consume (print buffer)
			//printf("        Reader read: %c\n", taken);

			printf("Reader reading...:");
			for (int i = 0; i < NUM_TOTAL_BUFFERS; i++)
			{
				printf(" %c", buffers[i]);
				buffers[i] = 0;
				Sleep(1000 / NUM_DISCHARGE_POLICIES);
			}
			printf("\n");
			reads++;

			// Release the semaphore when task is finished
			if (!ReleaseSemaphore(
				emptybuffers,  // handle to semaphore
				1,            // increase count by one
				NULL))       // not interested in previous count
			{
				printf("ReleaseSemaphore error: %d\n", GetLastError());
			}
		}
	}
}
