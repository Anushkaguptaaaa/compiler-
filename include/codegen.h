#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"

typedef struct {
    int temp_count;
    char **code;
    int code_size;
    int code_capacity;
} CodeGen;

CodeGen* codegen_init();

void codegen_free(CodeGen *codegen);

char* codegen_new_temp(CodeGen *codegen);

void codegen_emit(CodeGen *codegen, const char *format, ...);

char* codegen_binary_op(CodeGen *codegen, char *left, char op, char *right);

void codegen_print(CodeGen *codegen);

#endif