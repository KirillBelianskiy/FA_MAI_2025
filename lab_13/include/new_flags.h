#pragma once

#include <stdio.h>

int to_rome(int num, char* res);

int to_zeckendorf(unsigned num, char* res);

int from_K_to_N(const char* num, const int from_base, const int to_base, int is_upper, char* res);

int memory_dump_helper(char* buffer, const void* data, size_t size);
