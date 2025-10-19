#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"

// Code generator structure
typedef struct {
    int temp_count;     // Counter for temporary variables
    char **code;        // Array of generated code lines
    int code_size;      // Current size of code array
    int code_capacity;  // Capacity of code array
} CodeGen;

// Initialize code generator
CodeGen* codegen_init();

// Free code generator resources
void codegen_free(CodeGen *codegen);

// Generate a new temporary variable
char* codegen_new_temp(CodeGen *codegen);

// Add a line of code to the code array
void codegen_emit(CodeGen *codegen, const char *format, ...);

// Generate code for binary operation
char* codegen_binary_op(CodeGen *codegen, char *left, char op, char *right);

// Print the generated code
void codegen_print(CodeGen *codegen);

#endif // CODEGEN_H
