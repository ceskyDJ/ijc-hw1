// ppm.c
// Solution of IJC-DU1, exercise b), 5th March 2021
// Author: Michal Šmahel, FIT
// Compiler: gcc 10.2.1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ppm.h"
#include "error.h"

/**
 * Prepares structure for storing loaded image's properties and data
 * @param file File to read from
 * @return Prepared image structure with defined properties
 */
struct ppm * prepare_structure(FILE *file) {
    // Magic number (definition of the file format) - must be P6
    char magic_number[3];
    if (fscanf(file, "%2s", magic_number) == EOF || strcmp(magic_number, "P6") != 0) {
        warning_msg("PPM soubor musí být ve formátu PPM Raw (P6)\n");

        return NULL;
    }

    // Image width - 0-MAX_WIDTH_DIGITS
    int width;
    if (fscanf(file, "%d", &width) == EOF) {
        warning_msg("V souboru není korektně specifikována šířka obrázku\n");

        return NULL;
    }

    // Image height - 0-MAX_HEIGHT_DIGITS
    int height;
    if (fscanf(file, "%d", &height) == EOF) {
        warning_msg("V souboru není korektně specifikována výška obrázku\n");

        return NULL;
    }

    if (width > 8000 || height > 8000) {
        warning_msg("Byla překročena maximální velikost obrázku, která činí 8000x8000 pixelů\n");

        return NULL;
    }

    // Max value of color number - must be 255 (3 digits)
    int max_value;
    if (fscanf(file, "%d", &max_value) == EOF || max_value != 255) {
        warning_msg("PPM soubor musí mít hodnoty barev specifikované jako čísla 0..255\n");

        return NULL;
    }

    // Skip whitespace
    fgetc(file);

    struct ppm *prepared_structure;
    // 3 = number of colors in each pixel (R, G, B => 3)
    if ((prepared_structure = malloc(sizeof(struct ppm) + width * height * 3)) == NULL) {
        fclose(file);
        error_exit("Nebylo možné alokovat paměť pro strukturu s načteným PPM obrázkem\n");
    }

    prepared_structure->xsize = width;
    prepared_structure->ysize = height;

    return prepared_structure;
}

/**
 * Loads image data into its structure
 * @param file File to read from
 * @param image Image structure to modify
 * @return 0 if success or -1 if failure
 */
int load_image_data(FILE *file, struct ppm *image) {
    size_t data_size = image->xsize * image->ysize * 3;
    if (fread(image->data, 1, data_size, file) != data_size) {
        return 1;
    }

    return 0;
}

/**
 * Loads image from PPM file
 * @param filename File with the image
 * @return Structure with loaded image (properties and data)
 */
struct ppm * ppm_read(const char * filename) {
    FILE *file;
    if ((file = fopen(filename, "rb")) == NULL) {
        warning_msg("Zadaný soubor není možné otevřít\n");

        return NULL;
    }

    struct ppm *image;
    if ((image = prepare_structure(file)) == NULL) {
        fclose(file);
        return NULL;
    }

    if (load_image_data(file, image) != 0) {
        warning_msg("Soubor neobsahuje všechna data (liší se od počtu uvedených v hlaviččce)\n");

        fclose(file);
        return NULL;
    }

    fclose(file);

    return image;
}

/**
 * Free allocated structure for storing loaded image
 * @param p Pointer to the structure
 */
void ppm_free(struct ppm *p) {
    free(p);
}
