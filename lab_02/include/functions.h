#pragma once

typedef struct
{
    unsigned* numbers;
    int size;
    int capacity;
} d_array;

int create_d_array(d_array* d_array, const int start_capacity);
int get_size(const d_array* d_array);
int push_back(d_array* d_array, const unsigned value);
int free_d_array(d_array* d_array);
unsigned max(const d_array* d_array);

int _sieve(const unsigned n, const d_array* primes);
int sieve(const d_array* input);