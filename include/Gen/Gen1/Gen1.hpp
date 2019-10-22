#ifndef _PKMN_GEN1_HPP_
#define _PKMN_GEN1_HPP_

#include "Constants.hpp"
#include "Gen/Gen1/Enums.hpp"
#include "Gen/Gen1/Structs.hpp"
#include "IGlobal.hpp"
#include "Rom/RomInterface.hpp"
#include "Utils.hpp"

#include <fstream>
#include <memory>

/** @brief Contains Generation I relevant classes, functions and utilities. */
namespace Gen1
{

/** @brief  Generation I class. */
struct Gen1: IGlobal {

	/**
	 *  @brief Gen1 Constructor
	 *  @see Rom32Kb
	 *  @param r Rvalue reference to Rom32Kb.
	 */
    Gen1(std::unique_ptr<Rom32kb>&& r) :
        m_rom(std::move(r))
    {
        this->load_file();
    }

	/**
	 *  @brief Get current checksum.
	 *  @return Relevant byte that represents the checksum.
	 */
    auto get_checksum() const -> std::uint8_t override;

    /**
	 *  @brief Calculates the checksum.
	 *  @return Checksum calculation result.
	 */
    auto calc_checksum() const -> std::uint8_t override;

	/**
	 *  @brief Calculates the checksum and sets the value in the
	 *  relevant Rom byte.
	 */
    auto set_checksum() -> void;

	/**
	 *  @brief Loads Rom information into relevant structs.
	 */
    auto load_file() -> void;

	/**
	 *  @brief Save changes made to Rom information in memory to a file.
	 *
	 *  @param file_name Path to file.
	 *
	 *  @return True if everything worked.
	 */
    auto save_changes(std::filesystem::path const& file_name) const -> bool;

	/**
	 *  @brief Get player name.
	 *  @return Name of the player.
	 */
    auto get_player_name() const -> std::string;

	/**
	 *  @brief Set player name.
	 *  @param name New player name.
	 */
    auto set_player_name(std::string const& name) -> void;

	/**
	 *  @brief Get rival name.
	 *  @return Name of the rival.
	 */
    auto get_rival_name() const -> std::string;

	/**
	 *  @brief Set rival name.
	 *  @param name New rival name.
	 */
    auto set_rival_name(std::string const& name) -> void;

	/**
	 *  @brief Get total of owned Pokemons.
	 *  @return Value of owned Pokemons.
	 */
	auto get_pokedex_owned_total() const -> std::uint8_t;

	/**
	 *  @brief Get information from the Pokedex if Pokemon is owned.
	 *  @param index Pokedex index.
	 *  @return True if Pokemon owned.
	 */
    auto get_pokedex_owned(std::uint8_t const index) const -> bool;

	/**
	 *  @brief Set own status of Pokemons in Pokedex.
	 *  @param index Pokedex index.
	 *  @param owned Own status.
	 */
    auto set_pokedex_owned(std::uint8_t const index, bool const owned) -> void;

	/**
	 *  @brief Get total of seen Pokemons.
	 *  @return Value of seen Pokemons.
	 */
	auto get_pokedex_seen_total() const -> std::uint8_t;

    /**
     *  @brief Get information from the Pokedex if Pokemon is seen.
	 *  @param index Pokedex index.
	 *  @return True if Pokemon seen.
	 */
    auto get_pokedex_seen(std::uint8_t const index) const -> bool;

	/**
	 *  @brief Set seen status of Pokemons in Pokedex.
	 *  @param index Pokedex index.
	 *  @param seen Seen status.
	 */
    auto set_pokedex_seen(std::uint8_t const index, bool const seen) -> void;

	/**
     *  @brief Get player money.
	 *  @return Player money value.
	 */
    auto get_money() const -> std::uint32_t;

	/**
     *  @brief Sets player money.
	 *  @param value New money value.
	 */
    auto set_money(std::uint32_t const value) -> void;

	/**
     *  @brief Get player casino coins.
	 *  @return Player casino coins value.
	 */
    auto get_casino_coins() const -> std::uint16_t;

	/**
     *  @brief Sets player casino coins.
	 *  @param value New casino coins value.
	 */
    auto set_casino_coins(std::uint16_t const value) -> void;

	/**
     *  @brief Get time played.
	 *  @param dest Variable to hold result.
	 */
    auto get_time_played(struct Structs::pkmn_time* dest) const -> void;

	/**
     *  @brief Set time played.
	 *  @param hours Hours value.
	 *  @param minutes Minutes value.
	 *  @param seconds Seconds value.
	 *  @param frames Frames value.
	 */
    auto set_time_played(std::uint8_t const hours, std::uint8_t const minutes, std::uint8_t const seconds, std::uint8_t const frames) -> void;

	/**
     *  @brief Get current active PC Box.
	 *  @return Current active PC Box index.
	 */
    auto get_current_pc_box() const -> std::uint8_t;

	/**
     *  @brief Set current active PC Box.
	 *  @param index PC Box index.
	 */
    auto set_current_pc_box(std::uint8_t const index) -> void;

	/**
     *  @brief Get Gym badge status.
	 *  @param badge Gym badge to check up against.
	 *  @return True if Gym has been completed.
	 */
    auto get_badge(enum Enums::badges const badge) const -> bool;

	/**
     *  @brief Set Gym badge status.
	 *  @param badge Gym badge to change.
	 */
    auto set_badge(enum Enums::badges const badge) -> void;

	/**
     *  @brief Get options flags.
	 *  @param flag Option to get.
	 *  @return Chosen option value.
	 */
    auto get_option(enum Enums::options const flag) const -> std::uint8_t;

	/**
     *  @brief Set options flags.
	 *  @param flag Option to change.
	 */
    auto set_option(enum Enums::options const flag) -> void;

	/**
     *  @brief Get Pikachu friendship value.
	 *  @return Pikachu friendship value.
	 */
    auto get_pikachu_friendship() const -> std::uint8_t;

	/**
     *  @brief Set Pikachu friendship value.
	 *  @param value New value.
	 */
    auto set_pikachu_friendship(std::uint8_t const value) -> void;

	/**
     *  @brief Get total amount of items in players bag.
	 *  @return Count of items in bag.
	 */
    auto get_item_bag_count() const -> std::uint8_t;

	/**
     *  @brief Get information from item in players bag.
	 *  @param index Index of the item.
	 *  @return Selected item information
	 */
    auto get_item_bag(std::uint8_t const index) const -> struct Structs::item*;

	/**
     *  @brief Set an item in the players bag.
	 *  @param items Items in the players bag.
	 *  @param index Item index in the bag
	 *  @param item Item type.
	 *  @param count Item quantity.
	 */
    auto set_item_bag(struct Structs::item* items, std::uint8_t const index, std::uint8_t const item, std::uint8_t const count) -> void;

	/**
     *  @brief Get PC items count.
	 *  @return PC items count value.
	 */
    auto get_item_pc_count() const -> std::uint8_t;

	/**
     *  @brief Get PC item information.
	 *  @param index PC item index.
	 *  @return PC item information.
	 */
    auto get_item_pc(std::uint8_t const index) const -> struct Structs::item*;

	/**
     *  @brief Set PC item information.
	 *  @param index PC index.
	 *  @param item Item ID.
	 *  @param count Item amount.
	 */
    auto set_item_pc(std::uint8_t const index, std::uint8_t const item, std::uint8_t const count) -> void;

	/**
     *  @brief Get party information.
	 *  @return Party information.
	 */
    auto get_pokemon_party() const -> struct Structs::pkmn_party*;

	/**
     *  @brief Get Pokemon information from the party.
	 *  @param index Party index.
	 *  @return Pokemon information.
	 */
    auto get_pokemon_in_party(std::uint8_t index) const -> struct Structs::pkmn_data_party*;

	/**
     *  @brief Get Pokemon information from the party.
	 *  @param index Party index.
	 *  @return Pokemon information.
	 */
    auto get_pokemon_in_party_trainer_name(std::uint8_t index) const -> std::string;

	/**
     *  @brief Get Pokemon name from the party.
	 *  @param index Party index.
	 *  @return Pokemon name.
	 */
    auto get_pokemon_in_party_name(std::uint8_t index) const -> std::string;

	/**
     *  @brief Get current active PC Box information.
	 *  @return Current active PC Box information.
	 */
    auto get_current_pc_box_list() const -> struct Structs::pkmn_box*;

	/**
     *  @brief Get Pokemon from current active PC Box.
     *  @param index Pokemon index.
	 *  @return Pokemon information from current active PC Box.
	 */
    auto get_pokemon_in_current_box(std::uint8_t index) const -> struct Structs::pkmn_data_box*;

	/**
     *  @brief Get Pokemon name from current active PC Box.
	 *  @param index Current active PC Box index.
	 *  @return Pokemon name.
	 */
    auto get_pokemon_in_current_box_name(std::uint8_t index) const -> std::string;

	/**
     *  @brief Get PC Box information.
	 *  @param box PC Box index.
	 *  @return PC Box information.
	 */
    auto get_pokemon_box(std::uint8_t box) const -> struct Structs::pkmn_box*;

	/**
     *  @brief Get Pokemon information from PC Box.
	 *  @param box PC Box index.
	 *  @param index Pokemon index.
	 *  @return Pokemon information from PC Box.
	 */
    auto get_pokemon_in_box(std::uint8_t box, std::uint8_t index) const -> struct Structs::pkmn_data_box*;

	/**
     *  @brief Get Pokemon trainer name from PC Box.
	 *  @param box PC Box index.
	 *  @param index Pokemon index.
	 *  @return Pokemon trainer name.
	 */
    auto get_pokemon_in_box_trainer_name(std::uint8_t box, std::uint8_t index) const -> std::string;

	/**
     *  @brief Get Pokemon name from PC Box.
	 *  @param index PC Box index.
	 *  @return Pokemon name.
	 */
    auto get_pokemon_in_box_name(std::uint8_t box, std::uint8_t index) const -> std::string;

	/**
     *  @brief Convert ASCII char to equivalent ROM byte.
	 *  @param c ASCII character.
	 *  @return Converted byte.
	 */
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
