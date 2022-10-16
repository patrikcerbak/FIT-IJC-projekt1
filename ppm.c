/*
 * soubor:      ppm.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * projekt:     IJC DU1, příklad B)
 * překladač:   gcc 11.2.1
 * datum:       22.3.2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"
#include "error.h"

struct ppm * ppm_read(const char * filename) {
    FILE * soubor;
    soubor = fopen(filename, "r");

    if(soubor == NULL) {
        warning_msg("ppm: Nepodařilo se otevřít soubor\n");
        return NULL;
    }

    // proměnné na kontrolu hlavičky
    char typ[3];
    unsigned x, y, barva;
    int parametry = fscanf(soubor, "%2s\n%u %u\n%u\n", typ, &x, &y, &barva);

    // hlavička obsahuje špatný počet "věcí"
    if(parametry != 4) {
        warning_msg("ppm: Špatný formát ppm souboru\n");
        fclose(soubor);
        return NULL;
    }

    // kontrola, zda je soubor ve formátu P6 a barvy 0..255
    if(strcmp(typ, "P6") != 0 || barva != 255) {
        warning_msg("ppm: Špatný formát ppm souboru\n");
        fclose(soubor);
        return NULL;
    }

    // kontrola, zda nepřekročil implementační limit
    if(x * y * 3 > LIMIT) {
        warning_msg("ppm: Soubor překračuje velikostní limit: (%d) > (%d)\n", x * y * 3, LIMIT);
        fclose(soubor);
        return NULL;
    }

    // alokování paměti a kontrola, zda proběhlo úspěšně
    struct ppm *obrazek = malloc((x * y * 3) * sizeof(char) + sizeof(struct ppm));
    if(obrazek == NULL) {
        warning_msg("ppm: Chyba při alokaci paměti\n");
        fclose(soubor);
        return NULL;
    }

    obrazek->xsize = x;
    obrazek->ysize = y;

    // čtení binárních dat pomocí funkce fread() 
    fread(obrazek->data, sizeof(char), x * y * 3, soubor);

    fclose(soubor);
    return obrazek;
}

// uvolnění paměti
void ppm_free(struct ppm *p) {
    free(p);
}
