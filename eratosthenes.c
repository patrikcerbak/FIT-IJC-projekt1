/*
 * soubor:      eratosthenes.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * projekt:     IJC DU1, příklad A)
 * překladač:   gcc 11.2.1
 * datum:       22.3.2022
 */

#include <math.h>
#include "eratosthenes.h"
#include "bitset.h"

void Eratosthenes(bitset_t pole) {
    // nastaví 0 a 1 na jedničku - nejsou to prvočísla
    bitset_setbit(pole, 0, 1);
    bitset_setbit(pole, 1, 1);

    unsigned long velikost = bitset_size(pole);
    unsigned long maximum = sqrt(velikost);
    
    for(unsigned long i = 2; i < maximum; i++) {
        // když narazí na prvočíslo, tak nastaví jeho násobky na 1
        if(bitset_getbit(pole, i) == 0) {
            unsigned long j = 2;
            unsigned long nasobek = i * j; // pomocná proměnná pro násobky prvočísla
            while(nasobek < velikost) {
                bitset_setbit(pole, nasobek, 1);
                nasobek = i * ++j;
            }
        }
    }
}
