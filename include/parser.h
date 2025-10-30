#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct {
    Lexer *lexer;
    Token current_token;
    Token peek_token;
    int error;
} Parser;

Parser* parser_init(Lexer *lexer);

void parser_free(Parser *parser);

void parser_next_token(Parser *parser);

int parser_expect_peek(Parser *parser, TokenType type);

char* parse_expression(Parser *parser, int precedence);

char* parse_term(Parser *parser);

char* parse_factor(Parser *parser);

void parser_parse(Parser *parser);

int parser_is_valid(Parser *parser);

#endif