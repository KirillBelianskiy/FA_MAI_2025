#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/table.h"
#include "../include/parsing.h"

#define MAX_LINE_LEN 256

int main()
{
    FILE* inputFile = fopen("input.txt", "r");
    FILE* traceFile = fopen("trace.txt", "w");

    if (!inputFile)
    {
        printf("Error: Cannot open input.txt\n");
        return 1;
    }
    if (!traceFile)
    {
        printf("Error: Cannot open trace.txt\n");
        if (inputFile) fclose(inputFile);
        return 1;
    }

    Variables table;
    init_table(&table);

    char line[MAX_LINE_LEN];
    int line_num = 1;

    while (fgets(line, sizeof(line), inputFile))
    {
        line[strcspn(line, "\n")] = 0;

        if (strlen(line) == 0) continue;

        char op_name[64] = {0};

        int err = parsing_string(line, &table, op_name);

        if (!err && strlen(op_name) > 0)
        {
            char vars_str[256];
            get_variables_string(&table, vars_str);

            fprintf(traceFile, "[%d] %-20s | %-20s | %s\n",
                    line_num, line, vars_str, op_name);
        }

        line_num++;
    }

    fclose(inputFile);
    fclose(traceFile);

    printf("Done. Check trace.txt\n");

    return 0;
}
