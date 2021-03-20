// eratosthenes.c
// Solution of IJC-DU1, exercise a), 5th March 2021
// Author: Michal Šmahel, FIT
// Compiler: gcc 10.2.1

#include <math.h>
#include "eratosthenes.h"

void eratosthenes(bitset_t bit_array) {
    bitset_setbit(bit_array, 0, 1);
    bitset_setbit(bit_array, 1, 1);

    for (unsigned long i = 2; i <= (unsigned long)sqrt((double)bitset_size(bit_array)); i++) {
        if (bitset_getbit(bit_array, i) == 0) {
            for (unsigned long n = 2; (n * i) < bitset_size(bit_array); n++) {
                bitset_setbit(bit_array, n * i, 1);
            }
        }
    }
}
