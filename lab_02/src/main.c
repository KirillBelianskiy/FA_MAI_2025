#include <stdio.h>

#include "../include/functions.h"
#include "../include/status_codes.h"

int main()
{
    int n;
    if (scanf("%d", &n) == 0)
    {
        printf("Error reading include\n");
        return INCORRECT_ARGUMENTS;
    }

    if (n <= 0 || n > 100000)
    {
        printf("Invalid input\n");
        return SIZE_NOT_FOUND;
    }

    d_array input;
    if (create_d_array(&input, 10))
    {
        printf("Error memory allocation\n");
        return ERROR_MEMORY_ALLOCATION;
    }

    int x;
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &x) != 1)
        {
            printf("Invalid include\n");
            return ERROR_NOT_FOUND;
        }
        if (x <= 0 || x > 100000)
        {
            printf("This is an incorrect number\n");
            return INCORRECT_ARGUMENTS;
        }

        if (push_back(&input, x) != OK)
        {
            printf("Error memory allocation\n");
            return ERROR_MEMORY_ALLOCATION;
        }
    }

    switch (sieve(&input))
    {
        case OK: break;
        case ERROR_NOT_FOUND:
            printf("The array has no numbers\n");
            break;
        case ERROR_MEMORY_ALLOCATION:
            printf("d_array memory allocation failed\n");
            break;
    }

    free_d_array(&input);
    return 0;
}