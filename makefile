## Compilation settings
BIN=bin/resembler
CC=gcc
CFLAGS= -std=c11 \
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
SRC=src/*.c
INC=    -Isrc/header/trait/ \
	-Isrc/header/core/ \
	-Isrc/header/ 

## Targets and dependencies
all:
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(BIN)
