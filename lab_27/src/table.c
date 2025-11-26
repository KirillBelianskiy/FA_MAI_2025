#include "../include/table.h"
#include <stdio.h>
#include <string.h>

void init_table(Variables* v)
{
    for (int i = 0; i < 26; ++i) v->is_set[i] = 0;
}

int is_set(Variables* v, int index)
{
    if (index < 0 || index >= 26) return 0;
    return v->is_set[index] == 1;
}

void set_variable(Variables* v, int index, int value)
{
    if (index >= 0 && index < 26)
    {
        v->is_set[index] = 1;
        v->variables[index] = value;
    }
}

int get_variable(Variables* v, int index)
{
    if (index < 0 || index >= 26 || v->is_set[index] == 0) return 0;
    return v->variables[index];
}

void get_variables_string(Variables* v, char* buffer)
{
    buffer[0] = '\0';
    int first = 1;
    for (int i = 0; i < 26; i++)
    {
        if (v->is_set[i])
        {
            char temp[32];
            if (!first)
            {
                strcat(buffer, ", ");
            }
            sprintf(temp, "%c=%d", 'A' + i, v->variables[i]);
            strcat(buffer, temp);
            first = 0;
        }
    }
}
