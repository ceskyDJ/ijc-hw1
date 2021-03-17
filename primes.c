// primes.c
// Solution of IJC-DU1, exercise a), 5th March 2021
// Author: Michal Šmahel, FIT
// Compiler: gcc 10.2.1

#include <stdio.h>
#include <time.h>
#include "bitset.h"
#include "eratosthenes.h"

#ifdef USE_INLINE
extern void bitset_free(bitset_t array_name);
extern unsigned long bitset_size(bitset_t array_name);
extern void bitset_setbit(bitset_t array_name, bitset_index_t position, int expression);
extern unsigned long bitset_getbit(bitset_t array, bitset_index_t position);
#endif

#define PRIMES_TO_WRITE 4

int main(void) {
    clock_t start = clock();

    // Create bit array and apply the Sieve of Eratosthenes
    bitset_create(bit_array, 200000000);
    eratosthenes(bit_array);

    // Get PRIMES_TO_WRITE of found primes (in descending order)
    int n = 0;
    unsigned long primes[PRIMES_TO_WRITE];
    for (unsigned long i = bitset_size(bit_array) - 1; n < PRIMES_TO_WRITE && i > 0; i--) {
        if (bitset_getbit(bit_array, i) == 0) {
            primes[n++] = i;
        }
    }

    // Write number in opposite order (ascending)
    for (int i = PRIMES_TO_WRITE - 1; i >= 0; i--) {
        printf("%lu\n", primes[i]);
    }

    // Measure script execution time
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}
