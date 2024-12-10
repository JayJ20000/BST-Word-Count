# Compiler and flags
CC = g++
CFLAGS = -g -Wall -Wextra

# Default entry point
default: bst_program

# Build the target executable
bst_program: main.o bst.o
	$(CC) $(CFLAGS) -o bst_program main.o bst.o

# Rule to create main.o
main.o: main.cpp bst.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o

# Rule to create bst.o
bst.o: bst.cpp bst.h
	$(CC) $(CFLAGS) -c bst.cpp -o bst.o

# Clean up build files
clean:
	$(RM) bst_program *.o *~
