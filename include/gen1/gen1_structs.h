#ifndef __GEN1_STRUCTS_H_
#define __GEN1_STRUCTS_H_

#include "../defines.h"

#include "gen1_defines.h"
#include "gen1_enums.h"

#include <inttypes.h>
#include <sys/types.h>

#define FONT_SIZE 0x100
#define FILE_SIZE 0x8000

#define BOX_SIZE 20

#define OPTION_TEXT_SPEED_MASK 0x7
#define OPTION_SOUND_MASK 0x30
#define OPTION_BATTLE_STYLE_MASK 0x40
#define OPTION_BATTLE_EFFECTS_MASK 0x80

// TODO FILE include unions
// to enable the possibility of
// changing the bits easier

static const u8 OPTIONS_LOOKUP_TABLE[] = {0x1, 0x2, 0x5, 0x0, 0x0, 0x10, 0x10,
                                          0x20, 0x30, 0x0, 0x40, 0x0, 0x80  };

static const u8 FONT[] =
{'?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // 0
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // 1
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // 2
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // 3
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // 4
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // 5
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // 6
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',' ',   // 7
 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',   // 8
 'Q','R','S','T','U','V','W','X','Y','Z','(',')',':',';','[',']',   // 9
 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p',   // A
 'q','r','s','t','u','v','w','x','y','z','?','?','?','?','?','?',   // B
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // C
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // D
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // E
 '?','?','.','/',',','?','0','1','2','3','4','5','6','7','8','9'};  // F


struct gen1_pkmn_time {
    u16 hours;
    u8 minutes;
    u8 seconds;
};

// TODO apply unions for PPs.
struct gen1_pkmn_data_struct {
    u8 name;
    u8 ot_name;
    u8 index;
    u16 hp;
    u8 level;
    u8 status;
    u8 type[2];
    u8 catch_item;
    u8 moves[4];
    u16 trainer_id;
    u8 xp[3];
    u16 hp_ev;
    u16 atk_ev;
    u16 def_ev;
    u16 speed_ev;
    u16 special_ev;
    u16 iv;
    u8 moves_pp[4];
    // these are not exactly needed.. ?
    u8 level_opt;
    u16 max_hp;
    u16 atk;
    u16 def;
    u16 speed;
    u16 special;
};

struct gen1_pkmn_box {
    struct gen1_pkmn_data_struct *pokemon_list[BOX_SIZE];
};

struct gen1_item {
    u8 index;
    u8 count;
};

struct gen1_pocket_item_list {
    struct gen1_item *item[20];
};

struct gen1_pkmn_file_struct {
    u8 *player_name;
    u8 *pokedex_owned;
    u8 *pokedex_seen;
    struct gen1_pocket_item_list *pocket_items;
    u8 *money;
    u8 *rival_name;
    u8 *options;
    u8 *badges;
    u16 *player_trainer_id;
    u8 *pikachu_friendship;
    u8 *pc_item_list;
    u8 *current_pc_box;
    u8 *casino_coins;
    struct gen1_pkmn_time *time_played;
    u8 *item_count;
    struct gen1_pkmn_data_struct *team_pokemon_list;
    u8 *current_box_list;
    u8 *checksum;
    struct gen1_pkmn_box *pc_box[12];
    u8 *file_map;
};

int gen1_save_changes(struct gen1_pkmn_file_struct *file_struct, char* file_name);
void gen1_set_checksum(struct gen1_pkmn_file_struct *file_struct);

// functions to get properties of the struct
char* gen1_get_name(u8 *name);
u8 gen1_get_pokedex(u8 *pokedex, u8 index);
u32 gen1_get_money(struct gen1_pkmn_file_struct *file_struct);
u16 gen1_get_casino_coins(struct gen1_pkmn_file_struct *file_struct);
u8 gen1_get_option(struct gen1_pkmn_file_struct *file_struct, u8 option);
void gen1_get_time_played(struct gen1_pkmn_file_struct *file_struct, struct gen1_pkmn_time *time);
u8 gen1_get_badge(struct gen1_pkmn_file_struct *file_struct, enum badges badge);
u8 gen1_get_current_pc_box(struct gen1_pkmn_file_struct *file_struct);
struct gen1_pkmn_data_struct gen1_get_pokemon_in_party(struct gen1_pkmn_file_struct *file_struct, u8 index);
struct gen1_pkmn_data_struct *gen1_get_pokemon_in_box(struct gen1_pkmn_file_struct *file_struct, u8 box_index, u8 pkmn_index);
u8 gen1_get_pikachu_friendship(struct gen1_pkmn_file_struct *file_struct);


// functions to set properties of the struct
void gen1_set_name(u8* name, char* new_name, size_t size);
void gen1_set_pokedex(u8 *pokedex, u8 index);
void gen1_unset_pokedex(u8 *pokedex, u8 index);
void gen1_set_money(struct gen1_pkmn_file_struct *file_struct, u32 value);
void gen1_set_casino_coins(struct gen1_pkmn_file_struct *file_struct, u16 value);
void gen1_set_option(struct gen1_pkmn_file_struct *file_struct, u8 option);
void gen1_set_time_played(struct gen1_pkmn_time *time, u16 hours, u8 minutes, u8 seconds);
void gen1_set_badge(struct gen1_pkmn_file_struct *file_struct, enum badges badge);
void gen1_set_current_pc_box(struct gen1_pkmn_file_struct *file_struct, u8 index);
void gen1_set_pokemon_in_party(struct gen1_pkmn_file_struct *file_struct,
                               struct gen1_pkmn_data_struct pkmn_data,
                               u8 index);
void gen1_set_pokemon_in_box(struct gen1_pkmn_file_struct *file_struct,
                               struct gen1_pkmn_data_struct pkmn_data,
                               u8 box_index,
                               u8 pkmn_index);
void gen1_set_pikachu_friendship(struct gen1_pkmn_file_struct *file_struct, u8 value);

// others
u8 gen1_get_number_pkmn_party(struct gen1_pkmn_file_struct *file_struct);
u8 gen1_get_pokedex_numbers(u8 *pokedex);

// TODO create function body
void gen1_add_item(struct gen1_pkmn_file_struct *file_struct, u8 item, u8 count);

#endif
