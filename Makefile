CC=cc
C_FLAGS=-Wall -std=c99 -pg -g
BIN_DIR=bin
BIN_NAME=main
OBJ_DIR=bin/obj

all: hashmap
	$(CC) $(C_FLAGS) $(OBJ_DIR)/*.o main.c -o $(BIN_DIR)/$(BIN_NAME)

hashmap:
	mkdir -p $(OBJ_DIR)
	$(CC) $(C_FLAGS) -c hashmap.c -o $(OBJ_DIR)/hashmap.o
