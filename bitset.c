/*
 * soubor:      bitset.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * projekt:     IJC DU1, příklad A)
 * překladač:   gcc 11.2.1
 * datum:       22.3.2022
 */

#include "bitset.h"

#ifdef USE_INLINE
    extern unsigned long bitset_size(bitset_t jmeno_pole);
    extern void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, unsigned vyraz);
    extern unsigned long bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);
#endif
