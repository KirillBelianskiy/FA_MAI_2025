#include <string.h>

#include "../include/Token.h"

void set_token(Token* token, TokenType type, char* value)
{
    token->type = type;
    strcpy(token->value, value);
}
