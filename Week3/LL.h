#ifndef LL_H
#define LL_H

struct Snode
{
    int value;
    struct Snode *next;
};

typedef struct Snode node;

struct list
{
    node *head;
    /*???*/;
};

typedef struct list LL;

void addFrontLL(LL *list, int number);
void constructLL(LL *list);
void printLL(LL *list);
void addRearLL(LL *list, int number);
int numbInLL(LL *list);
void deleteLL(LL *list, int number);
void copyLL(LL *list1, LL *list2);
void destructLL(LL *list);

#endif
/*eof LL.h*/