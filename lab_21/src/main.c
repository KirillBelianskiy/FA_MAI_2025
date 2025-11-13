#include <stdio.h>

#include "../include/function.h"

int main()
{
    int num = 3;

    for (int i = 1; i < 6; ++i)
    {
        char res[33];
        int ok = convert_base(num, i, res);

        if (ok == -1)
        {
            return -1;
        }

        printf("%s\n", res);
    }
    return 0;
}