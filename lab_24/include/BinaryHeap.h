#pragma once
#include <stdio.h>

typedef struct
{
    int* data;
    size_t size;
    size_t capacity;
} Heap;

//parent = (i - 1) / 2
//left child = 2 * i + 1
//right child = 2 * i + 2

Heap create_heap(size_t initial_capacity);
void delete_heap(Heap* h);
int is_empty_heap(const Heap* h); // empty = 1, not = 0
size_t size_heap(const Heap* h);
int peek_heap(const Heap* h);
void push_heap(Heap* h, int value);
int pop_heap(Heap* h);
Heap build_heap(const int* array, size_t n);
int is_equal_heap(const Heap* h1, const Heap* h2); // equal = 1, not = 0
