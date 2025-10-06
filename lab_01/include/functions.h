#pragma once
#include "../include/status_codes.h"

typedef int (*callback_t)(int);

int find_natural_numbers(const int x);

int is_prime(const int x);

int to_hex(const int x);

int table_of_degrees(const int x);

int sum_to_num(const int x);

int factorial(const int x);

int GetOpts(const int argc, char * const *argv, kOpts *option, int *number);

void print_errors(const int error_code);
