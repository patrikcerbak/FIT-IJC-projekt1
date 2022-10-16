/*
 * soubor:      error.c
 * autor:       Patrik Čerbák - xcerba00, FIT
 * projekt:     IJC DU1, příklad B)
 * překladač:   gcc 11.2.1
 * datum:       22.3.2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "error.h"

// chybová hláška
void warning_msg(const char *fmt, ...) {
    va_list argumenty;

    va_start(argumenty, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, argumenty);
    va_end(argumenty);
}

// chybová hláška + ukončení programu
void error_exit(const char *fmt, ...) {
    va_list argumenty;

    va_start(argumenty, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, argumenty);
    va_end(argumenty);

    exit(1); // konec programu s chybovým kódem 1
}
