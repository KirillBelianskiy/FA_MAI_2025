#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/parsing.h"
#include "../include/table.h"
#include "../include/Token.h"
#include "../include/calculating.h"

#define MAX_SIZE_VALUE 11
#define MAX_SIZE_TOKENS 100

int is_alpha_char(char c) { return c >= 'A' && c <= 'Z'; }
int is_operator_char(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '^'; }
int is_print_cmd(char* p) { return strncmp(p, "print", 5) == 0; }

int push_token(Token* token, TokenType type, char* value, int* tokens_count)
{
    if (*tokens_count >= MAX_SIZE_TOKENS)
    {
        printf("[ERROR] overflow of the token array\n");
        return 1;
    }
    set_token(token, type, value);
    ++(*tokens_count);
    return 0;
}

int tokenize(char* inp, Token* tokens, int* tokens_count)
{
    char* p = inp;
    while (*p != '\0')
    {
        if (*p == ' ' || *p == '\n' || *p == '\r')
        {
            p++;
            continue;
        }

        if (isdigit(*p))
        {
            char number[MAX_SIZE_VALUE];
            int j = 0;
            while (isdigit(*p) && j < MAX_SIZE_VALUE - 1)
            {
                number[j++] = *p++;
            }
            number[j] = '\0';
            if (push_token(&tokens[*tokens_count], TOKEN_NUMBER, number, tokens_count)) return 1;
            continue;
        }

        if (is_print_cmd(p))
        {
            if (push_token(&tokens[*tokens_count], TOKEN_PRINT, "print", tokens_count)) return 1;
            p += 5;
            continue;
        }

        char temp[2] = {*p, '\0'};
        int success = 0;

        if (is_alpha_char(*p))
        {
            success = push_token(&tokens[*tokens_count], TOKEN_VARIABLE, temp, tokens_count);
        }
        else if (is_operator_char(*p))
        {
            if (*p == '-')
            {
                int is_unary = 0;
                if (*tokens_count == 0)
                {
                    is_unary = 1;
                }
                else
                {
                    TokenType prev_type = tokens[*tokens_count - 1].type;
                    if (prev_type == TOKEN_OPERATOR ||
                        prev_type == TOKEN_LPAREN ||
                        prev_type == TOKEN_EQUAL)
                    {
                        is_unary = 1;
                    }
                }

                if (is_unary)
                {
                    temp[0] = '~';
                }
            }
            success = push_token(&tokens[*tokens_count], TOKEN_OPERATOR, temp, tokens_count);
        }
        else if (*p == '(')
        {
            success = push_token(&tokens[*tokens_count], TOKEN_LPAREN, temp, tokens_count);
        }
        else if (*p == ')')
        {
            success = push_token(&tokens[*tokens_count], TOKEN_RPAREN, temp, tokens_count);
        }
        else if (*p == '=')
        {
            success = push_token(&tokens[*tokens_count], TOKEN_EQUAL, temp, tokens_count);
        }
        else
        {
            printf("[ERROR] unknown symbol: %c\n", *p);
            return 1;
        }

        if (success) return 1;
        p++;
    }

    push_token(&tokens[*tokens_count], TOKEN_EOF, "", tokens_count);
    return 0;
}

int parsing_string(char* inp, Variables* table, char* op_name)
{
    Token tokens[MAX_SIZE_TOKENS];
    int tokens_count = 0;

    if (tokenize(inp, tokens, &tokens_count)) return 1;

    if (tokens_count == 0 || tokens[0].type == TOKEN_EOF) return 0;

    if (tokens[0].type == TOKEN_PRINT)
    {
        if (tokens_count >= 4 && tokens[1].type == TOKEN_LPAREN &&
            tokens[2].type == TOKEN_VARIABLE && tokens[3].type == TOKEN_RPAREN)
        {
            int varIdx = tokens[2].value[0] - 'A';
            int val = get_variable(table, varIdx);

            printf("%d\n", val);

            sprintf(op_name, "Print %s", tokens[2].value);
        }
        else
        {
            printf("Syntax error in print\n");
            return 1;
        }
    }
    else if (tokens_count > 2 && tokens[0].type == TOKEN_VARIABLE && tokens[1].type == TOKEN_EQUAL)
    {
        int targetVarIdx = tokens[0].value[0] - 'A';

        Token* expression_tokens = &tokens[2];
        Token postfix_tokens[MAX_SIZE_TOKENS];
        int postfix_count = to_postfix(expression_tokens, postfix_tokens);

        int result = calculating_expression(postfix_tokens, postfix_count, table);
        set_variable(table, targetVarIdx, result);

        int is_complex = 0;
        for (int i = 2; i < tokens_count; i++)
        {
            if (tokens[i].type == TOKEN_OPERATOR)
            {
                is_complex = 1;
                break;
            }
        }
        strcpy(op_name, is_complex ? "Arithmetic operation" : "Assignment");
    }
    else
    {
        return 0;
    }

    return 0;
}
