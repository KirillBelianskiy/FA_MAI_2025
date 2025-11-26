#pragma once

typedef enum
{
    TOKEN_NUMBER,
    TOKEN_VARIABLE,
    TOKEN_EQUAL,
    TOKEN_OPERATOR,
    TOKEN_LPAREN, // (
    TOKEN_RPAREN, // )
    TOKEN_PRINT,
    TOKEN_EOF
} TokenType;

typedef struct
{
    TokenType type;
    char value[11];
} Token;

void set_token(Token* token, TokenType type, char* value);
