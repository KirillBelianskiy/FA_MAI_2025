#include <stdio.h>

#include "../include/oversscanf.h"
#include "../include/overfscanf.h"

int main()
{
    char s[] = "1000010000010011 MMXIV FA5 4";
    int num1, num2, num3, num4;
    oversscanf(s, "%Zr %Ro %CV %d", &num1, &num2, &num3, 16, &num4);
    printf("%d\n%d\n%d\n%d", num1, num2, num3, num4);
    return 0;
}
