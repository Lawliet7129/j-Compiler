# J Language Compiler and Virtual Stack Machine

## Overview

This project implements a simple compiler for a custom programming language called "J" and a virtual stack machine to execute the generated assembly code. The compiler processes J source files, tokenizes the input, and generates assembly code compatible with a stack-based architecture. The virtual stack machine provides stack operations and arithmetic, logical, and control-flow constructs.

## Features

### Compiler
- Tokenizes the J language source files into defined tokens (e.g., `defun`, `if`, `while`, `+`, `-`).
- Supports the following:
  - Function definitions (`defun`).
  - Arithmetic operations (`+`, `-`, `*`, `/`, `%`).
  - Logical operations (`and`, `or`, `not`).
  - Comparison operations (`lt`, `le`, `eq`, `ge`, `gt`).
  - Control flow (`if`, `else`, `endif`, `while`, `endwhile`).
  - Stack manipulation (`push`, `pop`, `dup`, `swap`, `rot`, `drop`).
- Generates assembly code that can be executed on a stack-based virtual machine.

### Virtual Stack Machine
- Implements core stack operations:
  - `push` - Add an element to the top of the stack.
  - `pop` - Remove and return the top element of the stack.
  - `peek` - View the top element without removing it.
  - `clear` - Clear all elements from the stack.
- Handles arithmetic, logical, and comparison operations directly on stack operands.

### Tokenizer
- Reads and identifies valid tokens from a J language source file.
- Handles literal values, identifiers, and reserved keywords.
- Provides line number tracking for error reporting.

## File Descriptions

### `jc.c`
- Main compiler logic that processes J source files.
- Reads tokens and generates assembly code using the `generate_asm` function.
- Handles function definitions, control flow, and stack operations.

### `stack.c` and `stack.h`
- Implements a linked-list-based stack with operations for pushing, popping, and peeking elements.
- Includes utility functions for stack initialization and cleanup.

### `token.c` and `token.h`
- Provides functionality to tokenize a J source file.
- Defines token types and structures, including:
  - Reserved keywords (e.g., `defun`, `return`, `if`, `else`, `endif`, etc.).
  - Arithmetic and logical operators.
  - Literals and identifiers.
- Ensures proper parsing and error reporting.

### `Makefile`
- Build automation file for compiling the project.
- Includes targets to compile, clean, and run the program.

## Getting Started

### Prerequisites
- C compiler (e.g., `gcc`).
- Make utility (optional for using `Makefile`).

### Building the Project
1. Clone the repository:
   
   ```
   git clone <repository_url>
   cd <repository_directory>
   ```
3. Build the project using `make`:
   
   ```
   make
   ```

### Running the Compiler
1. Provide a J source file as input:
   
   ```
   ./jc <source_file.j>
   ```
3. The generated assembly file will be created in the same directory with the `.s` extension.

### Cleaning Up
- Remove compiled binaries and temporary files:
  
  ```
  make clean
  ```

## Project Structure
```
.
├── jc.c            # Main compiler source code
├── stack.c         # Stack implementation
├── stack.h         # Stack header file
├── token.c         # Tokenizer implementation
├── token.h         # Tokenizer header file
├── Makefile        # Build automation file
├── README.md       # Project documentation
```
