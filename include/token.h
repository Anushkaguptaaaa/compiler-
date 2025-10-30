#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_ID,
    TOKEN_NUM,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_ASSIGN,
    TOKEN_EOF,
    TOKEN_INVALID
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[100];
} Token;

#endif