#include "../include/Vector.h"
#include <stdlib.h>

Vector create_vector(size_t initial_capacity, CopyVoidPtr CopyF, DeleteVoidPtr DF, CompareVoidPtr CompF)
{
    Vector v;
    v.arr = malloc(sizeof(V_T) * initial_capacity);

    if (v.arr == NULL)
    {
        v.capacity = 0;
    }
    else
    {
        v.capacity = initial_capacity;
    }

    v.size = 0;
    v.CopyFunc = CopyF;
    v.DeleteFunc = DF;
    v.CompareFunc = CompF;
    return v;
}

void erase_vector(Vector* v)
{
    if (v->arr == NULL)
    {
        v->size = 0;
        v->capacity = 0;
        return;
    }

    if (v->DeleteFunc != NULL)
    {
        for (int i = 0; i < v->size; ++i)
        {
            v->DeleteFunc(v->arr[i]);
        }
    }
    v->size = 0;
}

int is_equal_vector(const Vector* v1, const Vector* v2)
{
    if (v1->size != v2->size)
    {
        return 0;
    }

    if (v1->CompareFunc == NULL)
    {
        return 0;
    }

    for (int i = 0; i < v1->size; ++i)
    {
        if (v1->CompareFunc(v1->arr[i], v2->arr[i]) != 0)
        {
            return 0;
        }
    }
    return 1;
}

void push_back_vector(Vector* v, V_T value)
{
    if (v->size == v->capacity)
    {
        size_t new_capacity = (v->capacity == 0) ? 1 : v->capacity * 2;

        V_T* temp = realloc(v->arr, new_capacity * sizeof(V_T));

        if (temp == NULL)
        {
            return;
        }
        v->arr = temp;
        v->capacity = new_capacity;
    }

    V_T new_elem = v->CopyFunc(value);
    v->arr[v->size] = new_elem;
    v->size++;
}

void copy_vector(Vector* dest, Vector* src)
{
    if (src == NULL || src->arr == NULL)
    {
        return;
    }

    erase_vector(dest);
    for (int i = 0; i < src->size; ++i)
    {
        push_back_vector(dest, src->arr[i]);
    }
}

Vector* copy_vector_new(const Vector* src)
{
    Vector* v = malloc(sizeof(Vector));
    if (v == NULL) return NULL;

    *v = create_vector(src->capacity, src->CopyFunc, src->DeleteFunc, src->CompareFunc);

    if (v->arr == NULL && src->capacity > 0)
    {
        free(v);
        return NULL;
    }

    for (int i = 0; i < src->size; ++i)
    {
        push_back_vector(v, src->arr[i]);
    }
    return v;
}

void delete_at_vector(Vector* v, size_t index)
{
    if (index >= v->size)
    {
        return;
    }
    if (v == NULL || v->arr == NULL)
    {
        return;
    }

    if (v->DeleteFunc != NULL)
    {
        v->DeleteFunc(v->arr[index]);
    }

    for (int i = index; i < v->size - 1; i++)
    {
        v->arr[i] = v->arr[i + 1];
    }
    v->size--;
}

V_T get_at_vector(Vector* v, size_t index)
{
    if (index >= v->size)
    {
        return NULL;
    }
    return v->arr[index];
}

void delete_vector(Vector* v)
{
    if (v == NULL || v->arr == NULL)
    {
        return;
    }

    if (v->DeleteFunc != NULL)
    {
        for (int i = 0; i < v->size; ++i)
        {
            v->DeleteFunc(v->arr[i]);
        }
    }

    free(v->arr);
    v->arr = NULL;
    v->capacity = 0;
    v->size = 0;
}
