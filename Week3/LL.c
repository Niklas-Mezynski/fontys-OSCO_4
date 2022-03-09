#include <stdio.h>
#include <stdlib.h>
#include "LL.h"

void constructLL(LL *list)
{
    // node *firstNode;
    node *head;
    head = (node *)malloc(sizeof(node));
    head = NULL;
    list->head = head;
}

void printLL(LL *list)
{
    node *current = list->head;
    int i = 0;
    while (current != NULL)
    {
        i++;
        printf("%d. Element in the list: %d\n", i, current->value);
        current = current->next;
    }
}

void addFrontLL(LL *list, int number)
{
    node *newNode;
    newNode = (node *)malloc(sizeof(node));

    newNode->value = number;
    newNode->next = list->head;
    list->head = newNode;
}

void addRearLL(LL *list, int number)
{
    node *tail = list->head;
    node *current = list->head;
    if (current == NULL)
    {
        addFrontLL(list, number);
        return;
    }
    while (current->next != NULL)
    {
        current = current->next;
    }
    tail = current;

    node *newNode;
    newNode = (node *)malloc(sizeof(node));

    newNode->value = number;
    newNode->next = tail->next;
    tail->next = newNode;
}

int numbInLL(LL *list)
{
    node *current = list->head;
    int i = 0;
    while (current != NULL)
    {
        i++;
        current = current->next;
    }
    return i;
}

void copyLL(LL *list1, LL *list2)
{
    constructLL(list1);
    node *currentL2 = list2->head;
    while (currentL2 != NULL)
    {
        addRearLL(list1, currentL2->value);
        currentL2 = currentL2->next;
    }
}

void destructLL(LL *list)
{
    node *toClear;
    node *current = list->head;
    while (current->next != NULL)
    {
        toClear = current;
        current = current->next;
        free(toClear);
    }
    free(current);
}

// Deletes the front element
void deleteLL(LL *list)
{
    if (list->head->next != NULL)
    {
        node* toRemove = list->head;
        list->head = toRemove->next;
        free(toRemove);
    }
}