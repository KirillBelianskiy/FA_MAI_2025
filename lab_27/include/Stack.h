#pragma once

#include <stdio.h>

typedef struct
{
    int* arr;
    size_t height;
    size_t capacity;
} Stack;

void stack_init(Stack* stack);
int push_stack(Stack* stack, int value);
int pop_stack(Stack* stack);
int peek_stack(Stack* stack);
int is_empty_stack(Stack* stack);
int get_height_stack(Stack* stack);
void stack_free(Stack* stack);
