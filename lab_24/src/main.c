#include <stdio.h>
#include "../include/BinaryHeap.h"
int main()
{
    Heap h = create_heap(5);

    for (int i = 1; i < 15; ++i)
    {
        push_heap(&h, i);
        printf("%d\n", h.data[h.size - 1]);
    }

    return 0;
}