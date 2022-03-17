#include "ntk_5.4.h"
#include <stdio.h>

// unsigned __stdcall taskCode(void* arg);

// typedef unsigned (__stdcall *taskCode)(void*);

unsigned __stdcall taskCode(void* arg) {
   task* t=(task*)arg;
   int* a=(int*)getArgument_task(t);
   printf("");
   while(!isTerminated_task(t)){
    //   ...
      //use a* ...
    //   ...
      //Do work for 5 seconds
      printf("I am doing something.\n");
    //   ....
   }
//    ...
}

int main() {
   task* t1=(task*)malloc(sizeof(task));
   int par = 1;
   startNTK();

   create_task(t1,taskCode,&par,sizeof(int),0);
   //Wait for two seconds
//    ......
   delete_task(t1);
   free(t1);
}

