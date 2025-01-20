# Paths for CUnit
CUNIT_INCLUDE = /opt/homebrew/Cellar/cunit/2.1-3/include
CUNIT_LIB = /opt/homebrew/Cellar/cunit/2.1-3/lib

# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -O2 -I$(CUNIT_INCLUDE)
LDFLAGS = -L$(CUNIT_LIB) -lcunit -Wl,-rpath,@loader_path

# Phony targets
.PHONY: all test main
all: aes

aes: aes.c
	$(CC) $(CFLAGS) -c -o aes.o $<
	$(CC) $(CFLAGS) -shared -fPIC -o libaes.so aes.o
	$(AR) rcs libaes.a aes.o

test: aes test_case.c
ifeq ($(CUNIT_VER), "2.1-2")
	$(CC) $(CFLAGS) -o test_case test_case.c $(LDFLAGS) -DCUNIT_VER=2
else ifneq ($(CUNIT_VER), "not_found")
	$(CC) $(CFLAGS) -o test_case test_case.c $(LDFLAGS) -DCUNIT_VER=1
else
	@echo "CUnit not found. Please install CUnit development library."
	exit 1
endif
	./test_case

main: aes main.c
	$(CC) $(CFLAGS) -o main main.c -L./ -laes
	./main

.PHONY: install uninstall clean
install: aes
	install libaes.so $(PREFIX)/lib/
	ln -sf $(PREFIX)/lib/libaes.so $(HOME)/.local/lib/libaes.so
	install aes.h $(PREFIX)/include/aes.h
	
uninstall:
	rm -f $(PREFIX)/lib/libaes.so $(HOME)/.local/lib/libaes.so $(PREFIX)/include/aes.h

clean:
	rm -f *.o *.so *.a test_case main
