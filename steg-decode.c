/*
 * soubor:      steg-decode.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * projekt:     IJC DU1, příklad B)
 * překladač:   gcc 11.2.1
 * datum:       22.3.2022
 */

#include <stdio.h>
#include "ppm.h"
#include "bitset.h"
#include "eratosthenes.h"
#include "error.h"

int main(int argc, char* argv[]) {
    // když není zadán argument
    if(argc != 2) {
        error_exit("steg-decode: Špatné použití programu\n./steg-decode [ppm_obrazek]\n");
    }

    struct ppm *obrazek = ppm_read(argv[1]);

    // když dunkce ppm_read() vrátí NULL, tak error exit
    if(obrazek == NULL) {
        error_exit("steg-decode: Chyba čtení souboru\n");
    }

    // vypočítá prvočísla pro bajty obrázku
    bitset_alloc(prvocisla, obrazek->xsize * obrazek->ysize * 3);
    Eratosthenes(prvocisla);


    char znak = 0; // pomocná proměnná pro znak
    unsigned j = 0; // proměnná pro pozici bitu ve znaku

    for(unsigned long i = 29; i < obrazek->xsize * obrazek->ysize * 3; i++) {
        if(bitset_getbit(prvocisla, i) == 0) {
            // když bity "zaplnily" celý znak...
            if(j == CHAR_BIT) {
                // ...a poslední znak je \0, tak break
                if(znak == '\0') {
                    break;
                // ...jinak putchar(znak)
                } else {
                    putchar(znak);
                    znak = 0;
                    j = 0;
                }
            }
            // přidá bit do znaku na určenou pozici
            znak |= (obrazek->data[i] & 1) << j++;
        }
    }

    // když není řetězec ukončen znakem \0
    if(znak != '\0') {
        bitset_free(prvocisla);
        ppm_free(obrazek);
        putchar('\n');
        error_exit("steg-decode: Řetězec nebyl ukončen znakem \\0\n");
    }

    bitset_free(prvocisla);
    ppm_free(obrazek);
    putchar('\n');
}
