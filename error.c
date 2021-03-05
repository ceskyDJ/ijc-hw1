// error.c
// Solution of IJC-DU1, exercise b), 5th March 2021
// Author: Michal Šmahel, FIT
// Compiler: gcc 10.2.1

#include "error.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Writes warning message to the standard error output
 * @param fmt Formatted message string (like the first parameter of printf())
 * @param ... Values for replacing tags in the first parameter
 */
void warning_msg(const char *fmt, ...) {
    va_list tag_replacements;

    va_start(tag_replacements, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, tag_replacements);
    va_end(tag_replacements);
}

/**
 * Writes error message to the standard error output and stops program with error code
 * @param fmt Formatted message string (like the first parameter of printf())
 * @param ... Values for replacing tags in the first parameter
 */
void error_exit(const char *fmt, ...) {
    va_list tag_replacements;

    va_start(tag_replacements, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, tag_replacements);
    va_end(tag_replacements);

    exit(EXIT_FAILURE);
}
