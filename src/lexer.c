#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/lexer.h"

// Initialize lexer with input string
Lexer* lexer_init(char *input) {
    Lexer *lexer = (Lexer*)malloc(sizeof(Lexer));
    if (!lexer) {
        fprintf(stderr, "Failed to allocate memory for lexer\n");
        exit(1);
    }
    
    lexer->input = input;
    lexer->position = 0;
    lexer->read_position = 0;
    lexer->current_char = '\0';
    
    // Read the first character
    lexer_read_char(lexer);
    
    return lexer;
}

// Free lexer resources
void lexer_free(Lexer *lexer) {
    if (lexer) {
        free(lexer);
    }
}

// Read the next character
void lexer_read_char(Lexer *lexer) {
    if (lexer->read_position >= (int)strlen(lexer->input)) {
        lexer->current_char = '\0'; // EOF
    } else {
        lexer->current_char = lexer->input[lexer->read_position];
    }
    
    lexer->position = lexer->read_position;
    lexer->read_position++;
}

// Skip whitespace characters
void lexer_skip_whitespace(Lexer *lexer) {
    while (isspace(lexer->current_char)) {
        lexer_read_char(lexer);
    }
}

// Check if the character is a letter
int is_letter(char ch) {
    return isalpha(ch) || ch == '_';
}

// Check if the character is a digit
int is_digit(char ch) {
    return isdigit(ch);
}

// Read an identifier
void read_identifier(Lexer *lexer, Token *token) {
    int start_pos = lexer->position;
    while (is_letter(lexer->current_char)) {
        lexer_read_char(lexer);
    }
    
    int length = lexer->position - start_pos;
    strncpy(token->lexeme, lexer->input + start_pos, length);
    token->lexeme[length] = '\0';
    token->type = TOKEN_ID;
}

// Read a number
void read_number(Lexer *lexer, Token *token) {
    int start_pos = lexer->position;
    while (is_digit(lexer->current_char)) {
        lexer_read_char(lexer);
    }
    
    int length = lexer->position - start_pos;
    strncpy(token->lexeme, lexer->input + start_pos, length);
    token->lexeme[length] = '\0';
    token->type = TOKEN_NUM;
}

// Get the next token from the input
Token lexer_next_token(Lexer *lexer) {
    Token token;
    memset(token.lexeme, 0, sizeof(token.lexeme));
    
    lexer_skip_whitespace(lexer);
    
    switch (lexer->current_char) {
        case '+':
            token.type = TOKEN_PLUS;
            strcpy(token.lexeme, "+");
            lexer_read_char(lexer);
            break;
        case '-':
            token.type = TOKEN_MINUS;
            strcpy(token.lexeme, "-");
            lexer_read_char(lexer);
            break;
        case '*':
            token.type = TOKEN_MULT;
            strcpy(token.lexeme, "*");
            lexer_read_char(lexer);
            break;
        case '/':
            token.type = TOKEN_DIV;
            strcpy(token.lexeme, "/");
            lexer_read_char(lexer);
            break;
        case '(':
            token.type = TOKEN_LPAREN;
            strcpy(token.lexeme, "(");
            lexer_read_char(lexer);
            break;
        case ')':
            token.type = TOKEN_RPAREN;
            strcpy(token.lexeme, ")");
            lexer_read_char(lexer);
            break;
        case '=':
            token.type = TOKEN_ASSIGN;
            strcpy(token.lexeme, "=");
            lexer_read_char(lexer);
            break;
        case '\0':
            token.type = TOKEN_EOF;
            strcpy(token.lexeme, "EOF");
            break;
        default:
            if (is_letter(lexer->current_char)) {
                read_identifier(lexer, &token);
            } else if (is_digit(lexer->current_char)) {
                read_number(lexer, &token);
            } else {
                token.type = TOKEN_INVALID;
                token.lexeme[0] = lexer->current_char;
                token.lexeme[1] = '\0';
                lexer_read_char(lexer);
            }
            break;
    }
    
    return token;
}
