#include "multMethod.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int a = 0,b = 0,r;

    if (argc >= 2) {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    }

    r = mult(a,b);
    printf("%d times %d is equal to %d\n", a, b, r);
    return 0;
}