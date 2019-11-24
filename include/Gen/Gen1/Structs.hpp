#ifndef __GEN1_STRUCTS_H_
#define __GEN1_STRUCTS_H_

#include "Constants.hpp"

#include <cinttypes>
#include <sys/types.h>

namespace Gen1
{
/** @brief Contains Generation I relevant serializable structures. */
namespace Structs
{
    /**
	 * @brief Structure that represents the time played.
	 */
    struct pkmn_time {
        std::uint8_t hours; /**< Hours played. */
        std::uint8_t maxed; /**< Bit that is set if time is maxed out.  */
        std::uint8_t minutes; /**< Minutes played. */
        std::uint8_t seconds; /**< Seconds played. */
        std::uint8_t frames; /**< Frames per second. */
    };
	static_assert(sizeof(struct pkmn_time) == 5, "struct pkmn_time should be 5 bytes");

    /**
	 * @brief Structure that represents a pokemon in the party.
	 */
    struct pkmn_data_party {
        std::uint8_t index; /**< Party index. */
        std::uint16_t hp; /**< Health Points. */
        std::uint8_t level; /**< Level. */
        std::uint8_t status; /**< Current status. (e.g.: Poisoned) */
        std::uint8_t type[2]; /**< Primary type and secondary type. */
        std::uint8_t catch_item; /**< Catch rate or held item. */
        std::uint8_t moves[4]; /**< Current moves learned. */
        std::uint16_t trainer_id; /**< Original trainer ID. */
        std::uint8_t xp[3]; /**< Experience points. */
        std::uint16_t hp_ev; /**< Health Points effort value. */
        std::uint16_t atk_ev; /**< Attack effort value. */
        std::uint16_t def_ev; /**< Defense effort value. */
        std::uint16_t speed_ev; /**< Speed effort value. */
        std::uint16_t special_ev; /**< Special effort value. */
        std::uint16_t iv; /**< Individual value. */
        std::uint8_t moves_pp[4]; /**< Power Points for each move. */
        std::uint8_t level_opt; /**< Level alternative value. */
        std::uint16_t max_hp; /**< Maximum Health Points. */
        std::uint16_t atk; /**< Alternative Attack value. */
        std::uint16_t def; /**< Alternative Defense value. */
        std::uint16_t speed; /**< Alternative Speed value. */
        std::uint16_t special; /**< Alternative Special value. */
    } __attribute__((packed));
    static_assert(sizeof(struct pkmn_data_party) == 44, "struct pkmn_data_party should be 44 bytes");

    /**
	 * @brief Structure that represents a pokemon in a PC Box.
	 */
    struct pkmn_data_box {
        std::uint8_t index; /**< Party index. */
        std::uint16_t hp; /**< Health Points. */
        std::uint8_t level; /**< Level. */
        std::uint8_t status; /**< Current status. (e.g.: Poisoned) */
        std::uint8_t type[2]; /**< Primary type and secondary type. */
        std::uint8_t catch_item; /**< Catch rate or held item. */
        std::uint8_t moves[4]; /**< Current moves learned. */
        std::uint16_t trainer_id; /**< Original trainer ID. */
        std::uint8_t xp[3]; /**< Experience points. */
        std::uint16_t hp_ev; /**< Health Points effort value. */
        std::uint16_t atk_ev; /**< Attack effort value. */
        std::uint16_t def_ev; /**< Defense effort value. */
        std::uint16_t speed_ev; /**< Speed effort value. */
        std::uint16_t special_ev; /**< Special effort value. */
        std::uint16_t iv; /**< Individual value. */
        std::uint8_t moves_pp[4]; /**< Power Points for each move. */
    } __attribute__((packed));
    static_assert(sizeof(struct pkmn_data_box) == 33, "struct pkmn_data_box should be 33 bytes");

    /**
	 * @brief Structure that represents a Pokemon Party.
	 */
    struct pkmn_party {
        std::uint8_t count; /**< Pokemon count in party. */
        std::uint8_t species_id[6]; /**< Species ID of each Pokemon. */
        std::uint8_t unused; /**< Unused byte. */
        struct pkmn_data_party pokemon[6]; /**< Pokemon Data for each Pokemon. */
        std::uint8_t original_trainer_name[6][11]; /**< Original Trainer Name for each Pokemon. */
        std::uint8_t pokemon_name[6][11]; /**< Pokemon Name for each Pokemon. */
    } __attribute__((packed));
	static_assert(sizeof(struct pkmn_party) == 404, "struct pkmn_party should be 404 bytes");

    /**
	 * @brief Structure that represents a Pokemon PC Box.
	 */
    struct pkmn_box {
        std::uint8_t count; /**< Pokemon count in party. */
        std::uint8_t species_id[20]; /**< Species ID of each Pokemon. */
        std::uint8_t unused; /**< Unused byte. */
        struct pkmn_data_box pokemon[20]; /**< Pokemon Data for each Pokemon. */
        std::uint8_t original_trainer_name[20][11]; /**< Original Trainer Name for each Pokemon. */
        std::uint8_t pokemon_name[20][11]; /**< Pokemon Name for each Pokemon. */
    } __attribute__((packed));
	static_assert(sizeof(struct pkmn_box) == 1122, "struct pkmn_box should be 1122 bytes");

    /**
	 * @brief Structure that represents an item.
	 */
    struct item {
        std::uint8_t index; /**< Item ID. */
        std::uint8_t count; /** Item count. */
    } __attribute__((packed));
	static_assert(sizeof(struct item) == 2, "struct item should be 2 bytes");

    /**
	 * @brief Structure that represents the player bag.
	 */
    struct items_bag {
        std::uint8_t count; /**< Count of unique items. */
        struct item item[20]; /**< Item information for each item. */
        std::uint8_t terminator; /**< Terminator byte. */
    } __attribute__((packed));
	static_assert(sizeof(struct items_bag) == 42, "struct items_bag should be 42 bytes");

    /**
	 * @brief Structure that represents the player PC Item box.
	 */
    struct items_pc {
        std::uint8_t count; /**< Count of unique items. */
        struct item item[50]; /**< Item information for each item. */
        std::uint8_t terminator; /**< Terminator byte. */
    } __attribute__((packed));
	static_assert(sizeof(struct items_pc) == 102, "struct items_pc should be 102 bytes");
}
}

#endif
