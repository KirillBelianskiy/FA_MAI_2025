#pragma once

int parse_input(const int argc, const char** argv, double* nums, char* f);

int find_solutions(const double eps, const double a, const double b, const double c, double* sol, int* count);

int possible_solutions(const double eps, const double a, const double b, const double c);

int is_multiple(const int a, const int b);

int is_triangular(const double eps, const double a, const double b, const double c);

void print_messanges(const int err);