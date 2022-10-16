/*
 * soubor:      ppm.h
 * autor:       Patrik Čerbák - xcerba00, FIT
 * projekt:     IJC DU1, příklad B)
 * překladač:   gcc 11.2.1
 * datum:       22.3.2022
 */

#ifndef PPM_H
#define PPM_H

// implementační limit (hodnoty zvoleny podle zadání)
#define LIMIT (8000 * 8000 * 3)

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];
};

struct ppm * ppm_read(const char * filename);
void ppm_free(struct ppm *p);

#endif
