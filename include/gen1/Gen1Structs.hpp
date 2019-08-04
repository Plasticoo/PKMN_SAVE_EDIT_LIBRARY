#ifndef __GEN1_STRUCTS_H_
#define __GEN1_STRUCTS_H_

#include <cinttypes>
#include <sys/types.h>

#include "Constants.hpp"

namespace Gen1
{
struct gen1_pkmn_time {
    std::uint16_t hours;
    std::uint8_t minutes;
    std::uint8_t seconds;
};

struct gen1_pkmn_data_struct {
    std::uint8_t name;
    std::uint8_t ot_name;
    std::uint8_t index;
    std::uint16_t hp;
    std::uint8_t level;
    std::uint8_t status;
    std::uint8_t type[2];
    std::uint8_t catch_item;
    std::uint8_t moves[4];
    std::uint16_t trainer_id;
    std::uint8_t xp[3];
    std::uint16_t hp_ev;
    std::uint16_t atk_ev;
    std::uint16_t def_ev;
    std::uint16_t speed_ev;
    std::uint16_t special_ev;
    std::uint16_t iv;
    std::uint8_t moves_pp[4];
    // these are not exactly needed.. ?
    std::uint8_t level_opt;
    std::uint16_t max_hp;
    std::uint16_t atk;
    std::uint16_t def;
    std::uint16_t speed;
    std::uint16_t special;
};

struct gen1_pkmn_box {
    struct gen1_pkmn_data_struct* pokemon_list[C::GEN1::SIZES::BOX];
};

struct gen1_item {
    std::uint8_t index;
    std::uint8_t count;
};

struct gen1_items_bag {
    std::uint8_t count;
    struct gen1_item item[20];
    std::uint8_t terminator;
};

struct gen1_items_pc {
    std::uint8_t count;
    struct gen1_item item[50];
    std::uint8_t terminator;
};

struct gen1_pkmn_file_struct {
    std::uint8_t* player_name;
    std::uint8_t* pokedex_owned;
    std::uint8_t* pokedex_seen;
    struct gen1_items_bag* pocket_items;
    std::uint8_t* money;
    std::uint8_t* rival_name;
    std::uint8_t* options;
    std::uint8_t* badges;
    std::uint16_t* player_trainer_id;
    std::uint8_t* pikachu_friendship;
    struct gen1_items_pc* pc_item_list;
    std::uint8_t* current_pc_box;
    std::uint8_t* casino_coins;
    struct gen1_pkmn_time* time_played;
    std::uint8_t* item_count;
    struct gen1_pkmn_data_struct* team_pokemon_list;
    std::uint8_t* current_box_list;
    std::uint8_t* checksum;
    struct gen1_pkmn_box* pc_box[12];
    std::uint8_t* file_map;
};

}

int gen1_save_changes(struct gen1_pkmn_file_struct* file_struct,
                      char* file_name);
void gen1_set_checksum(struct gen1_pkmn_file_struct* file_struct);

// functions to get properties of the struct
char* gen1_get_name(std::uint8_t* name);
std::uint8_t gen1_get_pokedex(std::uint8_t* pokedex, std::uint8_t index);
std::uint32_t gen1_get_money(std::uint8_t* money);
std::uint16_t gen1_get_casino_coins(std::uint8_t* casino_coins);
std::uint8_t gen1_get_option(std::uint8_t* options, std::uint8_t flag);
void gen1_get_time_played(struct gen1_pkmn_time* time,
                          struct gen1_pkmn_time* dest);
std::uint8_t gen1_get_badge(std::uint8_t* badges, enum badges badge);
std::uint8_t gen1_get_current_pc_box(std::uint8_t* current_pc_box);
struct gen1_pkmn_data_struct*
gen1_get_pokemon_in_party(struct gen1_pkmn_data_struct* pokemon_party,
                          std::uint8_t index);
struct gen1_pkmn_data_struct*
gen1_get_pokemon_in_box(struct gen1_pkmn_box* pc_box[], std::uint8_t box_index,
                        std::uint8_t pkmn_index);
std::uint8_t gen1_get_pikachu_friendship(std::uint8_t* pikachu_friendship);

// functions to set properties of the struct
void gen1_set_name(std::uint8_t* name, char* new_name, size_t size);
void gen1_set_pokedex(std::uint8_t* pokedex, std::uint8_t index);
void gen1_unset_pokedex(std::uint8_t* pokedex, std::uint8_t index);
void gen1_set_money(std::uint8_t* money, std::uint32_t value);
void gen1_set_casino_coins(std::uint8_t* casino_coins, std::uint16_t value);
void gen1_set_option(std::uint8_t* options, std::uint8_t option);
void gen1_set_time_played(struct gen1_pkmn_time* time, std::uint16_t hours,
                          std::uint8_t minutes, std::uint8_t seconds);
void gen1_set_badge(std::uint8_t* badges, enum badges badge);
void gen1_set_current_pc_box(std::uint8_t* current_pc_box, std::uint8_t index);
void gen1_set_pokemon(struct gen1_pkmn_data_struct* pkmn_data,
                      struct gen1_pkmn_data_struct pkmn_new);

void gen1_set_pikachu_friendship(std::uint8_t* pikachu_friendship,
                                 std::uint8_t value);

// others
std::uint8_t gen1_get_number_pkmn_party(std::uint8_t* file_map);
std::uint8_t gen1_get_pokedex_numbers(std::uint8_t* pokedex);
std::uint8_t gen1_get_item_pocket_count(std::uint8_t* file_map);
std::uint8_t gen1_get_item_box_count(std::uint8_t* file_map);

// items
struct gen1_item* gen1_get_item_bag(struct gen1_items_bag* bag,
                                    std::uint8_t index);
struct gen1_item* gen1_get_item_pc(struct gen1_items_pc* pc,
                                   std::uint8_t index);
void gen1_set_item_bag(struct gen1_item* items, std::uint8_t index,
                       std::uint8_t item, std::uint8_t count);
void gen1_set_item_pc(struct gen1_item* items, std::uint8_t index,
                      std::uint8_t item, std::uint8_t count);

#endif
