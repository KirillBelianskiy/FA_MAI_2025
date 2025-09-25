#pragma ones
#include "../include/status_codes.h"

typedef int (*callback_t)(int);

int find_natural_numbers(int x);

int is_prime(int x);

int to_hex(int x);

int table_of_degrees(int x);

int sum_to_num(int x);

int factorial(int x);

int GetOpts(int argc, char **argv, kOpts *option, int *number);

void print_errors(int error_code);
