// error.h
// Solution of IJC-DU1, exercise b), 5th March 2021
// Author: Michal Šmahel, FIT
// Compiler: gcc 10.2.1

#ifndef IJC_1_HOMEWORK_ERROR_H
#define IJC_1_HOMEWORK_ERROR_H

/**
 * Writes warning message to the standard error output
 * @param fmt Formatted message string (like the first parameter of printf())
 * @param ... Values for replacing tags in the first parameter
 */
void warning_msg(const char *fmt, ...);
/**
 * Writes error message to the standard error output and stops program with error code
 * @param fmt Formatted message string (like the first parameter of printf())
 * @param ... Values for replacing tags in the first parameter
 */
void error_exit(const char *fmt, ...);

#endif //IJC_1_HOMEWORK_ERROR_H
