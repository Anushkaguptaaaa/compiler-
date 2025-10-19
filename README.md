# Mini Compiler for Arithmetic Expressions

A simple compiler written in C that performs lexical analysis, syntax analysis, and intermediate code generation for arithmetic expressions.

## Project Structure

```
compiler-/
├── include/           # Header files
│   ├── token.h        # Token definitions
│   ├── lexer.h        # Lexical analyzer interface
│   ├── parser.h       # Syntax analyzer interface
│   └── codegen.h      # Code generator interface
├── src/               # Source files
│   ├── lexer.c        # Lexical analyzer implementation
│   ├── parser.c       # Syntax analyzer implementation
│   ├── codegen.c      # Code generator implementation
│   └── main.c         # Main program
├── obj/               # Object files (created during build)
├── bin/               # Binary output (created during build)
├── Makefile           # Build instructions
└── README.md          # This file
```

## Features

1. **Lexical Analysis (Tokenizer)**
   - Breaks input like `a = b + c * d` into tokens: `ID(a)`, `=`, `ID(b)`, `+`, `ID(c)`, `*`, `ID(d)`
   - Supports identifiers, numbers, and operators (+, -, *, /, =, (, ))

2. **Syntax Analysis (Parser)**
   - Checks if tokens follow grammar rules
   - Implements a recursive descent parser for the grammar:
     ```
     E → E + T | E - T | T
     T → T * F | T / F | F
     F → (E) | id | num
     ```

3. **Intermediate Code Generation**
   - Generates three-address code (TAC) for the expression
   - Example: For input `a = b + c * d`, generates:
     ```
     t1 = c * d
     t2 = b + t1
     a = t2
     ```

## Building and Running

### Prerequisites

- GCC compiler
- Make utility

### Build

```bash
make
```

### Run

```bash
make run
```

Or directly:

```bash
./bin/mini_compiler
```

## Usage

1. Enter an arithmetic expression when prompted
2. The compiler will perform lexical analysis, syntax analysis, and code generation
3. The results of each phase will be displayed

## Example

Input:
```
a = b + c * d
```

Output:
```
===== Lexical Analysis =====
Token { type: ID, lexeme: "a" }
Token { type: ASSIGN, lexeme: "=" }
Token { type: ID, lexeme: "b" }
Token { type: PLUS, lexeme: "+" }
Token { type: ID, lexeme: "c" }
Token { type: MULT, lexeme: "*" }
Token { type: ID, lexeme: "d" }
Token { type: EOF, lexeme: "EOF" }

===== Syntax Analysis =====
Valid expression!

===== Code Generation =====
t1 = c * d
t2 = b + t1
a = t2
```

## Grammar

The compiler uses the following grammar for arithmetic expressions:

```
E → E + T | E - T | T
T → T * F | T / F | F
F → (E) | id | num
```

Where:
- E represents an expression
- T represents a term
- F represents a factor
- id represents an identifier (variable)
- num represents a number
