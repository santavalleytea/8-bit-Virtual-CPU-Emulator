# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -I./src

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
BIN = $(BIN_DIR)/cpu

# Source files (excluding write_program.c)
SRCS = $(filter-out $(SRC_DIR)/write_program.c, $(wildcard $(SRC_DIR)/*.c))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Write program files
WRITE_SRC = $(SRC_DIR)/write_program.c
WRITE_OBJ = $(OBJ_DIR)/write_program.o
WRITE_BIN = $(BIN_DIR)/write_program

# Default target: compile, run writer, build cpu
all: generate_program $(BIN)

# Step 1: Compile and run write_program to generate program.bin
generate_program: $(WRITE_BIN)
	@echo "📦 Running write_program to generate bin/program.bin..."
	./$(WRITE_BIN)

# Step 2: Build main CPU binary
$(BIN): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c files (excluding write_program.c)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile write_program.c to obj/write_program.o
$(WRITE_OBJ): $(WRITE_SRC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link write_program binary
$(WRITE_BIN): $(WRITE_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Clean everything
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean generate_program