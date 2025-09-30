#include <stdio.h>

#include "../include/functions.h"
#include "../include/status_codes.h"

int main (int argc, char** argv)
{
    double nums[4];
    char flag;

    int rc = parse_input(argc, argv, nums, &flag);
    if (rc != OK)
    {
        print_messanges(rc);
        return 1;
    }

    if (flag == 'q')
    {
        rc = possible_solutions(nums[0], nums[1], nums[2], nums[3]);
    }
    else if (flag == 'm')
    {
        rc = is_multiple((int)nums[0], (int)nums[1]);
    }
    else if (flag == 't')
    {
        rc = is_triangular(nums[0], nums[1], nums[2], nums[3]);
    }

    if (rc != OK)
    {
        print_messanges(rc);
        return 1;
    }
    return 0;
}