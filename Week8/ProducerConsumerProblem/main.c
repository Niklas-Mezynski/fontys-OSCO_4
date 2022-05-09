#include "ntk_5.4.h"
#include "OSCO.h"
#include <stdio.h>
#include <windows.h>

#define NUM_TOTAL_BUFFERS 5
#define DATA_LENGTH 10

char buffers[NUM_TOTAL_BUFFERS];            //The shared buffer
semaphore emptybuffers, fullbuffers;        //Semaphores used as counters
int writeI = 0;
int readI = 0;

unsigned __stdcall Writer(void* arg);
unsigned __stdcall Reader(void* arg);

int main(int argc, char** argv)
{
	printf("Main started. %d buffers and %d Data.\n", NUM_TOTAL_BUFFERS, DATA_LENGTH);
	startNTK();

	create_semaphore(&emptybuffers, NUM_TOTAL_BUFFERS, NUM_TOTAL_BUFFERS);
	create_semaphore(&fullbuffers, 0, NUM_TOTAL_BUFFERS);

	task* t = (task*)malloc(sizeof(task)); // dynamic task object
	int par = 1;
	//Start the reader and writer thread
	create_task(t, Writer, &par, sizeof(int), 0);
	create_task(t, Reader, &par, sizeof(int), 0);

	//Wait for all threads to finish
	Sleep(15000);
	printf("All done!\n");
}


/* Writer
* -------
* This is the routine forked by the writer thread. It will loop until
* all data (DATA_LENGTH) is read. It prepares (Generate a random character) the data to be written, waits for an
* empty buffer and signals that a full buffer is ready to be read.
*/
unsigned __stdcall Writer(void* arg)
{
	task* t = (task*)arg;
	char rand;
	while (true)
	{
		//Produce
		rand = rand_between('B', 'Y');

		wait_semaphore(&emptybuffers);
		//Append
		buffers[writeI] = rand;
		readI = writeI;
		writeI = (writeI + 1) % 5;
		printf("Writer wrote: %c\n", rand);
		Sleep(1000);

		signal_semaphore(&fullbuffers);
	}
}


/*Reader
* ------
* This is the routine forked by the reader thread. It will read until
* all data is read (DATA_LENGTH). It waits until a full buffer is available and then
* reads from it, signals that now an empty buffer is ready and goes off
* to process the data (printf()).
*/
unsigned __stdcall Reader(void* arg)
{
	task* t = (task*)arg;
	char taken;
	while (true)
	{
		//wait_semaphore(&emptybuffers);
		wait_semaphore(&fullbuffers);
		//Take
		taken = buffers[readI];
		buffers[readI] = 0;
		Sleep(1000);
		signal_semaphore(&emptybuffers);
		//Consume (print buffer)
		printf("        Reader read: %c\n", taken);
	}
}
