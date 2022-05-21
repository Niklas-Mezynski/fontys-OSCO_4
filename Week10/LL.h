#ifndef LL_H
#define LL_H

#include "schedulers.h"

struct Snode
{
    Process *value;
    struct Snode *next;
};

typedef struct Snode node;

struct list
{
    node *head;
};

typedef struct list LL;

void addFrontLL(LL *list, Process *value);
void constructLL(LL *list);
void printLL(LL *list);
void addRearLL(LL *list, Process *value);
int numbInLL(LL *list);

// Deletes the front element
Process *deleteLL(LL *list);
void copyLL(LL *list1, LL *list2);
void destructLL(LL *list);
#endif
/*eof LL.h*/