#pragma once
#include <stdio.h>

#define MAX_COUNT_INPUT 50

int parse_input(const int argc, const char** argv, int *base, int* nums);
int from10toN(int num, const int n, char* output, int sign);

int abs_max(const int* nums, const int size, int* sign);

void print_errors(const int err);




