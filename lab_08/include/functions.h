#pragma once
#include <stdio.h>

#define MAX_COUNT_INPUT 50

int parse_input(const int argc, const char** argv, int *base, int* nums);

int fromNto10(const char* num, const int n);
int from10toN(int num, const int n, char* output);

int max(const int* nums, const int size);

void print_errors(const int err);




