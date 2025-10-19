#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Parser structure
typedef struct {
    Lexer *lexer;       // Lexer to get tokens from
    Token current_token; // Current token
    Token peek_token;    // Next token
    int error;          // Error flag
} Parser;

// Initialize parser with lexer
Parser* parser_init(Lexer *lexer);

// Free parser resources
void parser_free(Parser *parser);

// Advance to the next token
void parser_next_token(Parser *parser);

// Check if current token is of expected type
int parser_expect_peek(Parser *parser, TokenType type);

// Parse an expression
// Returns the result variable (could be a temp variable or an identifier)
char* parse_expression(Parser *parser, int precedence);

// Parse a term (T in the grammar)
char* parse_term(Parser *parser);

// Parse a factor (F in the grammar)
char* parse_factor(Parser *parser);

// Parse the entire input
void parser_parse(Parser *parser);

// Check if the expression is valid
int parser_is_valid(Parser *parser);

#endif // PARSER_H
