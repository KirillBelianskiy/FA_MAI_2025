#include <stdio.h>
#include "../include/functions.h"
#include "../include/status_codes.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Incorrect count of arguments\n");
        return INCORRECT_COUNT_INPUT;
    }

    FILE *inp = fopen(argv[1], "r");
    if (inp == NULL)
    {
        printf("File is not open\n");
        return ERROR_OPEN_FILE;
    }

    FILE *outp = fopen(argv[2], "w");
    if (outp == NULL)
    {
        printf("File is not open\n");
        return ERROR_OPEN_FILE;
    }

    char strs[1024][20];
    int count_nums = read_file(inp, strs);
    if (count_nums < 0)
    {
        printf("Incorrect count of numbers\n");
        return INCORRECT_COUNT_INPUT;
    }

    int bases[1024];
    int dec_nums[1024];
    for (int i = 0; i < count_nums; ++i)
    {
        int numbers = find_number_system(strs[i]);
        bases[i] = numbers;
        int dec_number = to_dec(strs[i], numbers);
        dec_nums[i] = dec_number;
    }

    if (write_file(outp, strs, bases, dec_nums, count_nums) != OK)
    {
        printf("Error writing to file\n");
    }

    fclose(inp);
    fclose(outp);
    return 0;
}