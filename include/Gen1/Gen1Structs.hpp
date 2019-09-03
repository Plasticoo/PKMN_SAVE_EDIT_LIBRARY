#ifndef __GEN1_STRUCTS_H_
#define __GEN1_STRUCTS_H_

#include "Constants.hpp"

#include <cinttypes>
#include <sys/types.h>

namespace Gen1
{
namespace Structs
{
    struct pkmn_time {
        std::uint8_t hours;
        std::uint8_t maxed;
        std::uint8_t minutes;
        std::uint8_t seconds;
        std::uint8_t frames;
    };

#pragma pack(push, 1)
    struct pkmn_data_party {
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
        std::uint8_t level_opt;
        std::uint16_t max_hp;
        std::uint16_t atk;
        std::uint16_t def;
        std::uint16_t speed;
        std::uint16_t special;
    };
#pragma pack(pop)

#pragma pack(push, 1)
    struct pkmn_data_box {
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
    };
#pragma pack(pop)

    struct pkmn_party {
        std::uint8_t count;
        std::uint8_t species_id[6];
        std::uint8_t unused;
        struct pkmn_data_party pokemon[6];
        std::uint8_t original_trainer_name[6][11];
        std::uint8_t pokemon_name[6][11];
    };

    struct pkmn_box {
        std::uint8_t count;
        std::uint8_t species_id[20];
        std::uint8_t unused;
        struct pkmn_data_box pokemon[20];
        std::uint8_t original_trainer_name[20][11];
        std::uint8_t pokemon_name[20][11];
    };

    struct item {
        std::uint8_t index;
        std::uint8_t count;
    };

    struct items_bag {
        std::uint8_t count;
        struct item item[20];
        std::uint8_t terminator;
    };

    struct items_pc {
        std::uint8_t count;
        struct item item[50];
        std::uint8_t terminator;
    };

    struct gen1_pkmn_file_struct {
        std::uint8_t* player_name;
        std::uint8_t* pokedex_owned;
        std::uint8_t* pokedex_seen;
        struct items_bag* pocket_items;
        std::uint8_t* money;
        std::uint8_t* rival_name;
        std::uint8_t* options;
        std::uint8_t* badges;
        std::uint16_t* player_trainer_id;
        std::uint8_t* pikachu_friendship;
        struct items_pc* pc_item_list;
        std::uint8_t* current_pc_box;
        std::uint8_t* casino_coins;
        struct pkmn_time* time_played;
        std::uint8_t* item_count;
        struct pkmn_data_struct* team_pokemon_list;
        std::uint8_t* current_box_list;
        std::uint8_t* checksum;
        struct pkmn_box* pc_box[12];
        std::uint8_t* file_map;
    };
}
}

#endif
