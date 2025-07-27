#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_KEYWORD,
    TOKEN_SYMBOL,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char* value;
    int position;
} Token;

#endif