#pragma once

#include <stdio.h>

typedef struct
{
    char* arr;
    size_t height;
    size_t capacity;
} Stack;

void stack_init(Stack* stack);
int push(Stack* stack, char value);
char pop(Stack* stack);
char peek(Stack* stack);
int is_empty(Stack* stack);
int get_height(Stack* stack);
void stack_free(Stack* stack);
