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
#define bitset_bits2ul(bits)                                                                                           \
        (bits) / (sizeof(unsigned long) * CHAR_BIT) + (((bits) % (sizeof(unsigned long) * 8)) == 0 ? 0 : 1)

// Counts index in bitset array from bit position wanted by caller
#define bitset_array_index(position)                                                                                   \
        /* + 1 - the first position is reserved for number of stored bits */                                           \
        ((position) / (sizeof(unsigned long) * CHAR_BIT)) + 1

// Counts bit offset in unsigned long value in bitset array from bit position wanted by caller
#define bitset_bit_offset(position)                                                                                    \
        (position) % (sizeof(unsigned long) * CHAR_BIT)

#define bitset_create(array_name, size)                                                                                \
        static_assert((size) <= 200000000, "bitset_create: Do pole lze vložit maximálně 200 * 10^6 bitů");            \
                                                                                                                       \
        /* + 1 - the first index is reserved for number of stored bits */                                              \
        unsigned long array_name[bitset_bits2ul(size) + 1] = {0, };                                                    \
        array_name[0] = (size)

#define bitset_alloc(array_name, size)                                                                                 \
        assert( ((void)"bitset_alloc: Do pole lze vložit maximálně 200 * 10^6 bitů", (size) <= 200000000) );           \
                                                                                                                       \
        unsigned long *array_name;                                                                                     \
        /* + 1 - the first index is reserved for number of stored bits */                                              \
        if ((array_name = malloc(sizeof(unsigned long) * (bitset_bits2ul(size) + 1))) == NULL) {                       \
            error_exit("bitset_alloc: Chyba alokace paměti.\n");                                                       \
        }                                                                                                              \
        memset(array_name, 0, sizeof(unsigned long) * (bitset_bits2ul(size) + 1));                                     \
        array_name[0] = (size)

#ifndef USE_INLINE
    #define bitset_free(array_name) free(array_name)

    #define bitset_size(array_name) array_name[0]

    #define bitset_setbit(array_name, position, expression)                                                            \
        do {                                                                                                           \
            if ((position) >= array_name[0]) {                                                                         \
                error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", (position), array_name[0] - 1);            \
            }                                                                                                          \
                                                                                                                       \
            if ((expression)) {                                                                                        \
                array_name[bitset_array_index(position)] |= 1UL << bitset_bit_offset(position);                        \
            } else {                                                                                                   \
                array_name[bitset_array_index(position)] &= ~(1UL << bitset_bit_offset(position));                     \
            }                                                                                                          \
        } while(0)

    #define bitset_getbit(array_name, position)                                                                        \
        (                                                                                                              \
        (position) < array_name[0]                                                                                     \
            ? (array_name[bitset_array_index(position)] >> bitset_bit_offset(position)) & 1UL                          \
            : (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", (position), bitset_size(array_name) - 1), 0)\
        )
#else
    inline void bitset_free(bitset_t array_name) {
        free(array_name);
    }

    inline unsigned long bitset_size(bitset_t array_name) {
        return array_name[0];
    }

    inline void bitset_setbit(bitset_t array_name, bitset_index_t position, int expression) {
        if (position >= array_name[0]) {
            error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", position, array_name[0] - 1);
        }

        if (expression) {
            array_name[bitset_array_index(position)] |= 1UL << bitset_bit_offset(position);
        } else {
            array_name[bitset_array_index(position)] &= ~(1UL << bitset_bit_offset(position));
        }
    }

    inline unsigned long bitset_getbit(bitset_t array, bitset_index_t position) {
        return (
            position < array[0]
                ? (array[bitset_array_index(position)] >> bitset_bit_offset(position)) & 1UL
                : (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", position, bitset_size(array) - 1), 0)
        );
    }
#endif

#endif //IJC_1_HOMEWORK_BITSET_H
