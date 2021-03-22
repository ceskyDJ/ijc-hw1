// ppm.h
// Solution of IJC-DU1, exercise b), 5th March 2021
// Author: Michal Šmahel, FIT
// Compiler: gcc 10.2.1

#ifndef IJC_1_HOMEWORK_PPM_H
#define IJC_1_HOMEWORK_PPM_H

#include <stdio.h>

/**
 * Structure for storing loaded PPM image data and properties
 */
struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bytes, total 3 * xsize * ysize
};

/**
 * Loads image from PPM file
 * @param filename File with the image
 * @return Structure with loaded image (properties and data)
 */
struct ppm * ppm_read(const char * filename);
/**
 * Free allocated structure for storing loaded image
 * @param p Pointer to the structure
 */
void ppm_free(struct ppm *p);

#endif //IJC_1_HOMEWORK_PPM_H
