#pragma once

int find_number_system(const char* num);
int to_dec(const char* num, const int base);

int read_file(FILE* file, char buffer[][20]);
int write_file(FILE* file, const char buffer[][20], const int* bases, const int* dec_numbers, const int size);