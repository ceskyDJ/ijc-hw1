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
CFLAGS=-std=c11 -pedantic -Wall -lm -O2

.PHONY: all dep run pack clean

# make
all: dep primes primes-i steg-decode

# Automatic compilation .c and .h to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
%-i.o: %.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c $< -o $@

## ## ##
# Dependencies
dep:
	$(CC) -MM *.c | sed 'p; s/\.o/-i.o/' > dep.list

-include dep.list
## ## ##

# Linking .o files into final binaries
primes: bitset.o eratosthenes.o error.o primes.o
	$(CC) $(CFLAGS) bitset.o eratosthenes.o error.o primes.o -o primes
primes-i: bitset-i.o eratosthenes-i.o error-i.o primes-i.o
	$(CC) $(CFLAGS) -DUSE_INLINE bitset-i.o eratosthenes-i.o error-i.o primes-i.o -o primes-i
steg-decode: bitset.o eratosthenes.o error.o ppm.o steg-decode.o
	$(CC) $(CFLAGS) bitset.o eratosthenes.o error.o ppm.o steg-decode.o -o steg-decode

# make run
run: primes primes-i
	chmod +x primes primes-i
	ulimit -s 65535 && ./primes
	ulimit -s 65535 && ./primes-i

# make pack
pack:
	zip xsmahe01.zip *.c *.h Makefile

# make clean
clean:
	rm -f primes primes-i steg-decode xsmahe01.zip *.o dep.list