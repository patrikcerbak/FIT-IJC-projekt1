/*
 * soubor:      primes.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * projekt:     IJC DU1, příklad A)
 * překladač:   gcc 11.2.1
 * datum:       22.3.2022
 */

#include <stdio.h>
#include <time.h>
#include "bitset.h"
#include "eratosthenes.h"

int main() {
    clock_t start = clock(); // "pustí stopky"

    // vytvoří pole a najde prvočísla
    bitset_create(prvocisla, 300000000);
    Eratosthenes(prvocisla);

    int pocet_prvocisel = 10;
    unsigned long velikost = 300000000;
    while(velikost > 0) {
        // nejdříve prochází deset prvočísel od posledního směrem dolů
        velikost--;
        if(bitset_getbit(prvocisla, velikost) == 0) {
            pocet_prvocisel--;
        }

        // když prošlo všech 10, tak je projde vzestupně zpátky nahoru a postupně vypíše
        if(pocet_prvocisel == 0) {
            while(pocet_prvocisel < 10) {
                if(bitset_getbit(prvocisla, velikost) == 0) {
                    printf("%lu\n", velikost); // když narazí na prvočíslo, tak ho vypíše
                    pocet_prvocisel++; // a přičte k proměnné
                }
                velikost++;
            }
            break;
        }
    }

    // vypíše čas běhu programu
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}
