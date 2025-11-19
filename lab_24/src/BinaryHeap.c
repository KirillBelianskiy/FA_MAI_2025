#include "../include/BinaryHeap.h"

#include <stdlib.h>

//helper
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//helper
void sift_up(Heap* h)
{
    size_t k = h->size - 1;
    while (k > 0)
    {
        size_t parent_ind = (k - 1) / 2;
        if (h->data[parent_ind] <= h->data[k]) break;

        swap(&h->data[parent_ind], &h->data[k]);
        k = parent_ind;
    }
}

//helper
void sift_down(Heap* h)
{
    size_t k = 0;
    size_t smallest_child_ind;

    while (2 * k + 1 < h->size)
    {
        size_t left_child_ind = 2 * k + 1;
        size_t right_child_ind = 2 * k + 2;

        if (right_child_ind < h->size && h->data[right_child_ind] < h->data[left_child_ind])
        {
            smallest_child_ind = right_child_ind;
        }
        else
        {
            smallest_child_ind = left_child_ind;
        }
        if (h->data[k] <= h->data[smallest_child_ind])
        {
            return;
        }
        swap(&h->data[k], &h->data[smallest_child_ind]);
        k = smallest_child_ind;
    }
}

Heap create_heap(size_t initial_capacity)
{
    Heap h;
    h.data = malloc(initial_capacity * sizeof(int));
    if (h.data == NULL)
    {
        h.capacity = 0;
    }
    else
    {
        h.capacity = initial_capacity;
    }
    h.size = 0;
    return h;
}

void delete_heap(Heap* h)
{
    if (h->data != NULL) free(h->data);
    h->capacity = 0;
    h->size = 0;
}

int is_empty_heap(const Heap* h)
{
    return h->size == 0;
}

size_t size_heap(const Heap* h)
{
    return h->size;
}

int peek_heap(const Heap* h)
{
    return h->data[0];
}

void push_heap(Heap* h, int value)
{
    if (h->size == h->capacity)
    {
        size_t new_capacity = (h->capacity * 2 == 0) ? 1 : h->capacity * 2;
        int* new_arr = realloc(h->data, new_capacity * sizeof(int));
        if (new_arr == NULL) return;
        h->data = new_arr;
        h->capacity = new_capacity;
    }
    h->data[h->size] = value;
    h->size++;
    sift_up(h);
}

int pop_heap(Heap* h)
{
    if (h->size == 0) return -1;

    int min_val = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    sift_down(h);
    return min_val;
}

Heap build_heap(const int* array, size_t n)
{
    Heap h = create_heap(n);
    for (size_t i = 0; i < n; i++)
    {
        push_heap(&h, array[i]);
    }
    return h;
}

int is_equal_heap(const Heap* h1, const Heap* h2) // equal = 1, not = 0
{
    if (h1->size != h2->size) return 0;
    for (size_t i = 0; i < h1->size; i++)
    {
        if (h1->data[i] != h2->data[i]) return 0;
    }
    return 1;
}
