
#ifndef __GEN1_STRUCTS_H_
#define __GEN1_STRUCTS_H_

#include <inttypes.h>
#include <sys/types.h>

#define FONT_SIZE 0x100
#define FILE_SIZE 0x8000

#define OPTION_TEXT_SPEED_MASK 0x7
#define OPTION_SOUND_MASK 0x10
#define OPTION_BATTLE_STYLE_MASK 0x40
#define OPTION_BATTLE_EFFECTS_MASK 0x80

enum options {
    OPTION_TEXT_SPEED,
    OPTION_SOUND,
    OPTION_BATTLE_STYLE,
    OPTION_BATTLE_EFFECTS
};

enum badges {
    BOULDER_BADGE,
    CASCADE_BADGE,
    THUNDER_BADGE,
    RAINBOW_BADGE,
    SOUL_BADGE,
    MARSH_BADGE,
    VOLCANO_BADGE,
    EARTH_BADGE
};

// TODO change number of bytes
struct gen1_pkmn_time {
    uint32_t hours;
    uint32_t minutes;
    uint32_t seconds;
};

struct gen1_pkmn_data_struct {
    uint8_t *name;
    uint8_t *ot_name;
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
    struct gen1_pkmn_data_struct *team_pokemon_list[6];
    uint8_t *current_box_list;
    uint8_t *checksum;
    uint8_t *pc_box[12];
    uint8_t *file_map;
};

int gen1_save_changes(struct gen1_pkmn_file_struct *file_struct, char* file_name);
void gen1_set_checksum(struct gen1_pkmn_file_struct *file_struct);

// functions to get properties of the struct
char* gen1_get_name(uint8_t *name);
uint8_t gen1_get_pokedex(uint8_t *pokedex, uint8_t index);
uint32_t gen1_get_money(struct gen1_pkmn_file_struct *file_struct);
uint16_t gen1_get_casino_coins(struct gen1_pkmn_file_struct *file_struct);
uint8_t gen1_get_option(struct gen1_pkmn_file_struct *file_struct, enum options option);
void gen1_get_time_played(struct gen1_pkmn_file_struct *file_struct, struct gen1_pkmn_time *time);
uint8_t gen1_get_badge(struct gen1_pkmn_file_struct *file_struct, enum badges badge);
uint8_t gen1_get_current_pc_box(struct gen1_pkmn_file_struct *file_struct);
struct gen1_pkmn_data_struct *gen1_get_pokemon_in_party(struct gen1_pkmn_file_struct *file_struct, uint8_t index);

// functions to set properties of the struct
void gen1_set_name(uint8_t* name, char* new_name, size_t size);
void gen1_set_pokedex(uint8_t *pokedex, uint8_t index);
void gen1_unset_pokedex(uint8_t *pokedex, uint8_t index);
void gen1_set_money(struct gen1_pkmn_file_struct *file_struct, uint32_t value);
void gen1_set_casino_coins(struct gen1_pkmn_file_struct *file_struct, uint16_t value);
void gen1_set_option(struct gen1_pkmn_file_struct *file_struct, enum options option);
void gen1_set_time_played(struct gen1_pkmn_file_struct *file_struct, struct gen1_pkmn_time *time);
void gen1_set_badge(struct gen1_pkmn_file_struct *file_struct, enum badges badge);
void gen1_set_current_pc_box(struct gen1_pkmn_file_struct *file_struct, uint8_t index);

// others
uint8_t gen1_get_number_pkmn_party(struct gen1_pkmn_file_struct *file_struct);

#endif
