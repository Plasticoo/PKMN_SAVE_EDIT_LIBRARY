#ifndef _PKMN_GEN1_HPP_
#define _PKMN_GEN1_HPP_

#include "Constants.hpp"
#include "gen1/Gen1Structs.hpp"
#include "IGlobal.hpp"
#include "Rom.hpp"

#include <memory>

//template<class Derived>
struct Gen1 : IGlobal {
    Gen1(std::unique_ptr<Rom>&& r) : m_rom(std::move(r))
    {
		//static_assert(std::is_base_of<Rom, Derived>::value, "Derived not derivative of Rom.");

	}

    auto get_checksum() const -> std::uint8_t override;
    auto calc_checksum() -> std::uint8_t override;

	auto load_file() -> void;

    private:
        std::unique_ptr<Rom> m_rom;

	std::uint8_t *player_name;
    std::uint8_t *pokedex_owned;
    std::uint8_t *pokedex_seen;
    std::uint8_t *money;
    std::uint8_t *rival_name;
    std::uint8_t *options;
    std::uint8_t *badges;
    std::uint8_t *pikachu_friendship;
    std::uint8_t *current_pc_box;
    std::uint8_t *casino_coins;
    std::uint8_t *item_count;
    std::uint8_t *current_box_list;
    std::uint8_t *checksum;

	std::uint16_t *player_trainer_id;

	struct Gen1Structs::items_bag *pocket_items;
	struct Gen1Structs::items_pc *pc_item_list;
	struct Gen1Structs::pkmn_time *time_played;
	struct Gen1Structs::pkmn_data_struct *team_pokemon_list;
    struct Gen1Structs::pkmn_box *pc_box[12];
};

#endif
