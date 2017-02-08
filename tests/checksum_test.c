#include "../include/gen1/gen1_funcs.h"

#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE* f;

    int errn;
    uint8_t val;
    uint8_t *file_map;

    if ((f = _fopen("/home/romeu/Documents/Games/GB/pokemon_red.sav", &errn)) == NULL) {
        printf("Error opening file: %d\n", errn);
        exit(EXIT_FAILURE);
    }

    file_map = load_file(f);

    uint8_t calculated = gen1_checksum_file(f);
    uint8_t calculated_map = gen1_checksum_map(file_map);

    printf("Calculated in file: %u\n", calculated);
    printf("Calculated in file map: %u\n", calculated_map);

    fseek(f, 0x3523, SEEK_SET);
    fread(&val, 1, 1, f);

    printf("Read from file: %u\n", val);

	fclose(f);

    return 0;
}

