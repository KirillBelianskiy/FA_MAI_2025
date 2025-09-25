#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "../include/functions.h"
#include "../include/status_codes.h"

int main()
{
    int n;
    scanf("%d", &n);

    if (n <= 0 || n > 100000)
    {
        printf("Invalid input\n");
        return SIZE_NOT_FOUND;
    }

    d_array input;
    create_d_array(&input, 10);
    if (input.numbers == NULL)
    {
        printf("Error memory allocation\n");
        return ERROR_MEMORY_ALLOCATION;
    }

    unsigned x;
    for (int i = 0; i < n; i++)
    {
        scanf("%u", &x);
        if (x == 0)
        {
            printf("Zero is not a correct number\n");
            return INCORRECT_NUMBER;
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