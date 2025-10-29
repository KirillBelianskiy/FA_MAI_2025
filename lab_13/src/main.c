#include "../include/overfprintf.h"
#include "../include/oversprintf.h"

int main()
{

    char num[] = "AFFC";
    char str[50];
    oversprintf(str, "%to", num, 16);
    printf("%s", str);
    return 0;
}