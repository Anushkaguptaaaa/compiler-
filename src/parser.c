#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

typedef enum {
    PREC_LOWEST,
    PREC_EQUALS,
    PREC_SUM,
    PREC_PRODUCT,
    PREC_PREFIX,
    PREC_CALL
} Precedence;

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

Parser* parser_init(Lexer *lexer) {
    Parser *parser = (Parser*)malloc(sizeof(Parser));
    if (!parser) {
        fprintf(stderr, "Failed to allocate memory for parser\n");
        exit(1);
    }
    
    parser->lexer = lexer;
    parser->error = 0;
    
    parser_next_token(parser);
    parser_next_token(parser);
    
    return parser;
}

void parser_free(Parser *parser) {
    if (parser) {
        free(parser);
    }
}

void parser_next_token(Parser *parser) {
    parser->current_token = parser->peek_token;
    parser->peek_token = lexer_next_token(parser->lexer);
}

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

char* parse_expression(Parser *parser, int precedence) {
    char *left = (char*)malloc(100 * sizeof(char));
    if (!left) {
        fprintf(stderr, "Failed to allocate memory for expression\n");
        exit(1);
    }
    
    switch (parser->current_token.type) {
        case TOKEN_ID:
        case TOKEN_NUM:
            strcpy(left, parser->current_token.lexeme);
            break;
        case TOKEN_LPAREN:
            parser_next_token(parser);
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
    
    while (parser->peek_token.type != TOKEN_EOF && 
           precedence < get_precedence(parser->peek_token.type)) {
        
        TokenType op_type = parser->peek_token.type;
        parser_next_token(parser);
        
        parser_next_token(parser);
        
        char *right = parse_expression(parser, get_precedence(op_type));
        
        char *temp = (char*)malloc(100 * sizeof(char));
        if (!temp) {
            fprintf(stderr, "Failed to allocate memory for temporary variable\n");
            exit(1);
        }
        sprintf(temp, "t%d", rand() % 100);
        
        char op = '\0';
        switch (op_type) {
            case TOKEN_PLUS: op = '+'; break;
            case TOKEN_MINUS: op = '-'; break;
            case TOKEN_MULT: op = '*'; break;
            case TOKEN_DIV: op = '/'; break;
            default: op = '?';
        }
        
        printf("%s = %s %c %s\n", temp, left, op, right);
        
        free(left);
        left = temp;
        free(right);
    }
    
    return left;
}

void parser_parse(Parser *parser) {
    if (parser->current_token.type == TOKEN_ID && 
        parser->peek_token.type == TOKEN_ASSIGN) {
        
        char lhs[100];
        strcpy(lhs, parser->current_token.lexeme);
        
        parser_next_token(parser);
        parser_next_token(parser);
        
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

int parser_is_valid(Parser *parser) {
    return !parser->error;
}