#ifndef LEXER_H
#define LEXER_H

#include "token.h"

#define MAX_TOKENS 1024

typedef struct {
    const char*  source;
    int pos;
    Token tokens[MAX_TOKENS];
    int token_count;
} Lexer;

void init_lexer(Lexer* lexer, const char* source);
void tokenise(Lexer* lexer);
void print_tokens(const Lexer* lexer);

#endif