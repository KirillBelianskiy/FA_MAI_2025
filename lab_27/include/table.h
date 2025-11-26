#pragma once

typedef struct
{
    int variables[26];
    int is_set[26];
} Variables;

void init_table(Variables* v);
int is_set(Variables* v, int index);
void set_variable(Variables* v, int index, int value);
int get_variable(Variables* v, int index);
void get_variables_string(Variables* v, char* buffer);
