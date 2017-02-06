#include "../../include/gen1/gen1_funcs.h"
#include "../../include/gen1/gen1_defines.h"

#define CHECKSUM_INIT_OFFSET 0x2598
#define CHECKSUM_END_OFFSET  0x3522

#define FILE_OPEN_ERR 1
#define FILE_SIZE_ERR 2

#define FILE_SIZE 32768
#define FILE_CONTENTS_SIZE 0x54B4
#define FILE_INIT_ADDRESS 0x2598

// TODO move to general purpose c file
// that works for any gen
long get_file_size(FILE* f) {
    long _s;

    fseek(f, 0L, SEEK_END);
    _s = ftell(f);

    return _s;
}

FILE* _fopen(char* file_name, int* errn) {
    FILE* f;

    if ((f = fopen(file_name, "r")) == NULL) {
        *errn = FILE_OPEN_ERR;
        return NULL;
    }

    if (get_file_size(f) != 32768) {
        fclose(f);

        *errn = FILE_SIZE_ERR;
        return NULL;
    }

    return f;
}

// TODO change 'file_name'
uint8_t gen1_checksum(FILE* file_name) {
    int i;

    uint8_t checksum = 0;
    uint8_t byte;

    fseek(file_name, CHECKSUM_INIT_OFFSET, SEEK_SET);

    for (i = 0; i <= CHECKSUM_END_OFFSET - CHECKSUM_INIT_OFFSET; i++) {
        fread(&byte, 1, 1, file_name);
        checksum += byte;
    }

    return ~checksum;
}

// TODO Make it so the user can do something like
// file_map = load_file(f);
void load_file(FILE* f, uint8_t *file_map) {
    int i;

    for (i = 0; i < FILE_SIZE; i++) {
        fread(&file_map[i], 1, 1, f);
    }
}

// TODO Create function to print hex of file contents
void gen1_load_file(struct gen1_pkmn_file_struct* file_struct, uint8_t *file_map) {
    file_struct->player_name = &file_map[PLAYER_NAME_ADDRESS];
    file_struct->pokedex_owned = &file_map[POKEDEX_OWNED_ADDRESS];
    file_struct->pokedex_seen = &file_map[POKEDEX_SEEN_ADDRESS];
    file_struct->pocket_item_list = &file_map[POCKET_ITEM_LIST_ADDRESS];
    file_struct->money = &file_map[MONEY_ADDRESS];
    file_struct->rival_name = &file_map[RIVAL_NAME_ADDRESS];
    file_struct->options = &file_map[OPTIONS_ADDRESS];
    file_struct->badges = &file_map[BADGES_ADDRESS];
    file_struct->player_trainer_id = &file_map[PLAYER_TRAINER_ID_ADDRESS];
    file_struct->pikachu_friendship = &file_map[PIKACHU_FRIENDSHIP_ADDRESS];
    file_struct->pc_item_list = &file_map[PC_ITEM_LIST_ADDRESS];
    file_struct->current_pc_box = &file_map[CURRENT_PC_BOX_ADDRESS];
    file_struct->casino_coins = &file_map[CASINO_COINS_ADDRESS];
    file_struct->time_played = &file_map[TIME_PLAYED_ADDRESS];
    file_struct->team_pokemon_list = &file_map[TEAM_POKEMON_LIST_ADDRESS];
    file_struct->current_box_list = &file_map[CURRENT_BOX_POKEMON_LIST_ADDRESS];
    file_struct->checksum = &file_map[CHECKSUM_ADDRESS];
	// TODO Fix PC_BOX_1_POKEMON_LIST name (add ADDRESS)
    // TODO file_struct->pc_box = &file_map[PC_BOX_1_POKEMON_LIST];
}
