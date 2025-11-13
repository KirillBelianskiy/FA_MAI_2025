#include "../include/overfprintf.h"
#include "../include/oversprintf.h"

int main()
{
    FILE* f = fopen("example.txt", "w");
    char num[] = "AFFC";
    // char str[50];
    overfprintf(f, "%to %d", num, 16, 10);
    // printf("%s", str);
    fclose(f);
    return 0;
}