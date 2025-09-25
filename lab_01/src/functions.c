#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "../include/functions.h"
#include "../include/status_codes.h"

int find_natural_numbers(int x)
{
    if (x <= 0)
    {
        return NEGATIVE_NUMBER;
    }
    if (x > 100)
    {
        return LARGE_NUMBER;
    }

    int count = 0;
    for (int i = x; i <= 100; i += x)
    {
        printf("%d ", i);
        ++count;
    }
    return OK;
}

int is_prime(int x)
{
    if (x < 0)
    {
        return NEGATIVE_NUMBER;
    }

    if (x == 1 || x == 0)
    {
        return INCORRECT_ARGUMENT;
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

int to_hex(int x)
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

    while (x > 0 && len < (int)sizeof(digits))
    {
        int d = x % 16;
        digits[len++] = (char)((d < 10) ? ('0' + d) : ('A' + (d - 10)));
        x /= 16;
    }

    for (int i = len - 1; i >= 0; --i)
    {
        printf("%c ", digits[i]);
    }
    return OK;
}

int table_of_degrees(int x)
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

int sum_to_num(int x)
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

static int _factorial(int x)
{
    if (x == 0 || x == 1)  return 1;
    return x * _factorial(x - 1);
}

int factorial(int x)
{
    if (x < 0)
    {
        return NEGATIVE_NUMBER;
    }

    if (x > 12)
    {
        return LARGE_NUMBER;
    }

    int a = _factorial(x);
    printf("%d", a);
    return OK;
}

int GetOpts(int argc, char** argv, kOpts *option, int *number) {
    if (argc != 3) {
        return INCORRECT_COUNT_INPUT;
    }

    char* opt_str = argv[1];
    if (opt_str[0] != '-' && opt_str[0] != '/') {
        return INCORRECT_ARGUMENT;
    }

    if (strlen(opt_str) != 2) {
        return INCORRECT_ARGUMENT;
    }

    char flag = opt_str[1];
    switch (flag) {
    case 'h': *option = OPT_H; break;
    case 'p': *option = OPT_P; break;
    case 's': *option = OPT_S; break;
    case 'e': *option = OPT_E; break;
    case 'a': *option = OPT_A; break;
    case 'f': *option = OPT_F; break;
    default: return UNKNOW_FLAG;
    }

    *number = atoi(argv[2]);
    return OK;
}

void print_errors(int error_code)
{
    switch (error_code) {
    case OK:
        break;
    case NEGATIVE_NUMBER:
        printf("Negative number");
        break;
    case LARGE_NUMBER:
        printf("Large number");
        break;
    case INCORRECT_ARGUMENT:
        printf("Incorrect number");
        break;
    default:
        printf("Unknown status");
        break;
    }
}