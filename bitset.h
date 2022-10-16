/*
 * soubor:      bitset.h
 * autor:       Patrik Čerbák - xcerba00, FIT
 * projekt:     IJC DU1, příklad A)
 * překladač:   gcc 11.2.1
 * datum:       22.3.2022
 */

#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "error.h"

#ifndef BITSET_H
#define BITSET_H

typedef unsigned long * bitset_t;
typedef unsigned long bitset_index_t;

// pomocná konstanta - velikost unsigned long v BITECH
#define UL_BITY (unsigned long)(sizeof(unsigned long) * CHAR_BIT) 

// zkontroluje velikost, vytvoří bitové pole a uloží do prvního prvku velikost
#define bitset_create(jmeno_pole, velikost) static_assert(velikost > 0 && velikost < ULONG_MAX, "CHYBA: bitset_create: Špatná velikost pole\n"); \
    unsigned long jmeno_pole[(velikost / UL_BITY) + ((velikost % UL_BITY) != 0 ? 2 : 1)] = {velikost, 0}

// zkontroluje velikost, alokuje bitové pole (pomocí calloc()), zkontroluje, zda se alokovalo a uloží do prvního prvku velikost
#define bitset_alloc(jmeno_pole, velikost) assert(velikost > 0 && velikost < ULONG_MAX); \
    bitset_t jmeno_pole = calloc(((velikost / UL_BITY) + ((velikost % UL_BITY) != 0 ? 2 : 1)), sizeof(unsigned long)); \
    if(jmeno_pole == NULL) { error_exit("bitset_alloc: Chyba alokace paměti\n"); } else { jmeno_pole[0] = velikost; }

// uvolní bitové pole z paměti
#define bitset_free(jmeno_pole) free(jmeno_pole)


// když je definováno USE_INLINE
#ifdef USE_INLINE

    // vráti první prvek pole (velikost)
    inline unsigned long bitset_size(bitset_t jmeno_pole) {
        return jmeno_pole[0];
    }

    // uloží bit na určený index
    inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, unsigned vyraz) {
        // kontrola, zda je index v rámci rozsahu pole (větší než 0 není třeba kontrolovat, protože index je unsigned)
        if(index < bitset_size(jmeno_pole)) {
            // uloží bit podle toho, zda je 1 nebo 0
            if(vyraz) {
                jmeno_pole[index / UL_BITY + 1] |= (1UL << (index % UL_BITY));
            } else {
                jmeno_pole[index / UL_BITY + 1] &= ~(1UL << (index % UL_BITY));
            }
        } else {
            error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole));
        }
    }

    // vrátí bit uložený na daném indexu
    inline unsigned long bitset_getbit(bitset_t jmeno_pole, bitset_index_t index) {
        // kontrola, zda je index v rámci rozsahu pole
        if(index < bitset_size(jmeno_pole)) {
            if(jmeno_pole[index / UL_BITY + 1] & (1UL << (index % UL_BITY))) {
                return 1UL;
            } else {
                return 0UL;
            }
        } else {
            error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole));
            return -1UL;
        }
    }

#else

    // vrátí první prvek pole (velikost)
    #define bitset_size(jmeno_pole) jmeno_pole[0]

    // zkontroluje jestli je index v roszahu, uloží bit na určený index podle toho, zda je 1 nebo 0
    #define bitset_setbit(jmeno_pole, index, vyraz) if((unsigned long)index >= (unsigned long)bitset_size(jmeno_pole)) { \
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole)); } else { \
        (vyraz) ? (jmeno_pole[index / UL_BITY + 1] |= (1UL << (index % UL_BITY))) : (jmeno_pole[index / UL_BITY + 1] &= ~(1UL << (index % UL_BITY))); }

    // zkontroluje jestli je index v roszahu, vrátí bit uložený na daném indexu
    #define bitset_getbit(jmeno_pole, index) ((unsigned long)index >= (unsigned long)bitset_size(jmeno_pole)) ? \
        (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole)), -1UL) : \
        ((jmeno_pole[index / UL_BITY + 1] & (1UL << (index % UL_BITY))) ? 1UL : 0UL)

#endif // USE_INLINE


#endif // BITSET_H
