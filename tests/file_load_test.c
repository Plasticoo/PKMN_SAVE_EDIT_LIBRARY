#include "../include/gen1/gen1_funcs.h"
#include "../include/gen1/gen1_prints.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int errn;
	uint8_t* f_map;

	FILE* f;
    struct gen1_pkmn_file_struct a;

	if ((f = _fopen("/home/romeu/Documents/Games/GB/pokemon_red.sav", &errn)) == NULL) {
        printf("Error opening file: %d\n", errn);
        exit(EXIT_FAILURE);
    }

	f_map = load_file(f);
	gen1_load_file(&a, f_map);

	printf("Casino coins: %d\n", a.casino_coins[0]);
    print_hexmap(f_map, 32768);

	fclose(f);
    free(f_map);

    return 0;
}
