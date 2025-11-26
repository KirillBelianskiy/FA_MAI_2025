#include <stdlib.h>

#include "../include/calculating.h"
#include "../include/Stack.h"
#include "../include/Token.h"

int fastPow(int number, int n)
{
    int res = 1;
    while (n > 0)
    {
        if (n % 2)
        {
            res *= number;
            n--;
        }
        else
        {
            number *= number;
            n >>= 1;
        }
    }
    return res;
}

static int operation_priority(char operation)
{
    switch (operation)
    {
    case '=': return 2;
    case '+':
    case '-': return 3;
    case '*':
    case '/': return 4;
    case '^': return 5;
    case '~': return 6;
    default: return -1;
    }
}

static int operation(char operation, int left, int right)
{
    switch (operation)
    {
    case '+': return left + right;
    case '-': return left - right;
    case '*': return left * right;
    case '/':
        if (right == 0)
        {
            return 0;
        }
        return left / right;
    case '^': return fastPow(left, right);
    default: return 0;
    }
}

int to_postfix(Token* inp, Token* outp)
{
    Stack operatorStack;
    stack_init(&operatorStack);

    int outp_count = 0;
    int i = 0;

    while (inp[i].type != TOKEN_EOF)
    {
        switch (inp[i].type)
        {
        case TOKEN_NUMBER:
        case TOKEN_VARIABLE:
            outp[outp_count++] = inp[i++];
            break;

        case TOKEN_OPERATOR:
            {
                char currentOp = inp[i].value[0];
                while (!is_empty_stack(&operatorStack) &&
                    peek_stack(&operatorStack) != '(' &&
                    operation_priority(currentOp) <= operation_priority((char)peek_stack(&operatorStack)))
                {
                    char op = (char)pop_stack(&operatorStack);
                    outp[outp_count].type = TOKEN_OPERATOR;
                    outp[outp_count].value[0] = op;
                    outp[outp_count].value[1] = '\0';
                    outp_count++;
                }
                push_stack(&operatorStack, currentOp);
                i++;
            }
            break;

        case TOKEN_LPAREN:
            push_stack(&operatorStack, inp[i++].value[0]);
            break;

        case TOKEN_RPAREN:
            while (!is_empty_stack(&operatorStack) && peek_stack(&operatorStack) != '(')
            {
                char op = (char)pop_stack(&operatorStack);
                outp[outp_count].type = TOKEN_OPERATOR;
                outp[outp_count].value[0] = op;
                outp[outp_count].value[1] = '\0';
                outp_count++;
            }

            if (!is_empty_stack(&operatorStack))
            {
                pop_stack(&operatorStack);
            }
            i++;
            break;

        default:
            i++;
            break;
        }
    }

    while (!is_empty_stack(&operatorStack))
    {
        char op = (char)pop_stack(&operatorStack);
        if (op == '(')
        {
            continue;
        }
        outp[outp_count].type = TOKEN_OPERATOR;
        outp[outp_count].value[0] = op;
        outp[outp_count].value[1] = '\0';
        outp_count++;
    }

    outp[outp_count].type = TOKEN_EOF;
    stack_free(&operatorStack);

    return outp_count;
}

int calculating_expression(Token* postfix, int postfix_count, Variables* table)
{
    Stack valueStack;
    stack_init(&valueStack);

    int i = 0;
    while (i < postfix_count)
    {
        switch (postfix[i].type)
        {
        case TOKEN_NUMBER:
            push_stack(&valueStack, atoi(postfix[i].value));
            i++;
            break;

        case TOKEN_VARIABLE:
            {
                int varIdx = postfix[i].value[0] - 'A';
                int val = get_variable(table, varIdx);
                push_stack(&valueStack, val);
                i++;
            }
            break;

        case TOKEN_OPERATOR:
            {
                if (postfix[i].value[0] == '~')
                {
                    int val = pop_stack(&valueStack);
                    push_stack(&valueStack, -val);
                }
                else
                {
                    int right = pop_stack(&valueStack);
                    int left = pop_stack(&valueStack);
                    int res = operation(postfix[i].value[0], left, right);
                    push_stack(&valueStack, res);
                }
                i++;
            }
            break;

        default:
            i++;
            break;
        }
    }

    int result = pop_stack(&valueStack);
    stack_free(&valueStack);
    return result;
}
