# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -O2
LDFLAGS = -L./ -laes

# Phony targets
.PHONY: all test main clean

# Default target: build AES library and test
all: aes

# Build AES library
aes: aes.c
	$(CC) $(CFLAGS) -c -o aes.o $<
	$(CC) $(CFLAGS) -shared -fPIC -o libaes.so aes.o
	$(AR) rcs libaes.a aes.o

# Test program for AES library
test: aes test_case.c
	$(CC) $(CFLAGS) -o test_case test_case.c $(LDFLAGS)
	./test_case

# Main program for additional testing
main: aes main.c
	$(CC) $(CFLAGS) -o main main.c $(LDFLAGS)
	./main

# Clean up generated files
clean:
	rm -f *.o *.so *.a test_case main
