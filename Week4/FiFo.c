#include <stdio.h>

int getAddr(int page_in);
int chkPmem(int page_in);       // result is yes: 1 no: 0
void handlePfault(int page_in); // update frames
int FIFO(int page_in);

#define F 3

int frames[F];         // take: #define F 3
int lastFIFOindex = 0; // keep track of last select
char pFault = 0;

int main()
{
    int pageInput[] = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2};
    printf("FiFo memory management\n");
    printf(" Frame:|");
    for (int i = 0; i < F; i++)
    {
        printf(" %d |", i);
    }
    printf(" PF?\n\n");

    for (int i = 0; i < sizeof(pageInput) / sizeof(pageInput[0]); i++)
    {
        FIFO(pageInput[i]);
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
int chkPmem(int page_in)
{
    for (int i = 0; i < F; i++)
    {
        if (frames[i] == page_in)
            return 1;
    }
    return 0;
}

void handlePfault(int page_in)
{
    frames[lastFIFOindex] = page_in;
}

int FIFO(int page_in)
{
    int addr = getAddr(page_in);

    if (addr != -1)
    {
        pFault = 0;
        return addr;
    }

    pFault = 1;
    addr = lastFIFOindex;
    frames[lastFIFOindex] = page_in;
    lastFIFOindex = (++lastFIFOindex) % F;

    return addr;
}