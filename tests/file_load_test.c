#include "../include/gen1/gen1_funcs.h"
#include "../include/gen1/gen1_prints.h"
#include "../include/gen1/gen1_structs.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int errn;
	uint8_t* f_map;

	FILE* f;
    struct gen1_pkmn_file_struct a;

    char* player_name;

	if ((f = _fopen("/home/romeu/Documents/Games/GB/pokemon_red.sav", &errn)) == NULL) {
        printf("Error opening file: %d\n", errn);
        exit(EXIT_FAILURE);
    }

	f_map = load_file(f);
	gen1_load_file(&a, f_map);

    // name tests
    player_name = gen1_get_player_name(a.player_name);
    printf("Player name: %s\n", player_name);

    gen1_set_player_name(&a, "test", 4);
    gen1_save_changes("saved_changes.sav", f_map);

	fclose(f);

    free(f_map);
    free(player_name);

    return 0;
}
