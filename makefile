## Project settings
INC=src/headers/

## Compilation settings
BIN=bin/resembler
CC=gcc
CFLAGS=-I$(INC) \
	-std=c11 \
	-pedantic \
	-Wfatal-errors \
	-Wall \
	-Wextra \
	-Wcast-align \
	-Wcast-qual \
	-Wformat=2 \
	-Winit-self \
	-Wlogical-op \
	-Wmissing-declarations \
	-Wmissing-include-dirs \
	-Wredundant-decls \
	-Wshadow \
	-Wsign-conversion \
	-Wstrict-overflow=5 \
	-Wundef \
	-Wno-unused \
	-Winline

## Sources
SRC=\
	src/arr.c \
	src/lex.c \
	src/vec.c \
	src/main.c

## Targets and dependencies
all:
	$(CC) $(CFLAGS) -O3 $(SRC) -o $(BIN)

debug:
	$(CC) $(CFLAGS) -O0 $(SRC) -o $(BIN)

