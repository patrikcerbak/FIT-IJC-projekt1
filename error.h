/*
 * soubor:      error.h
 * autor:       Patrik Čerbák - xcerba00, FIT
 * projekt:     IJC DU1, příklad B)
 * překladač:   gcc 11.2.1
 * datum:       22.3.2022
 */

#ifndef ERROR_H
#define ERROR_H

void warning_msg(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif
