#include <stdio.h>

#include "../include/function.h"

int main()
{
    char res[65];
    unsigned num = 52;
    int vc = convert_base(num, 5, res);
    if (vc == -1)
    {
        return -1;
    }
    printf("%s", res);
    return 0;
}