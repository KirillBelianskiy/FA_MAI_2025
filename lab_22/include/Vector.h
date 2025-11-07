#pragma once

#include <stdio.h>

#define V_T char*

typedef V_T (*CopyVoidPtr) (V_T);
typedef void (*DeleteVoidPtr) (V_T);
typedef int (*CompareVoidPtr) (V_T, V_T);

typedef struct
{
    V_T* arr;
    size_t size;
    size_t capacity;
    CopyVoidPtr CopyFunc;
    DeleteVoidPtr DeleteFunc;
    CompareVoidPtr CompareFunc;

} Vector;

Vector create_vector(size_t initial_capacity, CopyVoidPtr CopyF, DeleteVoidPtr DF, CompareVoidPtr CompF);
void erase_vector(Vector* v);
int is_equal_vector(const Vector* v1, const Vector* v2);
void copy_vector(Vector* dest, Vector* src);
Vector* copy_vector_new(const Vector *src);
void push_back_vector(Vector* v, V_T value);
void delete_at_vector(Vector* v, size_t index);
V_T get_at_vector(Vector* v, size_t index);
void delete_vector(Vector* v);
