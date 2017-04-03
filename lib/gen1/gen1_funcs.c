#include "gen1/gen1.h"

#include <stdlib.h>

u8 gen1_checksum_file(FILE* f)
{
    int i;

    u8 checksum = 0;
    u8 byte;

    fseek(f, CHECKSUM_INIT_OFFSET, SEEK_SET);

    for (i = 0; i <= CHECKSUM_END_OFFSET - CHECKSUM_INIT_OFFSET; i++) {
        fread(&byte, 1, 1, f);
        checksum += byte;
    }

    return ~checksum;
}

u8 gen1_checksum_map(u8 *file_map)
{
    int i;

    u8 checksum = 0;

    for (i = CHECKSUM_INIT_OFFSET; i <= CHECKSUM_END_OFFSET; i++) {
        checksum += file_map[i];
    }

    return ~checksum;
}

u8* load_file(FILE* f)
{
    int i;

    u8* file_map = calloc(FILE_SIZE, sizeof(u8));

    fseek(f, 0L, SEEK_SET);

    for (i = 0; i < FILE_SIZE; i++) {
        fread(&file_map[i], 1, 1, f);
    }

    return file_map;
}

void gen1_load_file(struct gen1_pkmn_file_struct* file_struct, FILE* f)
{
    u8 i;

    file_struct->file_map = load_file(f);

    file_struct->player_name = &file_struct->file_map[PLAYER_NAME_ADDRESS];
    file_struct->pokedex_owned = &file_struct->file_map[POKEDEX_OWNED_ADDRESS];
    file_struct->pokedex_seen = &file_struct->file_map[POKEDEX_SEEN_ADDRESS];
    file_struct->pocket_items = (struct gen1_pocket_item_list*)&file_struct->file_map[POCKET_ITEM_LIST_ADDRESS];
    file_struct->money = &file_struct->file_map[MONEY_ADDRESS];
    file_struct->rival_name = &file_struct->file_map[RIVAL_NAME_ADDRESS];
    file_struct->options = &file_struct->file_map[OPTIONS_ADDRESS];
    file_struct->badges = &file_struct->file_map[BADGES_ADDRESS];
    file_struct->player_trainer_id = (u16*)&file_struct->file_map[PLAYER_TRAINER_ID_ADDRESS];
    file_struct->pikachu_friendship = &file_struct->file_map[PIKACHU_FRIENDSHIP_ADDRESS];
    file_struct->pc_item_list = &file_struct->file_map[PC_ITEM_LIST_ADDRESS];
    file_struct->current_pc_box = &file_struct->file_map[CURRENT_PC_BOX_ADDRESS];
    file_struct->casino_coins = &file_struct->file_map[CASINO_COINS_ADDRESS];
    file_struct->time_played = (struct gen1_pkmn_time*)&file_struct->file_map[TIME_PLAYED_ADDRESS];
    file_struct->current_box_list = &file_struct->file_map[CURRENT_BOX_POKEMON_LIST_ADDRESS];
    file_struct->checksum = &file_struct->file_map[CHECKSUM_ADDRESS];

    file_struct->team_pokemon_list = (struct gen1_pkmn_data_struct*)&file_struct->file_map[TEAM_POKEMON_LIST_ADDRESS];

    // pc boxes
    u16 offset = PC_BOX_1_POKEMON_LIST;
    for(i = 0; i < 12; i++) {
        offset += (sizeof(struct gen1_pkmn_box) * i);
        file_struct->pc_box[i] = (struct gen1_pkmn_box*)&file_struct->file_map[offset];
    }
}
