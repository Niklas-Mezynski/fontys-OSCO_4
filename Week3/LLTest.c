#include <stdio.h>
#include <stdlib.h>
#include "LL.h"

int main(void)
{
    printf("Starting program\n");
    LL list1, list2;
    constructLL(&list1);
    constructLL(&list2);

    printf("First List print\n");
    printLL(&list1);
    addFrontLL(&list1, 3);
    addFrontLL(&list1, 5);
    addFrontLL(&list1, 2);
    addFrontLL(&list1, 18);
    addFrontLL(&list1, 12);

    printf("\nSecond List print\n");
    printLL(&list1);
    printf("number of elements: %d\n", numbInLL(&list1));
    addRearLL(&list1, 4);
    addRearLL(&list1, 10);

    printf("\nThird List print\n");
    printLL(&list1);
    printf("number of elements: %d\n", numbInLL(&list1));


    printf("Copying the list to another one...\n");
    copyLL(&list2, &list1);
    printLL(&list2);
    destructLL(&list1);
    destructLL(&list2);
    printf("Destructed lists\n");

    getchar();
    return 0;
}