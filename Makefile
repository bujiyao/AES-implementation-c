CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -O2
LDFLAGS = -lcunit -Wl,-rpath=./
PREFIX = $(HOME)/.local

CUNIT_PATH = /usr/include/CUnit/CUnit.h
CUNIT_VER = $(shell [ -f $(CUNIT_PATH) ] && cat $(CUNIT_PATH) | awk '$$0~/^\#define CU_VERSION/{print $$NF}' || echo "not_found")

.PHONY: all test sample
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

sample: aes sample.c
	$(CC) $(CFLAGS) -o sample sample.c -L./ -laes
	./sample

.PHONY: install uninstall clean
install: aes
	install libaes.so $(PREFIX)/lib/
	ln -sf $(PREFIX)/lib/libaes.so $(HOME)/.local/lib/libaes.so
	install aes.h $(PREFIX)/include/aes.h
	
uninstall:
	rm -f $(PREFIX)/lib/libaes.so $(HOME)/.local/lib/libaes.so $(PREFIX)/include/aes.h

clean:
	rm -f *.o *.so *.a test_case sample
