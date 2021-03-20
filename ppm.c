// ppm.c
// Solution of IJC-DU1, exercise b), 5th March 2021
// Author: Michal Šmahel, FIT
// Compiler: gcc 10.2.1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ppm.h"
#include "error.h"

// Max image size = 9999 * 9999 * 3
#define MAX_WIDTH_DIGITS 4
#define MAX_HEIGHT_DIGITS 4
#define MAGIC_NUMBER_LENGTH 2

/**
 * Reads all whitespaces until next non-whitespace char from file
 * @param file File to read from
 * @return 0 for success, 1 for error
 */
int read_whitespaces(FILE *file) {
    int c;
    do {
        if ((c = fgetc(file)) == EOF) {
            return 1;
        }
    } while (isspace(c));

    // Return non-whitespace char back
    ungetc(c, file);

    return 0;
}

/**
 * Reads single unsigned number stored in text form (ASCII digits) from file
 * @param file File to read from
 * @param max_digits Maximum of digits the loaded number can contain
 * @return Value > 0 if number has been read successfully or -1 if error has occurred
 */
int read_stringy_number(FILE *file, int max_digits) {
    int number = 0;

    // Skip whitespace char before number (the first digit, resp.)
    if (read_whitespaces(file) != 0) {
        return -1;
    }

    int c;
    int i = 0;
    while (isdigit(c = fgetc(file)) && i++ < max_digits) {
        number *= 10;
        number += (c - '0');
    }

    // While has ended due to end of file, so
    if (c == EOF) {
        return -1;
    }

    // Return non-digit char back
    ungetc(c, file);

    return number;
}

/**
 * Prepares structure for storing loaded image's properties and data
 * @param file File to read from
 * @return Prepared image structure with defined properties
 */
struct ppm * prepare_structure(FILE *file) {
    // Magic number (definition of the file format) - must be P6
    char magic_number[MAGIC_NUMBER_LENGTH + 1];
    if (fgets(magic_number, MAGIC_NUMBER_LENGTH + 1, file) == NULL || strcmp(magic_number, "P6") != 0) {
        warning_msg("PPM soubor musí být ve formátu PPM Raw (P6)\n");

        return NULL;
    }

    // Image width - 0-MAX_WIDTH_DIGITS
    int width;
    if ((width = read_stringy_number(file, MAX_WIDTH_DIGITS)) < 0) {
        warning_msg("Soubor neobsahuje všechny povinné informace, je příliš malý\n");

        return NULL;
    }

    // Image height - 0-MAX_HEIGHT_DIGITS
    int height;
    if ((height = read_stringy_number(file, MAX_HEIGHT_DIGITS)) < 0) {
        warning_msg("Soubor neobsahuje všechny povinné informace, je příliš malý\n");

        return NULL;
    }

    // Max value of color number - must be 255 (3 digits)
    int max_value;
    if ((max_value = read_stringy_number(file, 3)) < 0 || max_value != 255) {
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
    int c;
    for (unsigned i = 0; i < image->ysize; i++) {
        for (unsigned j = 0; j < image->xsize; j++) {
            if ((c = getc(file)) == EOF) {
                return 1;
            }

            image->data[i * image->xsize + j] = (char)c;
        }
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
    if ((file = fopen(filename, "r")) == NULL) {
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
