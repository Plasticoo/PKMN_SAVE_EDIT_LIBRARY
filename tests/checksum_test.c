#include "../include/gen1/gen1_funcs.h"

#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE* f;
    int errn;
    uint8_t val;

    if ((f = _fopen("/home/romeu/Documents/Games/GB/pokemon_red.sav", &errn)) == NULL) {
        printf("Error opening file: %d\n", errn);
        exit(EXIT_FAILURE);
    }

    uint8_t calculated = gen1_checksum(f);

    printf("Calculated: %u\n", calculated);

    fseek(f, 0x3523, SEEK_SET);
    fread(&val, 1, 1, f);

    printf("Read from file: %u\n", val);

	fclose(f);

    return 0;
}

