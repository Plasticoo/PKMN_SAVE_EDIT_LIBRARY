#ifndef __GEN1_STRUCTS_H_
#define __GEN1_STRUCTS_H_

#include <inttypes.h>

// TODO Change uint8_t for the
// respective structure
struct gen1_pkmn_file_struct {
    uint8_t *player_name;
    uint8_t *pokedex_owned;
    uint8_t *pokedex_seen;
    uint8_t *pocket_item_list;
    uint8_t *money;
    uint8_t *rival_name;
    uint8_t *options;
    uint8_t *badges;
    uint8_t *player_trainer_id;
    uint8_t *pikachu_friendship;
    uint8_t *pc_item_list;
    uint8_t *current_pc_box;
    uint8_t *casino_coins;
    uint8_t *time_played;
    uint8_t *team_pokemon_list;
    uint8_t *current_box_list;
    uint8_t *checksum;
    uint8_t *pc_box[12];
};

#endif
