#include <stdio.h>

#include "../include/function.h"

int main()
{
    char inp_file_name[52] = "inp.txt";
    char out_file_name[52] = "outp.txt";

    // if (scanf("%s %s", inp_file_name, out_file_name) < 2)
    // {
    //     return -1;
    // }

    FILE* inp_file = fopen(inp_file_name, "r");
    FILE* out_file = fopen(out_file_name, "w");

    if (inp_file == NULL || out_file == NULL)
    {
        return -1;
    }

    int vc = formatting(inp_file, out_file);

    if (vc)
    {
        return vc;
    }
    fclose(inp_file);
    fclose(out_file);
    return 0;
}