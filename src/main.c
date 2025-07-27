// main.c
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

char* read_file(const char* path) {
    FILE* f = fopen(path, "r");
    if (!f) {
        perror("File open failed");
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    rewind(f);
    char* buffer = malloc(len + 1);
    fread(buffer, 1, len, f);
    buffer[len] = '\0';
    fclose(f);
    return buffer;
}

int main() {
    char* code = read_file("test.flt");
    Lexer lexer;
    init_lexer(&lexer, code);
    tokenise(&lexer);
    print_tokens(&lexer);
    free(code);
    return 0;
}