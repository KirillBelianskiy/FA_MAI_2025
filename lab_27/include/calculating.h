#pragma once

#include "Token.h"
#include "table.h"

int fastPow(int number, int n);
int to_postfix(Token* inp, Token* outp);
int calculating_expression(Token* postfix, int postfix_count, Variables* table);
