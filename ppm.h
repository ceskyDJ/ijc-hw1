// ppm.h
// Solution of IJC-DU1, exercise b), 5th March 2021
// Author: Michal Šmahel, FIT
// Compiler: gcc 10.2.1

#ifndef IJC_1_HOMEWORK_PPM_H
#define IJC_1_HOMEWORK_PPM_H

#define MAX_IMG_DATA_SIZE 8000*8000*3

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bytes, total 3*xsize*ysize
};

struct ppm * ppm_read(const char * filename);
void ppm_free(struct ppm *p);

#endif //IJC_1_HOMEWORK_PPM_H
