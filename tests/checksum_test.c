#include "../include/gen1/gen1_funcs.h"

int main(int argc, char *argv[])
{
    FILE* f;
    uint8_t val;

    f = fopen("/home/romeu/Documents/Games/GB/pokemon_red.sav", "r");
    uint8_t calculated = gen1_checksum(f);

    printf("Calculated: %u\n", calculated);

    fseek(f, 0x3523, SEEK_SET);
    fread(&val, 1, 1, f);

    printf("Read from file: %u\n", val);

    return 0;
}

