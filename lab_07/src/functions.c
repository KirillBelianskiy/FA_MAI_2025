#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/status_codes.h"

#define BUFFER_SIZE 1024
#define STR_SIZE 20

int find_number_system(const char* num)
{
    char base = '0';
    for (int i = 0; i < strlen(num); i++)
    {
        if (tolower(num[i]) >= 'a' && tolower(num[i]) <= 'z')
        {
            base = tolower(num[i]) > base ? tolower(num[i]) : base;
        }
        else if (num[i] >= '0' && num[i] <= '9')
        {
            base = num[i] > base ? num[i] : base;
        }
    }
    if (base >= 'a' && base <= 'z')
    {
        return base - 'a' + 11;
    }
    return base - '0' + 1;
}

int to_dec(const char* num, const int base)
{
    int res = 0;
    int sign = 1;
    int i = 0;
    if (num[0] == '-')
    {
        sign = -1;
        i++;
    }
    for (; num[i] != '\0'; i++)
    {
        char ch = num[i];
        int digit;

        if (isdigit(ch))
        {
            digit = ch - '0';
        }
        else if (isalpha(ch))
        {
            digit = tolower(ch) - 'a' + 10;
        }

        res = res * base + digit;
    }
    return res * sign;
}

int read_file(FILE* file, char buffer[][20])
{
    int i = 0, j = 0, reading = 0, insignificant_zeros = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF && i < BUFFER_SIZE)
    {
        if (isalnum(ch))
        {
            if (ch == '0' && !reading && j == 0)
            {
                continue;
            }
            if (j < STR_SIZE - 1)
            {
                buffer[i][j] = ch;
                j++;
                reading = 1;
                insignificant_zeros = 0;
            }
            else
            {
                return INCORRECT_COUNT_INPUT;
            }
        }
        else if (reading)
        {
            buffer[i][j] = '\0';
            i++;
            j = 0;
            reading = 0;
        }
    }
    if (reading)
    {
        buffer[i][j] = '\0';
        i++;
    }
    return i;
}

int write_file(FILE* file, const char buffer[][20], const int* bases, const int* dec_numbers, const int size)
{
    if (size <= 0) return INCORRECT_ARGUMENT;
    for (int i = 0; i < size; i++)
    {
       fprintf(file, "%s %d %d\n", buffer[i], bases[i], dec_numbers[i]);
    }
    return OK;
}