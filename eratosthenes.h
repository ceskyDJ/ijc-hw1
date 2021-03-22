// eratosthenes.h
// Solution of IJC-DU1, exercise a), 5th March 2021
// Author: Michal Šmahel, FIT
// Compiler: gcc 10.2.1

#ifndef IJC_1ST_HOMEWORK_ERATOSTHENES_H
#define IJC_1ST_HOMEWORK_ERATOSTHENES_H

#include "bitset.h"

/**
 * Apply the Sieve of Eratosthenes algorithm to provided bitset
 * @param bit_array Bitset full of 0 - after processing it'll contain primes at bits with value "0"
 */
void eratosthenes(bitset_t bit_array);

#endif //IJC_1ST_HOMEWORK_ERATOSTHENES_H
