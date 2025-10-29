#pragma once

int rome_arabic(char rome_dig);

int from_rome(const char* num);

unsigned from_zeckendorf(const char* num);

int parse_digit(char c, int base, int is_upper);