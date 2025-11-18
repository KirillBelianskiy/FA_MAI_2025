#include "../include/check_brackets.h"
#include "../include/Stack.h"

int check_brackets(const char* str)
{
    if (str == NULL) return 1;
    if (str[0] == '\0') return 0;

    Stack stack;
    stack_init(&stack);

    const char* p = str;
    while (*p != '\0')
    {
        switch (*p)
        {
        case '(':
        case '{':
        case '<':
        case '[':
            if (push(&stack, *p))
            {
                return 1;
            }
            break;
        case ')':
            if (is_empty(&stack) || peek(&stack) != '(')
            {
                stack_free(&stack);
                return 1;
            }
            pop(&stack);
            break;
        case '}':
            if (is_empty(&stack) || peek(&stack) != '{')
            {
                stack_free(&stack);
                return 1;
            }
            pop(&stack);
            break;
        case '>':
            if (is_empty(&stack) || peek(&stack) != '<')
            {
                stack_free(&stack);
                return 1;
            }
            pop(&stack);
            break;
        case ']':
            if (is_empty(&stack) || peek(&stack) != '[')
            {
                stack_free(&stack);
                return 1;
            }
            pop(&stack);
            break;
        }
        p++;
    }

    int res = is_empty(&stack) ? 0: 1;

    stack_free(&stack);

    return res;
}
