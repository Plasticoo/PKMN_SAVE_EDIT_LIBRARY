#ifndef _PKMN_GEN1_HPP_
#define _PKMN_GEN1_HPP_

#include "Constants.hpp"
#include "IGlobal.hpp"
#include "Rom/RomInterface.hpp"
#include "Utils.hpp"
#include "Gen1/Enums.hpp"
#include "Gen1/Structs.hpp"

#include <fstream>
#include <memory>

//template<class Derived>
namespace Gen1 {
struct Gen1: IGlobal {
	Gen1(std::unique_ptr<Rom32kb>&& r) :
	    m_rom(std::move(r))
	{
		this->load_file();
	}

	auto get_checksum() const -> std::uint8_t override;
	auto calc_checksum() const -> std::uint8_t override;
	auto set_checksum() -> void;

	auto load_file() -> void;
	auto save_changes(std::filesystem::path const& file_name) const -> bool;

	auto get_player_name() const -> std::string;
	auto set_player_name(std::string const& name) -> void;

	auto get_rival_name() const -> std::string;
	auto set_rival_name(std::string const& name) -> void;

	auto get_pokedex_owned(std::uint8_t const index) const -> bool;
	auto set_pokedex_owned(std::uint8_t const index, bool const owned) -> void;

	auto get_pokedex_seen(std::uint8_t const index) const -> bool;
	auto set_pokedex_seen(std::uint8_t const index, bool const seen) -> void;

	auto get_money() const -> std::uint32_t;
	auto set_money(std::uint32_t const value) -> void;

	auto get_casino_coins() const -> std::uint16_t;
	auto set_casino_coins(std::uint16_t const value) -> void;

	auto get_time_played(struct Structs::pkmn_time* dest) const -> void;
	auto set_time_played(std::uint8_t const hours, std::uint8_t const minutes, std::uint8_t const seconds, std::uint8_t const frames) -> void;

	auto get_current_pc_box() const -> std::uint8_t;
	auto set_current_pc_box(std::uint8_t const index) -> void;

	auto get_badge(enum Enums::badges const badge) const -> std::uint8_t;
	auto set_badge(enum Enums::badges const badge) -> void;

	auto get_option(enum Enums::options const flag) const -> std::uint8_t;
	auto set_option(enum Enums::options const flag) -> void;

	auto get_pikachu_friendship() const -> std::uint8_t;
	auto set_pikachu_friendship(std::uint8_t const value) -> void;

	auto get_item_bag_count() const -> std::uint8_t;
	auto get_item_bag(std::uint8_t const index) const -> struct Structs::item*;
	auto set_item_bag(struct Structs::item* items, std::uint8_t const index, std::uint8_t const item, std::uint8_t const count) -> void;

	auto get_item_pc_count() const -> std::uint8_t;
	auto get_item_pc(std::uint8_t const index) const -> struct Structs::item*;
	auto set_item_pc(struct Structs::item* items, std::uint8_t const index, std::uint8_t const item, std::uint8_t const count) -> void;

	auto get_pokemon_party() const -> struct Structs::pkmn_party*;
	auto get_pokemon_in_party(std::uint8_t index) const -> struct Structs::pkmn_data_party*;
	auto get_pokemon_in_party_trainer_name(std::uint8_t index) const -> std::string;
	auto get_pokemon_in_party_name(std::uint8_t index) const -> std::string;

	auto get_current_pc_box_list() const -> struct Structs::pkmn_box*;
	auto get_pokemon_in_current_box(std::uint8_t index) const -> struct Structs::pkmn_data_box*;
	auto get_pokemon_in_current_box_name(std::uint8_t index) const -> std::string;

	auto get_pokemon_box(std::uint8_t box) const -> struct Structs::pkmn_box*;
	auto get_pokemon_in_box(std::uint8_t box, std::uint8_t index) const -> struct Structs::pkmn_data_box*;
	auto get_pokemon_in_box_trainer_name(std::uint8_t box, std::uint8_t index) const -> std::string;
	auto get_pokemon_in_box_name(std::uint8_t box, std::uint8_t index) const -> std::string;

	auto get_character_code(std::uint8_t const c) const -> std::uint8_t;

  private:
	std::unique_ptr<Rom32kb> m_rom;

	std::uint8_t* player_name;
	std::uint8_t* pokedex_owned;
	std::uint8_t* pokedex_seen;
	std::uint8_t* money;
	std::uint8_t* rival_name;
	std::uint8_t* options;
	std::uint8_t* badges;
	std::uint8_t* pikachu_friendship;
	std::uint8_t* current_pc_box;
	std::uint8_t* casino_coins;
	std::uint8_t* item_count;
	std::uint8_t* checksum;

	std::uint16_t* player_trainer_id;

	struct Structs::items_bag* pocket_item_list;
	struct Structs::items_pc* pc_item_list;
	struct Structs::pkmn_time* time_played;
	struct Structs::pkmn_party* team_pokemon_list;
	struct Structs::pkmn_box* current_box_list;
	struct Structs::pkmn_box* pc_box[12];
};
}

#endif
