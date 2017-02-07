#include "../../include/gen1/gen1_prints.h"
#include "../../include/gen1/gen1_defines.h"

#include <inttypes.h>
#include <stdio.h>

void print_hexmap(uint8_t* array, int size) {
    int i, j;

    for (i = 0; i < size; i+=16) {

        printf("%4X: ", i);

        for (j = 0; j < 16; j++) {
            printf("%2X", array[j]);
        }
    }
}
