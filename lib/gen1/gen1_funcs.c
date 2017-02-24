#include "../../include/gen1/gen1_funcs.h"
#include "../../include/gen1/gen1_defines.h"

#include <stdlib.h>

#define CHECKSUM_INIT_OFFSET 0x2598
#define CHECKSUM_END_OFFSET  0x3522

#define FILE_OPEN_ERR 1
#define FILE_SIZE_ERR 2

#define FILE_SIZE 0x8000
#define FILE_CONTENTS_SIZE 0x54B4
#define FILE_INIT_ADDRESS 0x2598

// TODO move to general purpose c file
// that works for any gen
long get_file_size(FILE* f) {
    long _s;

    fseek(f, 0L, SEEK_END);
    _s = ftell(f);
    fseek(f, 0L, SEEK_END);

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

uint8_t gen1_checksum_file(FILE* f) {
    int i;

    uint8_t checksum = 0;
    uint8_t byte;

    fseek(f, CHECKSUM_INIT_OFFSET, SEEK_SET);

    for (i = 0; i <= CHECKSUM_END_OFFSET - CHECKSUM_INIT_OFFSET; i++) {
        fread(&byte, 1, 1, f);
        checksum += byte;
    }

    return ~checksum;
}

uint8_t gen1_checksum_map(uint8_t *file_map) {
    int i;

    uint8_t checksum = 0;

    for (i = CHECKSUM_INIT_OFFSET; i <= CHECKSUM_END_OFFSET; i++) {
        checksum += file_map[i];
    }

    return ~checksum;
}

uint8_t* load_file(FILE* f) {
    int i;

    uint8_t* file_map = calloc(FILE_SIZE, sizeof(uint8_t));

    fseek(f, 0L, SEEK_SET);

    for (i = 0; i < FILE_SIZE; i++) {
        fread(&file_map[i], 1, 1, f);
    }

    return file_map;
}

// TODO Create function to print hex of file contents
void gen1_load_file(struct gen1_pkmn_file_struct* file_struct) {
    uint8_t  i;
    uint32_t pokemon_list_offset = TEAM_POKEMON_LIST_ADDRESS;
    uint32_t pokemon_list_data_offset = TEAM_POKEMON_LIST_ADDRESS + 0x8;
    uint32_t pokemon_ot_name_offset = 0x0110;
    uint32_t pokemon_name_offset = 0x0152;

    file_struct->player_name = &file_struct->file_map[PLAYER_NAME_ADDRESS];
    file_struct->pokedex_owned = &file_struct->file_map[POKEDEX_OWNED_ADDRESS];
    file_struct->pokedex_seen = &file_struct->file_map[POKEDEX_SEEN_ADDRESS];
    file_struct->pocket_item_list = &file_struct->file_map[POCKET_ITEM_LIST_ADDRESS];
    file_struct->money = &file_struct->file_map[MONEY_ADDRESS];
    file_struct->rival_name = &file_struct->file_map[RIVAL_NAME_ADDRESS];
    file_struct->options = &file_struct->file_map[OPTIONS_ADDRESS];
    file_struct->badges = &file_struct->file_map[BADGES_ADDRESS];
    file_struct->player_trainer_id = &file_struct->file_map[PLAYER_TRAINER_ID_ADDRESS];
    file_struct->pikachu_friendship = &file_struct->file_map[PIKACHU_FRIENDSHIP_ADDRESS];
    file_struct->pc_item_list = &file_struct->file_map[PC_ITEM_LIST_ADDRESS];
    file_struct->current_pc_box = &file_struct->file_map[CURRENT_PC_BOX_ADDRESS];
    file_struct->casino_coins = &file_struct->file_map[CASINO_COINS_ADDRESS];
    file_struct->time_played = &file_struct->file_map[TIME_PLAYED_ADDRESS];
    file_struct->current_box_list = &file_struct->file_map[CURRENT_BOX_POKEMON_LIST_ADDRESS];
    file_struct->checksum = &file_struct->file_map[CHECKSUM_ADDRESS];
	// TODO Fix PC_BOX_1_POKEMON_LIST name (add ADDRESS)
    // TODO file_struct->pc_box = &file_map[PC_BOX_1_POKEMON_LIST];

    // load pokemon party
    for (i = 0; i < 6; i++) {
        file_struct->team_pokemon_list[i]              = calloc(1, sizeof(struct gen1_pkmn_data_struct));

        file_struct->team_pokemon_list[i]->name        = &file_struct->file_map[pokemon_list_offset + pokemon_name_offset];
        file_struct->team_pokemon_list[i]->ot_name     = &file_struct->file_map[pokemon_list_offset + pokemon_ot_name_offset];
        file_struct->team_pokemon_list[i]->index       = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + INDEX_NR_SPECIES_OFFSET];
        file_struct->team_pokemon_list[i]->hp          = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + CURRENT_HP_OFFSET];
        file_struct->team_pokemon_list[i]->level       = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + LEVEL_OFFSET];
        file_struct->team_pokemon_list[i]->status      = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + STATUS_CONDITION_OFFSET];
        file_struct->team_pokemon_list[i]->type[0]     = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + TYPE_1_OFFSET];
        file_struct->team_pokemon_list[i]->type[1]     = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + TYPE_2_OFFSET];
        file_struct->team_pokemon_list[i]->catch_item  = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + CATCH_ITEM_OFFSET];
        file_struct->team_pokemon_list[i]->moves[0]    = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_1_OFFSET];
        file_struct->team_pokemon_list[i]->moves[1]    = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_2_OFFSET];
        file_struct->team_pokemon_list[i]->moves[2]    = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_3_OFFSET];
        file_struct->team_pokemon_list[i]->moves[3]    = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_4_OFFSET];
        file_struct->team_pokemon_list[i]->trainer_id  = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + TRAINER_ID_OFFSET];
        file_struct->team_pokemon_list[i]->xp          = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + XP_POINTS_OFFSET];
        file_struct->team_pokemon_list[i]->hp_ev       = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + HP_EV_OFFSET];
        file_struct->team_pokemon_list[i]->atk_ev      = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + ATTACK_EV_OFFSET];
        file_struct->team_pokemon_list[i]->def_ev      = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + DEFENSE_EV_OFFSET];
        file_struct->team_pokemon_list[i]->speed_ev    = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + SPEED_EV_OFFSET];
        file_struct->team_pokemon_list[i]->special_ev  = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + SPECIAL_EV_OFFSET];
        file_struct->team_pokemon_list[i]->iv          = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + IV_OFFSET];
        file_struct->team_pokemon_list[i]->moves_pp[0] = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_1_PP_OFFSET];
        file_struct->team_pokemon_list[i]->moves_pp[1] = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_2_PP_OFFSET];
        file_struct->team_pokemon_list[i]->moves_pp[2] = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_3_PP_OFFSET];
        file_struct->team_pokemon_list[i]->moves_pp[3] = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_4_PP_OFFSET];
        file_struct->team_pokemon_list[i]->level_opt   = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + LEVEL_OPT_OFFSET];
        file_struct->team_pokemon_list[i]->max_hp      = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MAX_HP_OFFSET];
        file_struct->team_pokemon_list[i]->atk         = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + ATTACK_OFFSET];
        file_struct->team_pokemon_list[i]->def         = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + DEFENSE_OFFSET];
        file_struct->team_pokemon_list[i]->speed       = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + SPEED_OFFSET];
        file_struct->team_pokemon_list[i]->special     = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + SPECIAL_OFFSET];
    }
}
