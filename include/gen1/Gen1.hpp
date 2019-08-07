#ifndef _PKMN_GEN1_HPP_
#define _PKMN_GEN1_HPP_

#include "Constants.hpp"
#include "IGlobal.hpp"
#include "Rom.hpp"

#include <memory>

//template<class Derived>
struct Gen1 : IGlobal {
    Gen1(std::unique_ptr<Rom>&& r) : m_rom(std::move(r))
    {
		//static_assert(std::is_base_of<Rom, Derived>::value, "Derived not derivative of Rom.");

	}

    std::uint8_t get_checksum() const override;
    std::uint8_t calc_checksum() override;

	void load_file();

    private:
        std::unique_ptr<Rom> m_rom;

	std::uint8_t *player_name;
    std::uint8_t *pokedex_owned;
    std::uint8_t *pokedex_seen;
    //struct gen1_items_bag *pocket_items;
    std::uint8_t *money;
    std::uint8_t *rival_name;
    std::uint8_t *options;
    std::uint8_t *badges;
	std::uint16_t *player_trainer_id;
    std::uint8_t *pikachu_friendship;
	//struct gen1_items_pc *pc_item_list;
    std::uint8_t *current_pc_box;
    std::uint8_t *casino_coins;
    //struct gen1_pkmn_time *time_played;
    std::uint8_t *item_count;
    //struct gen1_pkmn_data_struct *team_pokemon_list;
    std::uint8_t *current_box_list;
    std::uint8_t *checksum;
    //struct gen1_pkmn_box *pc_box[12];
};

#endif
