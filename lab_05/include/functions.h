#pragma once
#include <stdio.h>
#include "../include/status_codes.h"

typedef int (*callback_t)(FILE *inp, FILE *outp);

int delete_digits(FILE *inp, FILE *outp);
int count_latin_letters(FILE *inp, FILE *outp);
int count_unusual_symb(FILE *inp, FILE *outp);
int change_to_ascii(FILE *inp, FILE *outp);

int GetOpts(int argc, char **argv, kOpts *option, FILE **input, FILE **output);
void print_errors(int error_code);
