// primes.c
// Solution of IJC-DU1, exercise a), 5th March 2021
// Author: Michal Šmahel, FIT
// Compiler: gcc 10.2.1

#include <stdio.h>
#include <time.h>
#include "bitset.h"
#include "eratosthenes.h"

#define PRIMES_TO_WRITE 4

/**
 * Program for counting primes by the Sieve of Eratosthenes algorithm
 * @return Status code (== 0 => ok, != 0 => error)
 */
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

    return 0;
}
