#include "ntk.h"
#include <stdio.h>
#include <windows.h>

 unsigned __stdcall taskCode(void* arg);
 unsigned __stdcall taskCodeUp(void* arg);
 unsigned __stdcall taskCodeDown(void* arg);

 int globalCount = 0;

//typedef unsigned (__stdcall *taskCode)(void*);


//EXPERIMENT 2 (5 threads)
 /*
int main()
{
    startNTK();
    task* threads[5];
    //Create 5 threads and store them in the array
    for (int i = 0; i < 5; i++)
    {
        threads[i] = (task*)malloc(sizeof(task));
        int par = i;

        printf("Created thread %d\n", i);
        create_task(threads[i], taskCode, &par, sizeof(int), 0);
        Sleep(1000);
    }

    for (int i = 4; i >= 0; i--)
    {
        delete_task(threads[i]);
        printf("Terminated thread %d\n", i);
        free(threads[i]);
        Sleep(1000);
    }
    printf("End of proram\n");
    // Wait for two seconds
    
}

unsigned __stdcall taskCode(void* arg)
{
    task* t = (task*)arg;
    int* a = (int*)getArgument_task(t);


    //printtaskcb(t);
    //printtib();

    while (!isTerminated_task(t))
    {
        printf("Thread %d is doing stuff\n", *a);
        Sleep(1000);
    }

    //printf("Task terminated\n");
}
*/


//EXPERIMENT 4 and 5
int main()
{
    startNTK();
    task* threads[5];

    int par = 123;

    task* taskInc = (task*)malloc(sizeof(task));
    task* taskDec = (task*)malloc(sizeof(task));
    
    create_task(taskInc, taskCodeUp, &par, sizeof(int), 0);
    create_task(taskDec, taskCodeDown, &par, sizeof(int), 0);

    setPriority_task(taskDec, high);

    Sleep(5000);

    delete_task(taskInc);
    free(taskInc);
    delete_task(taskDec);
    free(taskDec);
    printf("End status of global int:%d\n", globalCount);
    printf("End of proram\n");
    // Wait for two seconds

}


unsigned __stdcall taskCodeUp(void* arg)
{
    task* t = (task*)arg;
    int* a = (int*)getArgument_task(t);

    for (int i = 0; i < 1000; i++)
    {
        globalCount++;
        //if (i % 50 == 0) {
            //printf("Incrementing thread status for global int: %d\n", globalCount);
        //}
        printf("Incrementing thread status for global int: %d\n", globalCount);
    }
}

unsigned __stdcall taskCodeDown(void* arg)
{
    task* t = (task*)arg;
    int* a = (int*)getArgument_task(t);

    for (int i = 0; i < 1000; i++)
    {
        globalCount--;
        //if (i % 50 == 0) {
            //printf("Decrementing thread status for global int: %d\n", globalCount);
        //}
        printf("Decrementing thread status for global int: %d\n", globalCount);
    }
}

unsigned __stdcall taskCode(void* arg)
{
    task* t = (task*)arg;
    int* a = (int*)getArgument_task(t);

}