# Project: IJC - 1st homework
# Author:  Michal Šmahel (xsmahe01)
# Date:    March 2021
#
# Usage:
#   - compile:             make
#   - compile and run all: make run
#   - pack to archive:     make pack
#   - clean:               make clean

CC=gcc
CFLAGS=-g -std=c11 -pedantic -Wall -Wextra -lm -O2

.PHONY: all run pack clean

# make
all: primes primes-i steg-decode

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

## ## ##
eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h error.h
error.o: error.c error.h
ppm.o: ppm.c ppm.h error.h
primes.o: primes.c bitset.h error.h eratosthenes.h
steg-decode.o: steg-decode.c ppm.h error.h bitset.h eratosthenes.h

# Modules for using inline functions
bitset.o: bitset.c bitset.h error.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c $< -o $@
eratosthenes-i.o: eratosthenes.c eratosthenes.h bitset.h error.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c $< -o $@
## ## ##

# Linking .o files into final binaries
primes: eratosthenes.o error.o primes.o
	$(CC) $(CFLAGS) eratosthenes.o error.o primes.o -o primes
primes-i: bitset.o eratosthenes-i.o error.o primes.o
	$(CC) $(CFLAGS) -DUSE_INLINE bitset.o eratosthenes-i.o error.o primes.o -o primes-i
steg-decode: eratosthenes.o error.o ppm.o steg-decode.o
	$(CC) $(CFLAGS) eratosthenes.o error.o ppm.o steg-decode.o -o steg-decode

# make run
run: primes primes-i
	ulimit -s 65535 && ./primes
	ulimit -s 65535 && ./primes-i

# make pack
pack:
	zip xsmahe01.zip *.c *.h Makefile

# make clean
clean:
	rm -f primes primes-i steg-decode xsmahe01.zip *.o