#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/functions.h"
#include "../include/status_codes.h"

unsigned upper_bound(unsigned n) {
    if (n < 1) return 0;
    if (n < 6) return 20;
    double ln_n = log(n);
    double ln_ln_n = log(ln_n);
    return (unsigned)ceil((double)n * (ln_n + ln_ln_n) * 1.2);
}

int create_d_array(d_array* d_array, int start_capacity)
{
    if (d_array == NULL || start_capacity <= 0) return ERROR_NOT_FOUND;

    unsigned* arr = (unsigned *)calloc(start_capacity, sizeof(unsigned));
    if (arr == NULL) return ERROR_MEMORY_ALLOCATION;

    d_array->numbers = arr;
    d_array->size = 0;
    d_array->capacity = start_capacity;
    return OK;
}

int get_size(d_array* d_array)
{
    if (d_array == NULL) return SIZE_NOT_FOUND;
    return d_array->size;
}

int push_back(d_array* d_array, unsigned value)
{
    if (d_array == NULL) return ERROR_NOT_FOUND;

    if (d_array->size >= d_array->capacity)
    {
        int new_capacity = d_array->capacity * 2;
        unsigned* new_arr = (unsigned *)realloc(d_array->numbers, new_capacity * sizeof(unsigned));
        if (new_arr == NULL) return ERROR_MEMORY_ALLOCATION;

        d_array->numbers = new_arr;
        d_array->capacity = new_capacity;
    }

    d_array->numbers[d_array->size] = value;
    d_array->size++;
    return OK;
}

unsigned max(d_array* d_array)
{
    if (d_array == NULL || d_array->size == 0) return 0;

    unsigned max_val = d_array->numbers[0];
    for (int i = 1; i < d_array->size; ++i)
    {
        if (d_array->numbers[i] > max_val) {
            max_val = d_array->numbers[i];
        }
    }
    return max_val;
}

int free_d_array(d_array* d_array)
{
    if (d_array == NULL) return ERROR_NOT_FOUND;

    free(d_array->numbers);
    d_array->numbers = NULL;
    d_array->capacity = 0;
    d_array->size = 0;
    return OK;
}

int _sieve(unsigned n, d_array* primes)
{
    if (primes == NULL || n < 2) return ERROR_NOT_FOUND;

    int* is_composite = (int*)calloc(n + 1, sizeof(int));
    if (is_composite == NULL) return ERROR_MEMORY_ALLOCATION;

    unsigned sqrt_n = (unsigned)sqrt((double)n);
    for (unsigned i = 2; i <= sqrt_n; ++i)
    {
        if (!is_composite[i])
        {
            for (unsigned j = i * i; j <= n; j += i)
            {
                is_composite[j] = 1;
            }
        }
    }

    for (unsigned i = 2; i <= n; ++i)
    {
        if (!is_composite[i])
        {
            if (push_back(primes, i) != OK) {
                free(is_composite);
                return ERROR_MEMORY_ALLOCATION;
            }
        }
    }

    free(is_composite);
    return OK;
}

int sieve(d_array* input)
{
    if (input == NULL || input->size == 0) return ERROR_NOT_FOUND;

    unsigned max_k = max(input);
    if (max_k < 1) {
        printf("No valid ordinals found.\n");
        return OK;
    }

    d_array primes;
    if (create_d_array(&primes, 10) != OK) {
        return ERROR_MEMORY_ALLOCATION;
    }

    unsigned bound = upper_bound(max_k);
    int status = _sieve(bound, &primes);

    while (status == OK && (unsigned)primes.size < max_k) {
        bound *= 2;
        free_d_array(&primes);
        if (create_d_array(&primes, 10) != OK) {
            return ERROR_MEMORY_ALLOCATION;
        }
        status = _sieve(bound, &primes);
    }

    if (status != OK || (unsigned)primes.size < max_k) {
        free_d_array(&primes);
        return ERROR_MEMORY_ALLOCATION;
    }

    for (int i = 0; i < input->size; ++i) {
        unsigned k = input->numbers[i];
        if (k == 0 || k > (unsigned)primes.size) {
            printf("Invalid ordinal: %u\n", k);
        } else {
            printf("%u ", primes.numbers[k - 1]);
        }
    }
    printf("\n");

    free_d_array(&primes);
    return OK;
}