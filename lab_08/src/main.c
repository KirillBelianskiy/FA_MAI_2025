#include  <stdio.h>

#include "../include/functions.h"
#include "../include/status_codes.h"

int main(int argc, char **argv)
{
    int base;
    int nums[MAX_COUNT_INPUT];

    int rc = parse_input(argc, argv, &base, nums);
    if (rc != OK)
    {
        print_errors(rc);
        return 1;
    }

    int size = argc - 3;
    int max_num = max(nums, size);

    char res[5][32];
    int bases[5] = {base, 9, 18, 27, 36};

    for (int i = 0; i < 5; i++)
    {
        rc = from10toN(max_num, bases[i], res[i]);
        if (rc != OK)
        {
            print_errors(rc);
            return 1;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%d number system: %s\n", bases[i], res[i]);
    }

    return 0;
}