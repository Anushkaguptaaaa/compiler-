#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "../include/codegen.h"

#define INITIAL_CAPACITY 10

CodeGen* codegen_init() {
    CodeGen *codegen = (CodeGen*)malloc(sizeof(CodeGen));
    if (!codegen) {
        fprintf(stderr, "Failed to allocate memory for code generator\n");
        exit(1);
    }
    
    codegen->temp_count = 1;
    codegen->code_size = 0;
    codegen->code_capacity = INITIAL_CAPACITY;
    
    codegen->code = (char**)malloc(codegen->code_capacity * sizeof(char*));
    if (!codegen->code) {
        fprintf(stderr, "Failed to allocate memory for code array\n");
        free(codegen);
        exit(1);
    }
    
    return codegen;
}

void codegen_free(CodeGen *codegen) {
    if (codegen) {
        for (int i = 0; i < codegen->code_size; i++) {
            free(codegen->code[i]);
        }
        free(codegen->code);
        free(codegen);
    }
}

char* codegen_new_temp(CodeGen *codegen) {
    char *temp = (char*)malloc(10 * sizeof(char));
    if (!temp) {
        fprintf(stderr, "Failed to allocate memory for temporary variable\n");
        exit(1);
    }
    
    sprintf(temp, "t%d", codegen->temp_count++);
    return temp;
}

void codegen_emit(CodeGen *codegen, const char *format, ...) {
    if (codegen->code_size >= codegen->code_capacity) {
        codegen->code_capacity *= 2;
        codegen->code = (char**)realloc(codegen->code, codegen->code_capacity * sizeof(char*));
        if (!codegen->code) {
            fprintf(stderr, "Failed to reallocate memory for code array\n");
            exit(1);
        }
    }
    
    va_list args;
    va_start(args, format);
    
    va_list args_copy;
    va_copy(args_copy, args);
    int size = vsnprintf(NULL, 0, format, args_copy) + 1;
    va_end(args_copy);
    
    char *code_line = (char*)malloc(size * sizeof(char));
    if (!code_line) {
        fprintf(stderr, "Failed to allocate memory for code line\n");
        va_end(args);
        exit(1);
    }
    
    vsnprintf(code_line, size, format, args);
    va_end(args);
    
    codegen->code[codegen->code_size++] = code_line;
}

char* codegen_binary_op(CodeGen *codegen, char *left, char op, char *right) {
    char *result = codegen_new_temp(codegen);
    codegen_emit(codegen, "%s = %s %c %s", result, left, op, right);
    return result;
}

void codegen_print(CodeGen *codegen) {
    printf("\nGenerated Three-Address Code:\n");
    for (int i = 0; i < codegen->code_size; i++) {
        printf("%s\n", codegen->code[i]);
    }
}