#ifndef SCHEDULERS_H
#define SCHEDULERS_H

struct process
{
    char name;
    int arrivalT;
    int serviceT;
    int waitTime;
    int completionT;
};

typedef struct process Process;

#endif
/*eof LL.h*/