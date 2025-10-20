CC := clang
CFLAGS := -Wall -Wextra -Wpedantic -Iinclude -framework JavaScriptCore

SRC_DIR := src
INC_DIR := include
OBJ_DIR := build

SRC := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET := ./build/main

all: $(TARGET) js

run: all
	@$(TARGET)

js:
	@bun build ./src_ts/main.ts --outfile ./build/main.js --minify

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

fclean: clean

re: fclean all

.PHONY: all clean fclean re js
