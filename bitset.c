// bitset.c
// Solution of IJC-DU1, exercise a), 20th March 2021
// Author: Michal Šmahel, FIT
// Compiler: gcc 10.2.1

#include "bitset.h"

#ifdef USE_INLINE
extern void bitset_free(bitset_t array_name);
extern unsigned long bitset_size(bitset_t array_name);
extern void bitset_setbit(bitset_t array_name, bitset_index_t position, int expression);
extern unsigned long bitset_getbit(bitset_t array, bitset_index_t position);
#endif
