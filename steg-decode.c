// steg-decode.c
// Solution of IJC-DU1, exercise b), 5th March 2021
// Author: Michal Šmahel, FIT
// Compiler: gcc 10.2.1

#include <stddef.h>
#include <stdbool.h>
#include "ppm.h"
#include "error.h"
#include "bitset.h"
#include "eratosthenes.h"

/**
 * Program for decoding message hidden in PPM image by something like steganography technique
 * @param argc Number of input arguments - 1 explicit is required (path_to_image)
 * @param argv Array of input arguments
 * @return Status code (== 0 => ok, != 0 => error)
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        error_exit("Program vyžaduje jeden argument s cestou k PPM souboru\n");
    }

    // Load PPM image
    struct ppm *image;
    if ((image = ppm_read(argv[1])) == NULL) {
        error_exit("Neplatný formát souboru\n");
    }

    // Get primes using the Sieve of Eratosthenes
    unsigned size = image->xsize * image->ysize * 3;
    bitset_alloc(primes_bitset, size);
    eratosthenes(primes_bitset);

    // Find and write hidden message in loaded PPM image
    unsigned char value = 0;
    unsigned value_index = 0; // Bit index in value
    bool valid_string = false;
    for (unsigned i = 23; i < image->xsize * image->ysize * 3; i++) {
        // Not a prime
        if (bitset_getbit(primes_bitset, i)) {
            continue;
        }

        // Append bit to char in construction
        if (image->data[i] & 1) {
            value |= 1 << value_index;
        }

        // Complete char --> reset iterator-values and write a value
        if (++value_index > 7) {
            printf("%c", value);

            // Stop when end of string found
            if (value == '\0') {
                valid_string = true;
                break;
            } else {
                value = 0;
                value_index = 0;
            }
        }
    }

    // Add line break after message (it hasn't to continue it)
    printf("\n");

    if (!valid_string) {
        error_exit("Zpráva není ukončena znakem '\\0'\n");
    }

    bitset_free(primes_bitset);
    ppm_free(image);

    return 0;
}
