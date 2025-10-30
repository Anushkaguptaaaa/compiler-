#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct {
    char *input;
    int position;
    int read_position;
    char current_char;
} Lexer;

Lexer* lexer_init(char *input);

void lexer_free(Lexer *lexer);

Token lexer_next_token(Lexer *lexer);

void lexer_read_char(Lexer *lexer);

void lexer_skip_whitespace(Lexer *lexer);

int is_letter(char ch);

int is_digit(char ch);

#endif