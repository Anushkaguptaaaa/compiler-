CC = gcc
CFLAGS = -Wall -Wextra -g
INCLUDE = -I./include

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)
# Object files
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Executable name
TARGET = $(BIN_DIR)/mini_compiler

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Link object files to create executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the compiler
run: all
	$(TARGET)

.PHONY: all clean run directories
