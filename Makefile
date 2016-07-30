CC=$(shell which gcc)
C_FLAGS=-Wall -std=c99
BIN_DIR=bin
BIN_NAME=main
OBJ_DIR=bin/obj

hashmap:
	mkdir -p $(OBJ_DIR)
	$(CC) $(C_FLAGS) -c hashmap.c -o $(OBJ_DIR)/hashmap.o

all: hashmap
	$(CC) $(C_FLAGS) $(OBJ_DIR)/*.o main.c -o $(BIN_DIR)/$(BIN_NAME)