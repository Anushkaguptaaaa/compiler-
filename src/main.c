#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/codegen.h"

#define MAX_INPUT_SIZE 1000

void print_token(Token token) {
    const char* type_names[] = {
        "ID", "NUM", "PLUS", "MINUS", "MULT", "DIV", "LPAREN", "RPAREN", "ASSIGN", "EOF", "INVALID"
    };
    
    printf("Token { type: %s, lexeme: \"%s\" }\n", 
           type_names[token.type], token.lexeme);
}

void perform_lexical_analysis(char *input) {
    printf("\n===== Lexical Analysis =====\n");
    
    Lexer *lexer = lexer_init(input);
    Token token;
    
    do {
        token = lexer_next_token(lexer);
        print_token(token);
    } while (token.type != TOKEN_EOF);
    
    lexer_free(lexer);
}

void perform_syntax_analysis(char *input) {
    printf("\n===== Syntax Analysis =====\n");
    
    Lexer *lexer = lexer_init(input);
    Parser *parser = parser_init(lexer);
    
    parser_parse(parser);
    
    if (parser_is_valid(parser)) {
        printf("Valid expression!\n");
    } else {
        printf("Invalid expression!\n");
    }
    
    parser_free(parser);
    lexer_free(lexer);
}

void perform_code_generation(char *input) {
    printf("\n===== Code Generation =====\n");
    
    Lexer *lexer = lexer_init(input);
    Parser *parser = parser_init(lexer);
    
    parser_parse(parser);
    
    parser_free(parser);
    lexer_free(lexer);
}

int main() {
    char input[MAX_INPUT_SIZE];
    
    printf("Mini Compiler for Arithmetic Expressions\n");
    printf("Enter an arithmetic expression: ");
    
    if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    srand(time(NULL));
    
    perform_lexical_analysis(input);
    perform_syntax_analysis(input);
    perform_code_generation(input);
    
    return 0;
}