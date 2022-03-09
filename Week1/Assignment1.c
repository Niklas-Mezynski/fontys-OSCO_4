#include "stdio.h"
#include "multMethod.h"
#include "conio.h"

int main() {
    int a,b,r;
    printf("Enter a first value:\n");
    scanf("%d", &a);
    printf("Enter a second value:\n");
    scanf("%d", &b);
    r = mult(a,b);
    printf("%d times %d is equal to %d\n", a, b, r);
    printf("Press any key to exit\n");
    getch();
    return 0;
}