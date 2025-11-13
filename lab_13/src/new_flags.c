#include "../include/new_flags.h"
#include <string.h>
#include <limits.h>
#include <stdlib.h>

int to_rome(int num, char* res)
{
    if (num < 1 || num > 3999)
    {
        *res = '\0';
        return -1;
    }

    int arabic[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char* roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    char* start_res = res;

    for (int i = 0; i < 13; i++)
    {
        while (num >= arabic[i])
        {
            strcpy(start_res, roman[i]);
            start_res += strlen(roman[i]);
            num -= arabic[i];
        }
    }
    *start_res = '\0';
    return 0;
}

int to_zeckendorf(unsigned num, char* res)
{
    if (num == 0)
    {
        res[0] = '1';
        res[1] = '\0';
        return 0;
    }

    unsigned nums_of_fib[48] = {1, 2};
    int zeck_bits[48] = {0};
    int count = 2;

    while (nums_of_fib[count - 1] <= num && count < 48)
    {
        nums_of_fib[count] = nums_of_fib[count - 1] + nums_of_fib[count - 2];

        if (nums_of_fib[count] < nums_of_fib[count - 1])
        {
            break;
        }
        count++;
    }

    int i = count - 2;

    while (i >= 0)
    {
        if (num >= nums_of_fib[i])
        {
            zeck_bits[i] = 1;
            num -= nums_of_fib[i];
        }
        i--;
    }

    int j = 0;

    // for (j = 0; j <= count - 2; j++)
    // {
    //     if (zeck_bits[j])
    //     {
    //         res[j] = '1';
    //     }
    //     else
    //     {
    //         res[j] = '0';
    //     }

    while (j <= count -2)
    {
        if (zeck_bits[j])
        {
            res[j] = '1';
        }
        else
        {
            res[j] = '0';
        }
        j++;
    }


    res[j] = '1';
    res[j + 1] = '\0';
    return 0;
}

int from_K_to_N(const char* num, const int from_base, const int to_base, int is_upper, char* res)
{
    if (from_base < 2 || from_base > 36 || to_base < 2 || to_base > 36) return -1;

    if (from_base == to_base)
    {
        strcpy(res, num);
        return 0;
    }

    if (num == 0)
    {
        res[0] = '0';
        res[1] = '\0';
        return 0;
    }

    char* endptr;
    long val = strtol(num, &endptr, from_base);

    if (endptr == num || *endptr != '\0')
    {
        return -1;
    }

    if (val < INT_MIN || val > INT_MAX)
    {
        return -1;
    }

    char* digits = is_upper ? "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" : "0123456789abcdefghijklmnopqrstuvwxyz";

    char temp[65];
    int i = 0;

    int sign = val < 0;
    unsigned long abs_val = val < 0 ? -(unsigned long)val : (unsigned long)val;

    // do..while uses for the case with val == 0
    do
    {
        int remainder = abs_val % to_base;
        temp[i++] = digits[remainder];
        abs_val /= to_base;
    }
    while (abs_val > 0);

    int j = 0;
    if (sign)
    {
        res[j++] = '-';
    }

    while (i > 0)
    {
        res[j++] = temp[--i];
    }

    res[j] = '\0';
    return 0;
}

int memory_dump_helper(char* buffer, const void* data, size_t size)
{
    const unsigned char* bytes = (const unsigned char*)data;
    int written_count = 0;

    for (size_t i = 0; i < size; i++)
    {
        unsigned char current_byte = bytes[size - i - 1]; // little-endian

        for (int j = 7; j >= 0; j--)
        {
            buffer[written_count++] = ((current_byte >> j) & 1) ? '1' : '0';
        }

        if (i < size - 1)
        {
            buffer[written_count++] = ' ';
        }
    } // 1234 -≥ 4321

    buffer[written_count] = '\0';
    return written_count;
}