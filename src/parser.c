#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

// Precedence levels for operators
typedef enum {
    PREC_LOWEST,
    PREC_EQUALS,      // =
    PREC_SUM,         // + -
    PREC_PRODUCT,     // * /
    PREC_PREFIX,      // -X or !X
    PREC_CALL         // myFunction(X)
} Precedence;

// Get precedence for a token type
int get_precedence(TokenType type) {
    switch (type) {
        case TOKEN_PLUS:
        case TOKEN_MINUS:
            return PREC_SUM;
        case TOKEN_MULT:
        case TOKEN_DIV:
            return PREC_PRODUCT;
        default:
            return PREC_LOWEST;
    }
}

// Initialize parser with lexer
Parser* parser_init(Lexer *lexer) {
    Parser *parser = (Parser*)malloc(sizeof(Parser));
    if (!parser) {
        fprintf(stderr, "Failed to allocate memory for parser\n");
        exit(1);
    }
    
    parser->lexer = lexer;
    parser->error = 0;
    
    // Read two tokens to initialize current_token and peek_token
    parser_next_token(parser);
    parser_next_token(parser);
    
    return parser;
}

// Free parser resources
void parser_free(Parser *parser) {
    if (parser) {
        free(parser);
    }
}

// Advance to the next token
void parser_next_token(Parser *parser) {
    parser->current_token = parser->peek_token;
    parser->peek_token = lexer_next_token(parser->lexer);
}

// Check if current token is of expected type
int parser_expect_peek(Parser *parser, TokenType type) {
    if (parser->peek_token.type == type) {
        parser_next_token(parser);
        return 1;
    } else {
        parser->error = 1;
        fprintf(stderr, "Expected next token to be %d, got %d instead\n", type, parser->peek_token.type);
        return 0;
    }
}

// Parse an expression
char* parse_expression(Parser *parser, int precedence) {
    // Allocate memory for the result
    char *left = (char*)malloc(100 * sizeof(char));
    if (!left) {
        fprintf(stderr, "Failed to allocate memory for expression\n");
        exit(1);
    }
    
    // Parse the prefix expression
    switch (parser->current_token.type) {
        case TOKEN_ID:
        case TOKEN_NUM:
            strcpy(left, parser->current_token.lexeme);
            break;
        case TOKEN_LPAREN:
            parser_next_token(parser); // consume '('
            strcpy(left, parse_expression(parser, PREC_LOWEST));
            if (!parser_expect_peek(parser, TOKEN_RPAREN)) {
                free(left);
                return NULL;
            }
            break;
        default:
            fprintf(stderr, "Unexpected token: %s\n", parser->current_token.lexeme);
            parser->error = 1;
            free(left);
            return NULL;
    }
    
    // Parse the infix expression
    while (parser->peek_token.type != TOKEN_EOF && 
           precedence < get_precedence(parser->peek_token.type)) {
        
        TokenType op_type = parser->peek_token.type;
        parser_next_token(parser); // consume operator
        
        parser_next_token(parser); // move to the right operand
        
        // Parse the right operand
        char *right = parse_expression(parser, get_precedence(op_type));
        
        // Create a new temporary variable for the result
        char *temp = (char*)malloc(100 * sizeof(char));
        if (!temp) {
            fprintf(stderr, "Failed to allocate memory for temporary variable\n");
            exit(1);
        }
        sprintf(temp, "t%d", rand() % 100); // Simple temp variable generation
        
        // Print the three-address code
        char op = '\0';
        switch (op_type) {
            case TOKEN_PLUS: op = '+'; break;
            case TOKEN_MINUS: op = '-'; break;
            case TOKEN_MULT: op = '*'; break;
            case TOKEN_DIV: op = '/'; break;
            default: op = '?';
        }
        
        printf("%s = %s %c %s\n", temp, left, op, right);
        
        // Update left for the next iteration
        free(left);
        left = temp;
        free(right);
    }
    
    return left;
}

// Parse the entire input
void parser_parse(Parser *parser) {
    // Check if this is an assignment
    if (parser->current_token.type == TOKEN_ID && 
        parser->peek_token.type == TOKEN_ASSIGN) {
        
        char lhs[100];
        strcpy(lhs, parser->current_token.lexeme);
        
        parser_next_token(parser); // consume identifier
        parser_next_token(parser); // consume '='
        
        char *result = parse_expression(parser, PREC_LOWEST);
        if (result) {
            printf("%s = %s\n", lhs, result);
            free(result);
        }
    } else {
        char *result = parse_expression(parser, PREC_LOWEST);
        if (result) {
            free(result);
        }
    }
}

// Check if the expression is valid
int parser_is_valid(Parser *parser) {
    return !parser->error;
}
