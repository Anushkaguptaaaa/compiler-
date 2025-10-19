#ifndef TOKEN_H
#define TOKEN_H

// Token types
typedef enum {
    TOKEN_ID,       // Identifier (variable)
    TOKEN_NUM,      // Number
    TOKEN_PLUS,     // +
    TOKEN_MINUS,    // -
    TOKEN_MULT,     // *
    TOKEN_DIV,      // /
    TOKEN_LPAREN,   // (
    TOKEN_RPAREN,   // )
    TOKEN_ASSIGN,   // =
    TOKEN_EOF,      // End of input
    TOKEN_INVALID   // Invalid token
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char lexeme[100];  // The actual string value of the token
} Token;

#endif // TOKEN_H
