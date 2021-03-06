// bitset.h
// Solution of IJC-DU1, exercise a), 5th March 2021
// Author: Michal Šmahel, FIT
// Compiler: gcc 10.2.1

#ifndef IJC_1_HOMEWORK_BITSET_H
#define IJC_1_HOMEWORK_BITSET_H

#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "error.h"

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;

// Counts how many unsigned longs is needed for storing some bits
#define bitset_bits2ul(bits) \
        bits / (sizeof(unsigned long) * CHAR_BIT) + ((bits % (sizeof(unsigned long) * 8)) == 0 ? 0 : 1)

#define bitset_create(array_name, size) \
        static_assert(size > 0 && (int)size == size, "bitset_create: Velikost pole musí být kladné celé číslo"); \
        /* + 1 - the first index is reserved for number of stored bits */ \
        unsigned long array_name[bitset_bits2ul(size) + 1] = {0}; \
        array_name[0] = size

#define bitset_alloc(array_name, size) \
        static_assert(size > 0 && (int)size == size, "bitset_alloc: Velikost pole musí být kladné celé číslo"); \
        static_assert(size <= 200000000, "bitset_alloc: Do pole lze vložit maximálně 200 * 10^6 bitů"); \
        unsigned long *array_name; \
        /* + 1 - the first index is reserved for number of stored bits */ \
        if ((array_name = malloc(sizeof(unsigned long) * (bitset_bits2ul(size) + 1))) == NULL) { \
            error_exit("bitset_alloc: Chyba alokace paměti"); \
        } \
        memset(array_name, 0, sizeof(unsigned long) * (bitset_bits2ul(size) + 1)); \
        array_name[0] = size

#ifndef USE_INLINE
    #define bitset_free(array_name) free(array_name)

    #define bitset_size(array_name) array_name[0]

    #define bitset_setbit(array_name, index, expression) \
        if (index >= array_name[0]) { \
            error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", index, array_name[0] - 1); \
        } \
        /* + 1 - the first index is reserved for number of stored bits */ \
        array_name[index / sizeof(unsigned long) + 1] = ( \
            expression == 0 \
                ? array_name[index / sizeof(unsigned long) + 1] & (~(1 << index % sizeof(unsigned long))) \
                : array_name[index / sizeof(unsigned long) + 1] | (1 << index % sizeof(unsigned long)) \
        )

    #define bitset_getbit(array_name, index) \
        /* + 1 - the first index is reserved for number of stored bits */ \
        ( \
        index < array_name[0] \
            ? (array_name[index / sizeof(unsigned long) + 1] >> index % sizeof(unsigned long)) & 1 \
            : (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", index, array_name[0] - 1), 0) \
        )
#else
    inline void bitset_free(bitset_t array_name) {
        free(array_name);
    }

    inline unsigned long bitset_size(bitset_t array_name) {
        return array_name[0];
    }

    inline void bitset_setbit(bitset_t array_name, bitset_index_t index, int expression) {
        if (index >= array_name[0] - 1) {
            error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", index, array_name[0] - 1);
        }
        array_name[index / sizeof(unsigned long) + 1] = (
            expression == 0
                ? array_name[index / sizeof(unsigned long) + 1] & (~(1 << index % sizeof(unsigned long)))
                : array_name[index / sizeof(unsigned long) + 1] | (1 << index % sizeof(unsigned long))
        );
    }

    inline unsigned long bitset_getbit(bitset_t array_name, bitset_index_t index) {
        return (
            index < array_name[0]
                ? (array_name[index / sizeof(unsigned long) + 1] >> index % sizeof(unsigned long)) & 1
                : (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", index, (unsigned long)array_name[0] - 1), 0)
        );
    }
#endif

#endif //IJC_1_HOMEWORK_BITSET_H
