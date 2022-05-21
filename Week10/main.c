#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "schedulers.h"
#include "LL.h"

#define MAX_CYCLES 20
#define PROCESSES 5

Process *processes[PROCESSES];
int currentTick = 0;

void fillProcessesArray();
void simulateFCFS();
void simulateRoundRobin();
void increaseWaitingTimeForQueue(LL *queue);
void putNewProcessesInQueue(LL *queue);

int main()
{
    fillProcessesArray();
    simulateFCFS();
}

void simulateRoundRobin()
{
}

void simulateFCFS()
{
    LL queue;
    constructLL(&queue);
    Process *currentP = 0;
    for (currentTick = 0; currentTick <= MAX_CYCLES; currentTick++)
    {
        usleep(420 * 1000);
        printf("ClockCycle %d: ", currentTick);
        // Increase waiting time for all processes in the queue (for measuring)
        increaseWaitingTimeForQueue(&queue);

        // Schedule the threads into the queue (when their arrival time is reached)
        putNewProcessesInQueue(&queue);

        // If there is a process running -> decrease remaining running time
        if (currentP != 0)
        {
            // Decrease the remaining service time for that process
            currentP->serviceT--;
            printf("Process %c is running.. remaining time %d\n", currentP->name, currentP->serviceT);
            // If the process is done, remove it and set the completion time (for measuring)
            if (currentP->serviceT <= 0)
            {
                currentP->completionT = currentTick;
                currentP = 0;
            }
            else
            {
                continue;
            }
        }

        // If queue is empty do nothing
        if (numbInLL(&queue) == 0)
        {
            continue;
        }
        currentP = deleteLL(&queue);
        printf("Process %c has been scheduled, runtime: %d\n", currentP->name, currentP->serviceT);
    }

    printf("\nResults\n");
    int waitT, waitTSum, turnArroundT = 0, turnArroundTSum = 0;
    //Print the results and calc the average waiting/turn around time
    for (int i = 0; i < PROCESSES; i++)
    {
        waitT = processes[i]->waitTime;
        turnArroundT = processes[i]->completionT - processes[i]->arrivalT;
        waitTSum += waitT;
        turnArroundTSum += turnArroundT;
        printf("Process %c Waiting time: %d, Turn around time: %d\n", processes[i]->name, waitT, turnArroundT);
    }
    printf("Average Waiting time: %f, Turn around time: %f\n", (double) waitTSum / PROCESSES, (double) turnArroundTSum / PROCESSES);
}

void increaseWaitingTimeForQueue(LL *queue)
{
    node *current = queue->head;
    while (current != NULL)
    {
        current->value->waitTime++;
        current = current->next;
    }
}

void putNewProcessesInQueue(LL *queue)
{
    // printf(" ---SNENS---\n");
    for (int i = 0; i < PROCESSES; i++)
    {
        // printf(" ---%d--- \n", i);
        if (processes[i]->arrivalT == currentTick)
        {
            addRearLL(queue, processes[i]);
        }
    }
}

void fillProcessesArray()
{
    Process *p1 = (Process *)malloc(sizeof(Process));
    p1->name = 'A';
    p1->arrivalT = 0;
    p1->serviceT = 3;
    p1->waitTime = 0;
    processes[0] = p1;

    Process *p2 = (Process *)malloc(sizeof(Process));
    p2->name = 'B';
    p2->arrivalT = 2;
    p2->serviceT = 6;
    p2->waitTime = 0;
    processes[1] = p2;

    Process *p3 = (Process *)malloc(sizeof(Process));
    p3->name = 'C';
    p3->arrivalT = 4;
    p3->serviceT = 4;
    p3->waitTime = 0;
    processes[2] = p3;

    Process *p4 = (Process *)malloc(sizeof(Process));
    p4->name = 'D';
    p4->arrivalT = 6;
    p4->serviceT = 5;
    p4->waitTime = 0;
    processes[3] = p4;

    Process *p5 = (Process *)malloc(sizeof(Process));
    p5->name = 'E';
    p5->arrivalT = 8;
    p5->serviceT = 2;
    p5->waitTime = 0;
    processes[4] = p5;
}