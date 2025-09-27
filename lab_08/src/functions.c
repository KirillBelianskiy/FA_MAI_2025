#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "../include/functions.h"
#include "../include/status_codes.h"

int max(const int* nums, const int size)
{
    if (nums == NULL || size == 0) return INCORRECT_ARGUMENTS;

    int max = nums[0];
    for (int i = 0; i < size; i++)
    {
        max = nums[i] > max ? nums[i] : max;
    }
    return max;
}

int parse_input(const int argc, const char** argv, int *base, int* nums)
{
    if (strcmp(argv[argc-1], "Stop") != 0)
    {
        return INCORRECT_ARGUMENTS;
    }

    char* endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0')
    {
        return INCORRECT_ARGUMENTS;
    }

    if (val < INT_MIN || val > INT_MAX)
    {
        return LARGE_NUMBER;
    }

    *base = (int)val;

    if (argc - 3 > MAX_COUNT_INPUT)
    {
        return INCORRECT_COUNT_INPUT;
    }

    for (int i = 2; i < argc - 1; i++)
    {
        char *endptr;
        long val = strtol(argv[i], &endptr, *base);
        if (endptr == argv[i] || *endptr != '\0')
        {
            return INCORRECT_ARGUMENTS;
        }

        if (val < INT_MIN || val > INT_MAX)
        {
            return LARGE_NUMBER;
        }
        if (argc - 2 < MAX_COUNT_INPUT)
        {
            nums[i-2] = (int)val;
        }
    }
    return OK;
}

int from10toN(int num, const int n, char* output)
{
    if (n < 2 || n > 36) return INCORRECT_BASE;

    if (num == 0)
    {
        output[0] = '0';
        output[1] = '\0';
        return OK;
    }

    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    char temp[33];
    int i = 0;

    while (num > 0) {
        int remainder = num % n;
        temp[i++] = digits[remainder];
        num /= n;
    }

    int j = 0;
    while (i > 0)
    {
        output[j++] = temp[--i];
    }

    output[j] = '\0';

    return OK;
}

void print_errors(const int err)
{
    switch (err)
    {
        case OK: break;
        case INCORRECT_ARGUMENTS: printf("Incorrect arguments"); break;
        case INCORRECT_BASE: printf("Incorrect base"); break;
        case LARGE_NUMBER: printf("Large number"); break;
        case INCORRECT_COUNT_INPUT: printf("Incorrect count of arguments"); break;
        case INCORRECT_NUMBER: printf("Incorrect number"); break;
        default: printf("Unknown status"); break;
    }
}
