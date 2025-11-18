#include "../include/Stack.h"

#include <stdlib.h>
#include <stdio.h>

void stack_init(Stack* stack)
{
    stack->capacity = 5;
    stack->arr = malloc(stack->capacity * sizeof(char));

    if (stack->arr == NULL)
    {
        printf("Memory allocation error");
        stack->capacity = 0;
    }
    stack->height = 0;
}

int push(Stack* stack, char value)
{
    if (stack->arr == NULL || stack->capacity == 0)
    {
        stack_init(stack);
        if (stack->arr == NULL)
        {
            printf("Memory allocation error");
            return 1;
        }
    }

    if (stack->height >= stack->capacity)
    {
        size_t new_capacity = stack->capacity * 2;
        char* new_arr = realloc(stack->arr, new_capacity * sizeof(char));
        if (new_arr != NULL)
        {
            stack->arr = new_arr;
            stack->capacity = new_capacity;
        }
        else
        {
            printf("Error: Failed to reallocate memory.\n");
            return 1;
        }
    }
    stack->arr[stack->height] = value;
    stack->height++;
    return 0;
}

char pop(Stack* stack)
{
    if (stack->arr == NULL || stack->height == 0)
    {
        printf("You can't pop from empty stack");
        return 0;
    }
    --stack->height;
    return stack->arr[stack->height];
}

char peek(Stack* stack)
{
    if (stack->arr == NULL || stack->height == 0)
    {
        printf("You can't peek from empty stack");
        return 0;
    }
    return stack->arr[stack->height - 1];
}

int is_empty(Stack* stack)
{
    return stack->height == 0;
}

int get_height(Stack* stack)
{
    return stack->height;
}

void stack_free(Stack* stack)
{
    stack->height = 0;
    stack->capacity = 0;
    free(stack->arr);
}
