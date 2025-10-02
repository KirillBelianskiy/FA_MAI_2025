#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/functions.h"
#include "../include/status_codes.h"

int find_natural_numbers(const int x)
{
    if (x <= 0)
    {
        return NEGATIVE_NUMBER;
    }
    if (x > 100)
    {
        return INCORRECT_NUMBER;
    }

    int count = 0;
    for (int i = x; i <= 100; i += x)
    {
        printf("%d ", i);
        ++count;
    }
    return OK;
}

int is_prime(const int x)
{
    if (x < 0)
    {
        return NEGATIVE_NUMBER;
    }

    if (x == 1 || x == 0)
    {
        return INCORRECT_ARGUMENTS;
    }

    int limit = (int)sqrt(x);
    for (int i = 2; i <= limit; i++)
    {
        if (x % i == 0)
        {
            printf("The number is compound");
            return OK;
        }
    }
    printf("The number is prime");
    return OK;
}

int to_hex(const int x)
{
    if (x == 0)
    {
        printf("0");
        return OK;
    }
    if (x < 0)
    {
        return NEGATIVE_NUMBER;
    }

    char digits[8];
    int len = 0;
    int value = x;

    while (value > 0 && len < (int)sizeof(digits))
    {
        int d = value % 16;
        digits[len++] = (char)((d < 10) ? ('0' + d) : ('A' + (d - 10)));
        value /= 16;
    }

    for (int i = len - 1; i >= 0; --i)
    {
        printf("%c ", digits[i]);
    }
    return OK;
}

int table_of_degrees(const int x)
{
    if (x < 1)
    {
        return NEGATIVE_NUMBER;
    }

    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= x + 1; j++)
        {
            if (j == 1)
                printf("%d ", i);
            else
            {
                int num = (int)pow(i, j);
                printf("%d ", num);
            }
        }
        printf("\n");
    }
    return OK;
}

int sum_to_num(const int x)
{
    if (x < 1)
    {
        return NEGATIVE_NUMBER;
    }

    int sum = 0;
    for (int i = 1; i <= x; i++)
    {
        sum += i;
    }
    printf("%d", sum);
    return OK;
}

static int _factorial(const int x)
{
    if (x == 0 || x == 1)  return 1;
    return x * _factorial(x - 1);
}

int factorial(const int x)
{
    if (x < 0)
    {
        return NEGATIVE_NUMBER;
    }

    if (x > 12)
    {
        return INCORRECT_NUMBER;
    }

    int a = _factorial(x);
    printf("%d", a);
    return OK;
}

int GetOpts(const int argc, char* const* argv, kOpts *option, int *number) {
    if (argc != 3) {
        return INCORRECT_COUNT_INPUT;
    }

    const char* opt_str = argv[1];
    if (opt_str[0] != '-' && opt_str[0] != '/') {
        return INCORRECT_ARGUMENTS;
    }

    if (strlen(opt_str) != 2) {
        return INCORRECT_ARGUMENTS;
    }

    char flag = opt_str[1];
    switch (flag) {
    case 'h': *option = OPT_H; break;
    case 'p': *option = OPT_P; break;
    case 's': *option = OPT_S; break;
    case 'e': *option = OPT_E; break;
    case 'a': *option = OPT_A; break;
    case 'f': *option = OPT_F; break;
    }

    char *endptr;
    long val;
    val = strtol(argv[2], &endptr, 10);

    if (endptr == argv[2] || *endptr != '\0')
    {
        return INCORRECT_ARGUMENTS;
    }

    if (val < INT_MIN || val > INT_MAX)
    {
        return INCORRECT_NUMBER;
    }

    *number = (int)val;
    return OK;
}

void print_errors(const int error_code)
{
    switch (error_code) {
    case OK: break;
    case NEGATIVE_NUMBER: printf("Negative number"); break;
    case INCORRECT_NUMBER: printf("Large number"); break;
    case INCORRECT_ARGUMENTS: printf("Incorrect number"); break;
    default: printf("Unknown status"); break;
    }
}