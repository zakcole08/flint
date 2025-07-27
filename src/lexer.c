#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

char* flint_strndup(const char* s, size_t n) {
    char* result = malloc(n + 1);
    if (!result) return NULL;
    strncpy(result, s, n);
    result[n] = '\0';
    return result;
}

const char* keywords[] = { "let", "fn", "if", "else", "elif", "main", "return", "print" };
int is_keyword(const char* str) {
    for (size_t i = 0; i < sizeof(keywords)/sizeof(char*); i++) {
        if (strcmp(str, keywords[i]) == 0) return 1;
    }
    return 0;
}

void init_lexer(Lexer* lexer, const char* source) {
    lexer->source = source;
    lexer->pos = 0;
    lexer->token_count = 0;
}

void add_token(Lexer* lexer, TokenType type, const char* start, int length) {
    Token* token = &lexer->tokens[lexer->token_count++];
    token->type = type;
    token->value = flint_strndup(start, length);
    token->position = lexer->pos;
}

void tokenise(Lexer* lexer) {
    const char* src = lexer->source;
    while (src[lexer->pos] != '\0') {
        char c = src[lexer->pos];
            
        if (isspace(c)) {
            lexer->pos++;
            continue;
        }

        if (isalpha(c) || c == '_') {
            int start = lexer->pos;
            while (isalnum(src[lexer->pos]) || src[lexer->pos] == '_') lexer->pos++;
            int len = lexer->pos - start;
            char* word = flint_strndup(src + start, len);
            TokenType type = is_keyword(word) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
            add_token(lexer, type, src + start, len);
            free(word);
            continue;
        }

        if (isdigit(c)) {
            int start = lexer->pos;
            while (isdigit(src[lexer->pos])) lexer->pos++;
            add_token(lexer, TOKEN_NUMBER, src + start, lexer->pos - start);
            continue;
        }

        if (c == '"') {
            lexer->pos++; // skip opening quote
            int start = lexer->pos;
            while (src[lexer->pos] != '"' && src[lexer->pos] != '\0') lexer->pos++;
            add_token(lexer, TOKEN_STRING, src + start, lexer->pos - start);
            if (src[lexer->pos] == '"') lexer->pos++; // skip closing quote
            continue;
        }

        if (strchr("(){}=:+-*/,", c)) {
            add_token(lexer, TOKEN_SYMBOL, &src[lexer->pos], 1);
            lexer->pos++;
            continue;
        }

        if (c == '>') {
            add_token(lexer, TOKEN_SYMBOL, &src[lexer->pos], 1);
            lexer->pos++;
            continue;
        }

        printf("Unknown character: '%c'\n", c);
        exit(1);
    }

    add_token(lexer, TOKEN_EOF, "", 0);
}

void print_tokens(const Lexer* lexer) {
    for (int i = 0; i < lexer->token_count; i++) {
        Token t = lexer->tokens[i];
        const char* type_str = 
            t.type == TOKEN_KEYWORD ? "KEYWORD" :
            t.type == TOKEN_IDENTIFIER ? "IDENTIFIER" :
            t.type == TOKEN_NUMBER ? "NUMBER" :
            t.type == TOKEN_STRING ? "STRING" :
            t.type == TOKEN_SYMBOL ? "SYMBOL" :
            t.type == TOKEN_EOF ? "EOF" : "UNKNOWN";

        printf("<%s: %s>\n", type_str, t.value);
    }
}