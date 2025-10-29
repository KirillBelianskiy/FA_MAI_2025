#include "../include/new_flags.h"

#include <ctype.h>
#include <string.h>

int rome_arabic(char rome_dig)
{
    switch (rome_dig)
    {
    case 'I': return 1;
    case 'V': return 5;
    case 'X': return 10;
    case 'L': return 50;
    case 'C': return 100;
    case 'D': return 500;
    case 'M': return 1000;
    default: return -1;
    }
}

int from_rome(const char* num)
{
    if (num == NULL || *num == '\0')
    {
        return -1;
    }

    int length = strlen(num);
    int res = 0;

    for (int i = 0; i < length; i++)
    {
        int current = rome_arabic(num[i]);

        if (current == -1)
        {
            return -1;
        }

        if (i + 1 < length)
        {
            int next = rome_arabic(num[i + 1]);
            if (next > current)
            {
                res -= current;
            }
            else
            {
                res += current;
            }
        }
        else
        {
            res += current;
        }
    }

    return res;
}

unsigned from_zeckendorf(const char* s)
{
    if (s == NULL || *s == '\0')
    {
        return -1;
    }

    int len = strlen(s);

    for (int i = 0; i < len; i++)
    {
        if (s[i] != '0' && s[i] != '1')
        {
            return -1;
        }

        if (i < len - 1 && s[i] == '1' && s[i + 1] == '1')
        {
            if (i + 2 != len)
            {
                return -1;
            }
        }
    }

    if (len < 2 || s[len - 2] != '1' || s[len - 1] != '1')
    {
        return -1;
    }

    unsigned int result = 0;
    unsigned int fib_prev = 1;
    unsigned int fib_curr = 2;

    for (int i = 0; i < len - 1; i++)
    {
        if (s[i] == '1')
        {
            result += fib_prev;
        }

        unsigned int temp = fib_prev;
        fib_prev = fib_curr;
        fib_curr = temp + fib_curr;
    }

    return result;
}

int parse_digit(char c, int base, int is_upper)
{
    int digit_val = -1;

    if (isdigit(c))
    {
        digit_val = c - '0';
    }
    else if (is_upper && isupper(c))
    {
        digit_val = c - 'A' + 10;
    }
    else if (!is_upper && islower(c))
    {
        digit_val = c - 'a' + 10;
    }

    if (digit_val == -1 || digit_val >= base)
    {
        return -1;
    }

    return digit_val;
}