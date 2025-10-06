#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "../include/functions.h"
#include "../include/status_codes.h"

int abs_max(const int* nums, const int size, int* sign)
{
    if (nums == NULL || size == 0) return INCORRECT_ARGUMENTS;

    int max = INT_MIN;
    for (int i = 0; i < size; i++)
    {
        if (max < abs(nums[i]))
        {
            max = abs(nums[i]);
            if (nums[i] < 0)
            {
                *sign = 1;
            }
            else
            {
                *sign = 0;
            }
        }
    }
    return max;
}

int parse_input(const int argc, const char** argv, int *base, int* nums)
{
    if (strcmp(argv[argc-1], "Stop") != 0)
    {
        return INCORRECT_ARGUMENTS;
    }

    if (argc < 4)
    {
        return INCORRECT_COUNT_INPUT;
    }

    char* endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0')
    {
        return INCORRECT_ARGUMENTS;
    }

    if (val < INT_MIN || val > INT_MAX)
    {
        return INCORRECT_NUMBER;
    }

    if (val < 2 || val > 36)
    {
        return INCORRECT_BASE;
    }

    *base = (int)val;

    if (argc - 3 < 1 || argc - 3 > MAX_COUNT_INPUT)
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
            return INCORRECT_NUMBER;
        }
        nums[i-2] = (int)val;
    }
    return OK;
}

int from10toN(int num, const int n, char* output, int sign)
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
    if (sign)
    {
        output[j++] = '-';
    }
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
        case INCORRECT_ARGUMENTS: printf("Incorrect arguments\n"); break;
        case INCORRECT_BASE: printf("Incorrect base (must be 2-36)\n"); break;
        case INCORRECT_NUMBER: printf("Incorrect number (out of INT range or buffer size)\n"); break;
        case INCORRECT_COUNT_INPUT: printf("Incorrect count of arguments\n"); break;
        default: printf("Unknown status\n"); break;
    }
}
