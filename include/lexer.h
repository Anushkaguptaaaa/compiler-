#ifndef LEXER_H
#define LEXER_H

#include "token.h"

// Lexer structure
typedef struct {
    char *input;    // Input string
    int position;   // Current position in input
    int read_position; // Position after current character
    char current_char; // Current character under examination
} Lexer;

// Initialize lexer with input string
Lexer* lexer_init(char *input);

// Free lexer resources
void lexer_free(Lexer *lexer);

// Get the next token from the input
Token lexer_next_token(Lexer *lexer);

// Read the next character
void lexer_read_char(Lexer *lexer);

// Skip whitespace characters
void lexer_skip_whitespace(Lexer *lexer);

// Check if the character is a letter
int is_letter(char ch);

// Check if the character is a digit
int is_digit(char ch);

#endif // LEXER_H
