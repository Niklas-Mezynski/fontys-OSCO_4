#include "ntk_5.4.h"
#include <stdio.h>
#include <windows.h>

// unsigned __stdcall taskCode(void* arg);

// typedef unsigned (__stdcall *taskCode)(void*);

unsigned __stdcall taskCode(void *arg)
{
   task *t = (task *)arg;
   int *a = (int *)getArgument_task(t);
   printf("Task created\n");

   int i = 0;
   while (!isTerminated_task(t))
   {
      printf("Param a = %d\n", *a);
      // Do work for 5 seconds
      printf("I am doing something. Second: %d\n", i);
      Sleep(1000);
      i++;
      if (i == 5)
         terminate_task(t);
   }

   printf("Task terminated\n");
}

int main()
{
   task *t1 = (task *)malloc(sizeof(task));
   int par = 123;
   startNTK();

   create_task(t1, taskCode, &par, sizeof(int), 0);
   // Wait for two seconds
   Sleep(2000);
   delete_task(t1);
   free(t1);
}
