#pragma once

int find_number_system(const char* num);
int to_dec(const char* num, int base);

int read_file(FILE* file, char buffer[][20]);
int write_file(FILE* file, char buffer[][20], int* bases, int* dec_numbers, int size);