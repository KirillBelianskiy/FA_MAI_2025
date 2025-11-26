#include "../include/Stack.h"

#include <stdlib.h>
#include <stdio.h>

void stack_init(Stack* stack)
{
    stack->capacity = 5;
    stack->arr = malloc(stack->capacity * sizeof(int));

    if (stack->arr == NULL)
    {
        stack->capacity = 0;
    }
    stack->height = 0;
}

int push_stack(Stack* stack, int value)
{
    if (stack->arr == NULL || stack->capacity == 0)
    {
        stack_init(stack);
        if (stack->arr == NULL)
        {
            return 1;
        }
    }

    if (stack->height >= stack->capacity)
    {
        size_t new_capacity = stack->capacity * 2;
        int* new_arr = realloc(stack->arr, new_capacity * sizeof(int));
        if (new_arr != NULL)
        {
            stack->arr = new_arr;
            stack->capacity = new_capacity;
        }
        else
        {
            return 1;
        }
    }
    stack->arr[stack->height] = value;
    stack->height++;
    return 0;
}

int pop_stack(Stack* stack)
{
    if (stack->arr == NULL || stack->height == 0)
    {
        return 0;
    }
    --stack->height;
    return stack->arr[stack->height];
}

int peek_stack(Stack* stack)
{
    if (stack->arr == NULL || stack->height == 0)
    {
        return 0;
    }
    return stack->arr[stack->height - 1];
}

int is_empty_stack(Stack* stack)
{
    return stack->height == 0;
}

int get_height_stack(Stack* stack)
{
    return stack->height;
}

void stack_free(Stack* stack)
{
    stack->height = 0;
    stack->capacity = 0;
    free(stack->arr);
}
