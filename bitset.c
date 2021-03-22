// bitset.c
// Solution of IJC-DU1, exercise a), 20th March 2021
// Author: Michal Šmahel, FIT
// Compiler: gcc 10.2.1

#include "bitset.h"

#ifdef USE_INLINE
/**
 * Deallocates space allocated for bitset created by bitset_alloc()
 * @param array Name of the bitset (variable name)
 */
extern void bitset_free(bitset_t array);
/**
 * Returns declared size of bitset
 * @param array
 * @return Number of bits stored in bitset
 */
extern unsigned long bitset_size(bitset_t array);
/**
 * Sets a value of selected bit
 * @param array Name of the bitset (variable name)
 * @param position Bit's position in bitset (0..bitset size - 1) --> bit selection
 * @param expression Result of expression will be set as bit's value (result: == 0 --> "0", != 0 --> "1")
 */
extern void bitset_setbit(bitset_t array, bitset_index_t position, int expression);
/**
 * Returns value of selected bit
 * @param array Name of the bitset (variable name)
 * @param position Bit's position in bitset (0..bitset size - 1) --> bit selection
 * @return Expression saying a bit value (result: == 0 --> "0", != 0 --> "1")
 */
extern unsigned long bitset_getbit(bitset_t array, bitset_index_t position);
#endif
