## Project settings
INC=src/headers/

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

CONTAINERS_SRC=\
	../src/containers/arr/*.c
CONTAINERS_INC=\
	-I../src/containers/arr \
	-I../src/containers/vec \
	-I../src/containers/str

## Targets and dependencies
all:
	$(CC) $(CFLAGS) -O3 $(SRC) -o $(BIN)

debug:
	$(CC) $(CFLAGS) -O0 $(SRC) -o $(BIN)

containers:
	cd build; $(CC) $(CFLAGS) $(CONTAINERS_SRC) $(CONTAINERS_INC) -O3 -c
