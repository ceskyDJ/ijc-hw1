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

/**
 * Type of bitset array
 */
typedef unsigned long *bitset_t;
/**
 * Type of array index of bitset array
 */
typedef unsigned long bitset_index_t;

/**
 * Counts how many unsigned longs is needed for storing some bits
 * @param bits Number of bits to be stored in bitset
 */
#define bitset_bits2ul(bits)                                                                                           \
        (bits) / (sizeof(unsigned long) * CHAR_BIT) + (((bits) % (sizeof(unsigned long) * 8)) == 0 ? 0 : 1)

/**
 * Counts index in bitset array from bit position wanted by caller
 * @param position Bit's position in bitset (0..bitset size - 1)
 */
#define bitset_array_index(position)                                                                                   \
        /* + 1 - the first position is reserved for number of stored bits */                                           \
        ((position) / (sizeof(unsigned long) * CHAR_BIT)) + 1

/**
 * Counts bit offset in unsigned long value in bitset array from bit position wanted by caller
 * @param position Bit's position in bitset (0..bitset size - 1)
 */
#define bitset_bit_offset(position)                                                                                    \
        (position) % (sizeof(unsigned long) * CHAR_BIT)

/**
 * Create a new bitset using static memory
 * @param array Name of the bitset (variable name)
 * @param size Size - number of bits that can be stored
 */
#define bitset_create(array, size)                                                                                \
        static_assert((size) <= 200000000, "bitset_create: Do pole lze vložit maximálně 200 * 10^6 bitů");             \
                                                                                                                       \
        /* + 1 - the first index is reserved for number of stored bits */                                              \
        unsigned long array[bitset_bits2ul(size) + 1] = {0, };                                                    \
        array[0] = (size)

/**
 * Creates a new bitset using dynamically allocated memory
 * <b>Needs to be deallocated using bitset_free()!</a>
 * @param array Name of the bitset (variable name)
 * @param size Size - number of bits that can be stored
 */
#define bitset_alloc(array, size)                                                                                 \
        assert( ((void)"bitset_alloc: Do pole lze vložit maximálně 200 * 10^6 bitů", (size) <= 200000000) );           \
                                                                                                                       \
        unsigned long *array;                                                                                     \
        /* + 1 - the first index is reserved for number of stored bits */                                              \
        if ((array = malloc(sizeof(unsigned long) * (bitset_bits2ul(size) + 1))) == NULL) {                       \
            error_exit("bitset_alloc: Chyba alokace paměti.\n");                                                       \
        }                                                                                                              \
        memset(array, 0, sizeof(unsigned long) * (bitset_bits2ul(size) + 1));                                     \
        array[0] = (size)

#ifndef USE_INLINE
    /**
     * Deallocates space allocated for bitset created by bitset_alloc()
     * @param array Name of the bitset (variable name)
     */
    #define bitset_free(array_name) free(array_name)

    /**
     * Returns declared size of bitset
     * @param array
     * @return Number of bits stored in bitset
     */
    #define bitset_size(array_name) array_name[0]

    /**
     * Sets a value of selected bit
     * @param array Name of the bitset (variable name)
     * @param position Bit's position in bitset (0..bitset size - 1) --> bit selection
     * @param expression Result of expression will be set as bit's value (result: == 0 --> "0", != 0 --> "1")
     */
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

    /**
     * Returns value of selected bit
     * @param array Name of the bitset (variable name)
     * @param position Bit's position in bitset (0..bitset size - 1) --> bit selection
     * @return Expression saying a bit value (result: == 0 --> "0", != 0 --> "1")
     */
    #define bitset_getbit(array_name, position)                                                                        \
        (                                                                                                              \
        (position) < array_name[0]                                                                                     \
            ? (array_name[bitset_array_index(position)] >> bitset_bit_offset(position)) & 1UL                          \
            : (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", (position), bitset_size(array_name) - 1), 0)\
        )
#else
    /**
     * Deallocates space allocated for bitset created by bitset_alloc()
     * @param array Name of the bitset (variable name)
     */
    inline void bitset_free(bitset_t array) {
        free(array);
    }

    /**
     * Returns declared size of bitset
     * @param array
     * @return Number of bits stored in bitset
     */
    inline unsigned long bitset_size(bitset_t array) {
        return array[0];
    }

    /**
     * Sets a value of selected bit
     * @param array Name of the bitset (variable name)
     * @param position Bit's position in bitset (0..bitset size - 1) --> bit selection
     * @param expression Result of expression will be set as bit's value (result: == 0 --> "0", != 0 --> "1")
     */
    inline void bitset_setbit(bitset_t array, bitset_index_t position, int expression) {
        if (position >= array[0]) {
            error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", position, array[0] - 1);
        }

        if (expression) {
            array[bitset_array_index(position)] |= 1UL << bitset_bit_offset(position);
        } else {
            array[bitset_array_index(position)] &= ~(1UL << bitset_bit_offset(position));
        }
    }

    /**
     * Returns value of selected bit
     * @param array Name of the bitset (variable name)
     * @param position Bit's position in bitset (0..bitset size - 1) --> bit selection
     * @return Expression saying a bit value (result: == 0 --> "0", != 0 --> "1")
     */
    inline unsigned long bitset_getbit(bitset_t array, bitset_index_t position) {
        return (
            position < array[0]
                ? (array[bitset_array_index(position)] >> bitset_bit_offset(position)) & 1UL
                : (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", position, bitset_size(array) - 1), 0)
        );
    }
#endif

#endif //IJC_1_HOMEWORK_BITSET_H
