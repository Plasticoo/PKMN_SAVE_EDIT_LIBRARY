#ifndef _PKMN_GEN1_HPP_
#define _PKMN_GEN1_HPP_

#include "Constants.hpp"
#include "Gen/Gen1/Enums.hpp"
#include "Gen/Gen1/Structs.hpp"
#include "Rom.hpp"
#include "Rom/RomInterface.hpp"
#include "Utils.hpp"

#include <fstream>
#include <functional>
#include <map>
#include <memory>

/** @brief Contains Generation I relevant classes, functions and utilities. */
namespace Gen1
{
auto get_rom_type(std::uint32_t file_size) -> std::string
{
    if (file_size == 0x8000) {
        return "Rom32kb";
    } else {
        return "Rom64kb";
    }
}

template<template<typename> class>
struct base_of;

template<template<typename> class C>
using base_of_t = typename base_of<C>::type;

template<template<typename> class C>
std::unique_ptr<base_of_t<C>> make_templated(const std::string& type_str)
{
    RomType type = get_string_romtype(type_str);
    const std::map<RomType, std::function<std::unique_ptr<base_of_t<C>>()>> factory{
        { RomType::Rom32kb, [] { return std::make_unique<C<Rom32kb>>(); } },
        { RomType::Rom64kb, [] { return std::make_unique<C<Rom64kb>>(); } },
        { RomType::Unknown, [] { return nullptr; } }
    };
    return factory.at(type)();
}

struct IGen1 {
    virtual auto get_checksum() const -> std::uint8_t = 0;
    virtual auto calc_checksum() const -> std::uint8_t = 0;
    virtual auto set_checksum() -> void = 0;
    virtual auto get_rom_size() const -> std::uint32_t = 0;
    virtual auto load_file(std::filesystem::path const& file) -> void = 0;
    virtual auto save_changes(std::filesystem::path const& file_name) const -> bool = 0;
    virtual auto get_player_name() const -> std::string = 0;
    virtual auto set_player_name(std::string const& name) -> void = 0;
    virtual auto get_rival_name() const -> std::string = 0;
    virtual auto set_rival_name(std::string const& name) -> void = 0;
    virtual auto get_pokedex_owned_total() const -> std::uint8_t = 0;
    virtual auto get_pokedex_owned(std::uint8_t const index) const -> bool = 0;
    virtual auto set_pokedex_owned(std::uint8_t const index, bool const owned) -> void = 0;
    virtual auto get_pokedex_seen_total() const -> std::uint8_t = 0;
    virtual auto get_pokedex_seen(std::uint8_t const index) const -> bool = 0;
    virtual auto set_pokedex_seen(std::uint8_t const index, bool const seen) -> void = 0;
    virtual auto get_money() const -> std::uint32_t = 0;
    virtual auto set_money(std::uint32_t const value) -> void = 0;
    virtual auto get_casino_coins() const -> std::uint16_t = 0;
    virtual auto set_casino_coins(std::uint16_t const value) -> void = 0;
    virtual auto get_time_played(struct Structs::pkmn_time* dest) const -> void = 0;
    virtual auto set_time_played(std::uint8_t const hours, std::uint8_t const minutes, std::uint8_t const seconds, std::uint8_t const frames) -> void = 0;
    virtual auto get_current_pc_box() const -> std::uint8_t = 0;
    virtual auto set_current_pc_box(std::uint8_t const index) -> void = 0;
    virtual auto get_badge(enum Enums::badges const badge) const -> bool = 0;
    virtual auto set_badge(enum Enums::badges const badge) -> void = 0;
    virtual auto get_option(enum Enums::options const flag) const -> std::uint8_t = 0;
    virtual auto set_option(enum Enums::options const flag) -> void = 0;
    virtual auto get_pikachu_friendship() const -> std::uint8_t = 0;
    virtual auto set_pikachu_friendship(std::uint8_t const value) -> void = 0;
    virtual auto get_item_bag_count() const -> std::uint8_t = 0;
    virtual auto get_item_bag(std::uint8_t const index) const -> struct Structs::item* = 0;
    virtual auto set_item_bag(struct Structs::item* items, std::uint8_t const index, std::uint8_t const item, std::uint8_t const count) -> void = 0;
    virtual auto get_item_pc_count() const -> std::uint8_t = 0;
    virtual auto get_item_pc(std::uint8_t const index) const -> struct Structs::item* = 0;
    virtual auto set_item_pc(std::uint8_t const index, std::uint8_t const item, std::uint8_t const count) -> void = 0;
    virtual auto get_pokemon_party() const -> struct Structs::pkmn_party* = 0;
    virtual auto get_pokemon_in_party(std::uint8_t index) const -> struct Structs::pkmn_data_party* = 0;
    virtual auto get_pokemon_in_party_trainer_name(std::uint8_t index) const -> std::string = 0;
    virtual auto get_pokemon_in_party_name(std::uint8_t index) const -> std::string = 0;
    virtual auto get_current_pc_box_list() const -> struct Structs::pkmn_box* = 0;
    virtual auto get_pokemon_in_current_box(std::uint8_t index) const -> struct Structs::pkmn_data_box* = 0;
    virtual auto get_pokemon_in_current_box_name(std::uint8_t index) const -> std::string = 0;
    virtual auto get_pokemon_box(std::uint8_t box) const -> struct Structs::pkmn_box* = 0;
    virtual auto get_pokemon_in_box(std::uint8_t box, std::uint8_t index) const -> struct Structs::pkmn_data_box* = 0;
    virtual auto get_pokemon_in_box_trainer_name(std::uint8_t box, std::uint8_t index) const -> std::string = 0;
    virtual auto get_pokemon_in_box_name(std::uint8_t box, std::uint8_t index) const -> std::string = 0;
    virtual auto get_character_code(std::uint8_t const c) const -> std::uint8_t = 0;
};

/** @brief  Generation I class. */
template<typename T>
struct Gen1: IGen1 {
    /**
	 *  @brief Gen1 Constructor
	 */
    Gen1()
    {
        this->m_rom = std::make_unique<T>();
    }

    /**
	 *  @brief Get current checksum.
	 *  @return Relevant byte that represents the checksum.
	 */
    auto get_checksum() const -> std::uint8_t override
    {
        return this->m_rom->data[C::GEN1::OFFSETS::CHECKSUM];
    }

    /**
	 *  @brief Calculates the checksum.
	 *  @return Checksum calculation result.
	 */
    auto calc_checksum() const -> std::uint8_t override
    {
        std::uint8_t checksum{ 0 };
        for (auto i = C::GEN1::OFFSETS::CHECKSUM_INIT_OFFSET;
             i <= C::GEN1::OFFSETS::CHECKSUM_END_OFFSET; i++) {
            checksum += m_rom->data[i];
        }
        return ~checksum;
    }

    /**
	 *  @brief Calculates the checksum and sets the value in the relevant Rom byte.
	 */
    auto set_checksum() -> void override
    {
        auto checksum = this->calc_checksum();
        // NOTE: *(this->checksum) = checksum
        this->checksum[0] = checksum;
    }

	/**
	 *  @brief Get total size of the rom file.
	 *  @return Rom size;
	 */
    auto get_rom_size() const -> std::uint32_t override
    {
        return this->m_rom->get_size();
    }

    /**
	 *  @brief Loads Rom information into relevant structs.
	 *  @param file File to load.
	 */
    auto load_file(std::filesystem::path const& file) -> void override
    {
        if (this->m_rom == nullptr) {
            return;
        }

        this->m_rom->load(file);

        this->player_name = &this->m_rom->data[C::GEN1::OFFSETS::PLAYER_NAME];
        this->pokedex_owned = &this->m_rom->data[C::GEN1::OFFSETS::POKEDEX_OWNED];
        this->pokedex_seen = &this->m_rom->data[C::GEN1::OFFSETS::POKEDEX_SEEN];
        this->money = &this->m_rom->data[C::GEN1::OFFSETS::MONEY];
        this->rival_name = &this->m_rom->data[C::GEN1::OFFSETS::RIVAL_NAME];
        this->options = &this->m_rom->data[C::GEN1::OFFSETS::OPTIONS];
        this->badges = &this->m_rom->data[C::GEN1::OFFSETS::BADGES];
        this->player_trainer_id = (std::uint16_t*)&this->m_rom->data[C::GEN1::OFFSETS::PLAYER_TRAINER_ID];
        this->pikachu_friendship = &this->m_rom->data[C::GEN1::OFFSETS::PIKACHU_FRIENDSHIP];
        this->current_pc_box = &this->m_rom->data[C::GEN1::OFFSETS::CURRENT_PC_BOX];
        this->casino_coins = &this->m_rom->data[C::GEN1::OFFSETS::CASINO_COINS];
        this->current_box_list = (struct Structs::pkmn_box*)&this->m_rom->data[C::GEN1::OFFSETS::CURRENT_BOX_LIST];
        this->checksum = &this->m_rom->data[C::GEN1::OFFSETS::CHECKSUM];

        this->pocket_item_list = (struct Structs::items_bag*)&this->m_rom->data[C::GEN1::OFFSETS::POCKET_ITEM_LIST];
        this->pc_item_list = (struct Structs::items_pc*)&this->m_rom->data[C::GEN1::OFFSETS::PC_ITEM_LIST];
        this->time_played = (struct Structs::pkmn_time*)&this->m_rom->data[C::GEN1::OFFSETS::TIME_PLAYED];
        this->team_pokemon_list = (struct Structs::pkmn_party*)&this->m_rom->data[C::GEN1::OFFSETS::TEAM_POKEMON_LIST];

        this->pc_box[0] = (struct Structs::pkmn_box*)&this->m_rom->data[0x4000];
        this->pc_box[1] = (struct Structs::pkmn_box*)&this->m_rom->data[0x4000 + (1122 * 1)];
        this->pc_box[2] = (struct Structs::pkmn_box*)&this->m_rom->data[0x4000 + (1122 * 2)];
        this->pc_box[3] = (struct Structs::pkmn_box*)&this->m_rom->data[0x4000 + (1122 * 3)];
        this->pc_box[4] = (struct Structs::pkmn_box*)&this->m_rom->data[0x4000 + (1122 * 4)];
        this->pc_box[5] = (struct Structs::pkmn_box*)&this->m_rom->data[0x4000 + (1122 * 5)];

        this->pc_box[6] = (struct Structs::pkmn_box*)&this->m_rom->data[0x6000];
        this->pc_box[7] = (struct Structs::pkmn_box*)&this->m_rom->data[0x6000 + (1122 * 1)];
        this->pc_box[8] = (struct Structs::pkmn_box*)&this->m_rom->data[0x6000 + (1122 * 2)];
        this->pc_box[9] = (struct Structs::pkmn_box*)&this->m_rom->data[0x6000 + (1122 * 3)];
        this->pc_box[10] = (struct Structs::pkmn_box*)&this->m_rom->data[0x6000 + (1122 * 4)];
        this->pc_box[11] = (struct Structs::pkmn_box*)&this->m_rom->data[0x6000 + (1122 * 5)];
    }

    /**
	 *  @brief Save changes made to Rom information in memory to a file.
	 *
	 *  @param file_name Path to file.
	 *
	 *  @return True if everything worked.
	 */
    auto save_changes(std::filesystem::path const& file_name) const -> bool override
    {
        std::ofstream out;

        if (!this->m_rom) {
            return false;
        }

        out.open(file_name, std::ios::out | std::ios::binary);

        if (!out.is_open()) {
            return false;
        }

        for (auto i = 0; i < C::GEN1::SIZES::FILE; i++) {
            out.write((char*)&this->m_rom->data[i], 1);
        }

        return true;
    }

	/**
	 *  @brief Get player name.
	 *  @return Name of the player.
	 */
    auto get_player_name() const -> std::string override
    {
        if (this->player_name == nullptr) {
            return nullptr;
        }

        std::string name = "";
        for (auto i = 0; i < C::GEN1::SIZES::PLAYER_NAME; i++) {
            if (this->player_name[i] == 'P') {
                break;
            }

            name += C::GEN1::FONT[this->player_name[i]];
        }

        return name;
    }

	/**
	 *  @brief Set player name.
	 *  @param name New player name.
	 */
    auto set_player_name(std::string const& name) -> void override
    {
        std::size_t size = name.size();

        if (this->player_name == nullptr || name.empty()) {
            return;
        }

        if (size >= 7) {
            size = 7;
        }

        for (auto i = 0; i < size; i++) {
            this->player_name[i] = this->get_character_code(name[i]);
        }

        this->player_name[++size] = 'P';

        while (size < 11) {
            this->player_name[++size] = 0x0;
        }
    }

	/**
	 *  @brief Get rival name.
	 *  @return Name of the rival.
	 */
    auto get_rival_name() const -> std::string override
    {
        if (this->rival_name == nullptr) {
            return nullptr;
        }

        std::string name = "";
        for (auto i = 0; i < C::GEN1::SIZES::PLAYER_NAME; i++) {
            if (this->rival_name[i] == 'P') {
                break;
            }

            name += C::GEN1::FONT[this->rival_name[i]];
        }

        return name;
    }

	/**
	 *  @brief Set rival name.
	 *  @param name New rival name.
	 */
    auto set_rival_name(std::string const& name) -> void override
    {
        std::size_t size = name.size();

        if (this->rival_name == nullptr || name.empty()) {
            return;
        }

        if (size >= 7) {
            size = 7;
        }

        for (auto i = 0; i < size; i++) {
            this->rival_name[i] = this->get_character_code(name[i]);
        }

        this->rival_name[++size] = 'P';

        while (size < 11) {
            this->rival_name[++size] = 0x0;
        }
    }

	/**
	 *  @brief Get total of owned Pokemons.
	 *  @return Value of owned Pokemons.
	 */
    auto get_pokedex_owned_total() const -> std::uint8_t override
    {
        std::uint8_t total = 0;

        for (auto i = 0; i < 151; i++) {
            if (this->get_pokedex_owned(i)) {
                total++;
            }
        }

        return total;
    }

	/**
	 *  @brief Get information from the Pokedex if Pokemon is owned.
	 *  @param index Pokedex index.
	 *  @return True if Pokemon owned.
	 */
    auto get_pokedex_owned(std::uint8_t const index) const -> bool override
    {
        if (this->pokedex_owned && index < 152) {
            return (this->pokedex_owned[index >> 3] >> (index & 7) & 1) == 1;
        }

        return false;
    }

	/**
	 *  @brief Set own status of Pokemons in Pokedex.
	 *  @param index Pokedex index.
	 *  @param owned Own status.
	 */
    auto set_pokedex_owned(std::uint8_t const index, bool const owned) -> void override
    {
        if (owned) {
            this->pokedex_owned[index >> 3] |= 1 << (index & 7);
        } else {
            this->pokedex_owned[index >> 3] &= ~(1 << (index & 7));
        }
    }

	/**
	 *  @brief Get total of seen Pokemons.
	 *  @return Value of seen Pokemons.
	 */
    auto get_pokedex_seen_total() const -> std::uint8_t override
    {
        std::uint8_t total = 0;

        for (auto i = 0; i < 151; i++) {
            if (this->get_pokedex_seen(i)) {
                total++;
            }
        }

        return total;
    }

	/**
     *  @brief Get information from the Pokedex if Pokemon is seen.
	 *  @param index Pokedex index.
	 *  @return True if Pokemon seen.
	 */
    auto get_pokedex_seen(std::uint8_t const index) const -> bool override
    {
        if (this->pokedex_seen && index < 152) {
            return (this->pokedex_seen[index >> 3] >> (index & 7) & 1) == 1;
        }

        return false;
    }

	/**
	 *  @brief Set seen status of Pokemons in Pokedex.
	 *  @param index Pokedex index.
	 *  @param seen Seen status.
	 */
    auto set_pokedex_seen(std::uint8_t const index, bool const seen) -> void override
    {
        if (seen) {
            this->pokedex_seen[index >> 3] |= 1 << (index & 7);
        } else {
            this->pokedex_seen[index >> 3] &= ~(1 << (index & 7));
        }
    }

	/**
     *  @brief Get player money.
	 *  @return Player money value.
	 */
    auto get_money() const -> std::uint32_t override
    {
        if (!this->money) {
            return 0x7FFFFFFF;
        }

        if (this->money[1] == 0 && this->money[2] == 0) {
            return Utils::__bcd_to_dec(this->money, 1);
        } else if (this->money[1] != 0 && this->money[2] == 0) {
            return Utils::__bcd_to_dec(this->money, 2);
        }

        return Utils::__bcd_to_dec(this->money, C::GEN1::SIZES::MONEY);
    }

	/**
     *  @brief Sets player money.
	 *  @param value New money value.
	 */
    auto set_money(std::uint32_t const value) -> void override
    {
        if (!this->money) {
            return;
        }

        // std::uint8_t buffer[C::GEN1::SIZES::MONEY];
        std::array<std::uint8_t, C::GEN1::SIZES::MONEY> buffer;

        Utils::__dec_to_bcd(value, buffer.data());

        std::memcpy(this->money, buffer.data(), C::GEN1::SIZES::MONEY);
    }

	/**
     *  @brief Get player casino coins.
	 *  @return Player casino coins value.
	 */
    auto get_casino_coins() const -> std::uint16_t override
    {
        if (!this->casino_coins) {
            return 0;
        }

        if (this->casino_coins[1] == 0) {
            return Utils::__bcd_to_dec(this->casino_coins, 1);
        }

        return Utils::__bcd_to_dec(this->casino_coins, C::GEN1::SIZES::CASINO_COINS);
    }

	/**
     *  @brief Sets player casino coins.
	 *  @param value New casino coins value.
	 */
    auto set_casino_coins(std::uint16_t const value) -> void override
    {
        if (!this->casino_coins) {
            return;
        }

        std::array<std::uint8_t, C::GEN1::SIZES::CASINO_COINS> buffer;

        Utils::__dec_to_bcd(value, buffer.data());

        if (Utils::n_digits(value) == 1 || Utils::n_digits(value) == 2) {
            this->casino_coins[0] = buffer[0];
            this->casino_coins[1] = 0;

            return;
        }

        std::memcpy(this->casino_coins, buffer.data(), C::GEN1::SIZES::CASINO_COINS);
    }

	/**
     *  @brief Get time played.
	 *  @param dest Variable to hold result.
	 */
    auto get_time_played(struct Structs::pkmn_time* dest) const -> void override
    {
        if (this->time_played && dest) {
            dest->hours = this->time_played->hours;
            dest->maxed = this->time_played->maxed;
            dest->minutes = this->time_played->minutes;
            dest->seconds = this->time_played->seconds;
            dest->frames = this->time_played->frames;

            return;
        }
    }

	/**
     *  @brief Set time played.
	 *  @param hours Hours value.
	 *  @param minutes Minutes value.
	 *  @param seconds Seconds value.
	 *  @param frames Frames value.
	 */
    auto set_time_played(std::uint8_t const hours, std::uint8_t const minutes, std::uint8_t const seconds, std::uint8_t const frames) -> void override
    {
        if (hours <= 255 &&
            minutes <= 59 &&
            seconds <= 59 &&
            this->time_played) {
            this->time_played->frames = frames;
            this->time_played->seconds = seconds;
            this->time_played->minutes = minutes;
            this->time_played->hours = hours;

            if (hours == 255 && minutes == 59 && seconds == 59 && frames == 59) {
                this->time_played->maxed = 255;
            }

            return;
        }
    }

	/**
     *  @brief Get current active PC Box.
	 *  @return Current active PC Box index.
	 */
    auto get_current_pc_box() const -> std::uint8_t override
    {
        if (this->current_pc_box) {
            return (current_pc_box[0] & 0b01111111) + 1;
        }

        return 0;
    }

    // TODO: set 8th bit if needed
	/**
     *  @brief Set current active PC Box.
	 *  @param index PC Box index.
	 */
    auto set_current_pc_box(std::uint8_t const index) -> void override
    {
        std::uint8_t idx;

        if (this->current_pc_box && index <= 20) {
            if (index == 0) {
                idx = 0;
            } else {
                idx = index - 1;
            }

            this->current_pc_box[0] = idx;
        }
    }

	/**
     *  @brief Get Gym badge status.
	 *  @param badge Gym badge to check up against.
	 *  @return True if Gym has been completed.
	 */
    auto get_badge(enum Enums::badges const badge) const -> bool override
    {
        if (this->badges) {
            return ((this->badges[0] & (1 << badge)) >> badge) == 1 ? true : false;
        }

        return false;
    }

	/**
     *  @brief Set Gym badge status.
	 *  @param badge Gym badge to change.
	 */
    auto set_badge(enum Enums::badges const badge) -> void override
    {
        if (this->badges) {
            this->badges[0] ^= (1 << badge);
        }
    }

	/**
     *  @brief Get options flags.
	 *  @param flag Option to get.
	 *  @return Chosen option value.
	 */
    auto get_option(enum Enums::options const flag) const -> std::uint8_t override
    {
        if (!this->options) {
            return 0;
        }

        return options[0] & C::GEN1::OPTIONS::LOOKUP_TABLE[flag];
    }

	/**
     *  @brief Set options flags.
	 *  @param flag Option to change.
	 */
    auto set_option(enum Enums::options const flag) -> void override
    {
        if (!this->options) {
            return;
        }

        Utils::set_clear_bits(&this->options[0], C::GEN1::OPTIONS::LOOKUP_TABLE[flag]);
    }

	/**
     *  @brief Get Pikachu friendship value.
	 *  @return Pikachu friendship value.
	 */
    auto get_pikachu_friendship() const -> std::uint8_t override
    {
        if (this->pikachu_friendship) {
            return this->pikachu_friendship[0];
        }

        return 0;
    }

	/**
     *  @brief Set Pikachu friendship value.
	 *  @param value New value.
	 */
    auto set_pikachu_friendship(std::uint8_t const value) -> void override
    {
        if (this->pikachu_friendship) {
            this->pikachu_friendship[0] = value;
            return;
        }
    }

	/**
     *  @brief Get total amount of items in players bag.
	 *  @return Count of items in bag.
	 */
    auto get_item_bag_count() const -> std::uint8_t override
    {
        return this->pocket_item_list->count;
    }

	/**
     *  @brief Get information from item in players bag.
	 *  @param index Index of the item.
	 *  @return Selected item information
	 */
    auto get_item_bag(std::uint8_t const index) const -> struct Structs::item* override
    {
        if (index <= C::GEN1::SIZES::BAG_ITEM) {
            return &this->pocket_item_list->item[index];
        }

        return nullptr;
    }

    /**
     *  @brief Set an item in the players bag.
	 *  @param items Items in the players bag.
	 *  @param index Item index in the bag
	 *  @param item Item type.
	 *  @param count Item quantity.
	 */
    auto set_item_bag(struct Structs::item* items, std::uint8_t const index, std::uint8_t const item, std::uint8_t const count) -> void override
    {
        if (index > 0 && index <= C::GEN1::SIZES::BAG_ITEM) {
			this->pocket_item_list->item[index].index = item;
			this->pocket_item_list->item[index].count = count;

            return;
        }

		return;
    }

	/**
     *  @brief Get PC items count.
	 *  @return PC items count value.
	 */
    auto get_item_pc_count() const -> std::uint8_t override
    {
        return this->pc_item_list->count;
    }

	/**
     *  @brief Get PC item information.
	 *  @param index PC item index.
	 *  @return PC item information.
	 */
    auto get_item_pc(std::uint8_t const index) const -> struct Structs::item* override
    {
        if (index <= C::GEN1::SIZES::PC_ITEM) {
            return &this->pc_item_list->item[index];
        }

        return nullptr;
    }

    /**
     *  @brief Set PC item information.
	 *  @param index PC index.
	 *  @param item Item ID.
	 *  @param count Item amount.
	 */
    auto set_item_pc(std::uint8_t const index, std::uint8_t const item, std::uint8_t const count) -> void override
    {
        if (index > 0 && index < C::GEN1::SIZES::PC_ITEM) {
            this->pc_item_list->item[index].index = item;
            this->pc_item_list->item[index].count = count;

            return;
        }

        return;
    }

	/**
     *  @brief Get party information.
	 *  @return Party information.
	 */
    auto get_pokemon_party() const -> struct Structs::pkmn_party* override
    {
        if (this->team_pokemon_list) {
            return this->team_pokemon_list;
        }

        return nullptr;
    }

	/**
     *  @brief Get Pokemon information from the party.
	 *  @param index Party index.
	 *  @return Pokemon information.
	 */
    auto get_pokemon_in_party(std::uint8_t index) const -> struct Structs::pkmn_data_party* override
    {
        if (this->team_pokemon_list) {
            return &this->team_pokemon_list->pokemon[index];
        }

        return nullptr;
    }

	/**
     *  @brief Get Pokemon information from the party.
	 *  @param index Party index.
	 *  @return Pokemon information.
	 */
    auto get_pokemon_in_party_trainer_name(std::uint8_t index) const -> std::string override
    {
        auto _name = this->team_pokemon_list->original_trainer_name[index];

        if (_name == nullptr) {
            return "";
        }

        std::string name = "";
        for (auto i = 0; i < C::GEN1::SIZES::PLAYER_NAME; i++) {
            if (_name[i] == 'P') {
                break;
            }

            name += C::GEN1::FONT[_name[i]];
        }

        return name;
    }

	/**
     *  @brief Get Pokemon name from the party.
	 *  @param index Party index.
	 *  @return Pokemon name.
	 */
    auto get_pokemon_in_party_name(std::uint8_t index) const -> std::string override
    {
        auto _name = this->team_pokemon_list->pokemon_name[index];

        if (_name == nullptr) {
            return "";
        }

        std::string name = "";
        for (auto i = 0; i < C::GEN1::SIZES::PLAYER_NAME; i++) {
            if (_name[i] == 'P') {
                break;
            }

            name += C::GEN1::FONT[_name[i]];
        }

        return name;
    }

	/**
     *  @brief Get current active PC Box information.
	 *  @return Current active PC Box information.
	 */
    auto get_current_pc_box_list() const -> struct Structs::pkmn_box* override
    {
        if (this->current_box_list) {
            return this->current_box_list;
        }

        return nullptr;
    }

	/**
     *  @brief Get Pokemon from current active PC Box.
     *  @param index Pokemon index.
	 *  @return Pokemon information from current active PC Box.
	 */
    auto get_pokemon_in_current_box(std::uint8_t index) const -> struct Structs::pkmn_data_box* override
    {
        if (this->current_box_list) {
            return &this->current_box_list->pokemon[index];
        }

        return nullptr;
    }

	/**
     *  @brief Get Pokemon name from current active PC Box.
	 *  @param index Current active PC Box index.
	 *  @return Pokemon name.
	 */
    auto get_pokemon_in_current_box_name(std::uint8_t index) const -> std::string override
    {
        auto _name = this->current_box_list->pokemon_name[index];

        if (_name == nullptr) {
            return "";
        }

        std::string name = "";
        for (auto i = 0; i < C::GEN1::SIZES::PLAYER_NAME; i++) {
            if (_name[i] == 'P') {
                break;
            }

            name += C::GEN1::FONT[_name[i]];
        }

        return name;
    }

	/**
     *  @brief Get PC Box information.
	 *  @param box PC Box index.
	 *  @return PC Box information.
	 */
    auto get_pokemon_box(std::uint8_t box) const -> struct Structs::pkmn_box* override
    {
        if (this->pc_box[box]) {
            return this->pc_box[box];
        }

        return nullptr;
    }

	/**
     *  @brief Get Pokemon information from PC Box.
	 *  @param box PC Box index.
	 *  @param index Pokemon index.
	 *  @return Pokemon information from PC Box.
	 */
    auto get_pokemon_in_box(std::uint8_t box, std::uint8_t index) const -> struct Structs::pkmn_data_box* override
    {
        if (this->pc_box[box] != nullptr) {
            return &this->pc_box[box]->pokemon[index];
        }

        return nullptr;
    }

	/**
     *  @brief Get Pokemon trainer name from PC Box.
	 *  @param box PC Box index.
	 *  @param index Pokemon index.
	 *  @return Pokemon trainer name.
	 */
    auto get_pokemon_in_box_trainer_name(std::uint8_t box, std::uint8_t index) const -> std::string override
    {
        auto _name = this->pc_box[box]->original_trainer_name[index];

        if (_name == nullptr) {
            return "";
        }

        std::string name = "";
        for (auto i = 0; i < C::GEN1::SIZES::PLAYER_NAME; i++) {
            if (_name[i] == 'P') {
                break;
            }

            name += C::GEN1::FONT[_name[i]];
        }

        return name;
    }

	/**
     *  @brief Get Pokemon name from PC Box.
	 *  @param index PC Box index.
	 *  @return Pokemon name.
	 */
    auto get_pokemon_in_box_name(std::uint8_t box, std::uint8_t index) const -> std::string override
    {
        auto _name = this->pc_box[box]->pokemon_name[index];

        if (_name == nullptr) {
            return "";
        }

        std::string name = "";
        for (auto i = 0; i < C::GEN1::SIZES::PLAYER_NAME; i++) {
            if (_name[i] == 'P') {
                break;
            }

            name += C::GEN1::FONT[_name[i]];
        }

        return name;
    }

	/**
     *  @brief Convert ASCII char to equivalent ROM byte.
	 *  @param c ASCII character.
	 *  @return Converted byte.
	 */
    auto get_character_code(std::uint8_t const c) const -> std::uint8_t override
    {
        int i;

        for (i = 0; i < C::GEN1::SIZES::FONT; i++) {
            if (c == C::GEN1::FONT[i]) {
                return i;
            }
        }

        // return space code, as in, invalid character
        return 0x7F;
    }

  private:
    std::unique_ptr<T> m_rom;

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

template<>
struct base_of<Gen1> {
    using type = IGen1;
};
}
#endif
