// ppm.h
// Řešení IJC-DU1, příklad b), 5. 3. 2021
// Autor: Michal Šmahel, FIT
// Přeloženo: gcc 10.2.1

#ifndef IJC_1_HOMEWORK_PPM_H
#define IJC_1_HOMEWORK_PPM_H

#define MAX_IMG_DATA_SIZE 8000*8000*3

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3*xsize*ysize
};

struct ppm * ppm_read(const char * filename);
void ppm_free(struct ppm *p);

#endif //IJC_1_HOMEWORK_PPM_H
