#pragma once

typedef struct
{
    unsigned* numbers;
    int size;
    int capacity;
} d_array;

int create_d_array(d_array* d_array, int start_capacity);
int get_size(d_array* d_array);
int push_back(d_array* d_array, unsigned value);
int free_d_array(d_array* d_array);
unsigned max(d_array* d_array);

int _sieve(unsigned n, d_array* primes);
int sieve(d_array* input);