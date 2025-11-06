#include "../include/function.h"

int convert_base(unsigned number, int r, char* res)
{
    if (r < 1 || r > 5)
    {
        return -1;
    }

    char* p = res;
    if (number == 0)
    {
        *p = '0';
        *(p + 1) = '\0';
        return 0;
    }

    char all_digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";

    unsigned mask = ~(~0 << r);
    while (number > 0)
    {
        unsigned digit = number & mask;
        char symbol = all_digits[digit];

        *p = symbol;
        p++;

        number >>= r;
    }

    *p = '\0';

    char *left = res, *right = --p;
    while (left < right)
    {
        char temp = *left;
        *left = *right;
        *right = temp;

        left++;
        right--;
    }
    return 0;
}
