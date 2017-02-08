#ifndef __GEN1_STRUCTS_H_
#define __GEN1_STRUCTS_H_

#include <inttypes.h>

struct gen1_pkmn_data_struct {
    uint8_t *index;
    uint8_t *hp;
    uint8_t *level;
    uint8_t *status;
    uint8_t *type[2];
    uint8_t *catch_item;
    uint8_t *moves[4];
    uint8_t *trainer_id;
    uint8_t *xp;
    uint8_t *hp_ev;
    uint8_t *atk_ev;
    uint8_t *def_ev;
    uint8_t *speed_ev;
    uint8_t *special_ev;
    uint8_t *iv;
    uint8_t *moves_pp[4];
    uint8_t *level_opt;
    uint8_t *max_hp;
    uint8_t *atk;
    uint8_t *def;
    uint8_t *speed;
    uint8_t *special;
};

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

int gen1_save_changes(char* file_name, uint8_t *file_map);
void gen1_set_checksum(struct gen1_pkmn_file_struct *file_struct, uint8_t *file_map);

// functions to get properties of the struct
char* gen1_get_player_name(uint8_t *player_name);

// functions to set properties of the struct
void gen1_set_player_name(struct gen1_pkmn_file_struct *file_struct, char* player_name, int size);

#endif
