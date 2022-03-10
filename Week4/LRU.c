#include <stdio.h>

void updateAges(int page_in); // update the ages array,
                              // add into getAddr()
int LRU(int page_in);             // result is frame index
int getAddr(int page_in);

#define F 3

int frames[F];         // take: #define F 3
int ages[F];  // keep track of age per frame
int lastFIFOindex = 0; // keep track of last select
char pFault = 0;

int main()
{
    int pageInput[] = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2};
    printf("LRU memory management\n");
    printf(" Frame:|");
    for (int i = 0; i < F; i++)
    {
        printf(" %d |", i);
    }
    printf(" PF?\n\n");

    for (int i = 0; i < sizeof(pageInput) / sizeof(pageInput[0]); i++)
    {
        LRU(pageInput[i]);
        printf("| P: %d |", pageInput[i]);
        for (int j = 0; j < F; j++)
        {
            printf(" %d |", frames[j]);
        }
        if (pFault)
        {
            printf(" F\n");
        }
        else
        {
            printf("  \n");
        }
    }
}

int getAddr(int page_in)
{
    for (int i = 0; i < F; i++)
    {
        if (frames[i] == page_in)
            return i;
    }
    return -1;
}

void updateAges(int page_in)
{
    for (int i = 0; i < F; i++)
    {
        if (frames[i] == page_in)
        {
            ages[i] = 0;
            continue;
        }
        ages[i] = ages[i] + 1;
    }
}

int LRU(int page_in)
{
    int addr = getAddr(page_in);

    if (addr != -1)
    {
        pFault = 0;
        updateAges(page_in);
        return addr;
    }
    pFault = 1;
    int indexOldest = 0;
    for (int i = 1; i < F; i++)
    {
        if (ages[i] > ages[indexOldest])
        {
            indexOldest = i;
        }
    }
    frames[indexOldest] = page_in;
    updateAges(page_in);
    return indexOldest; 
}
