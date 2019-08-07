#ifndef _PKMN_CONSTANTS_HPP_
#define _PKMN_CONSTANTS_HPP_

#include <array>
#include <cinttypes>

namespace C
{
    namespace GB
    {
        constexpr std::uint32_t ROM_SIZE = 32768;
    }

    namespace GBA
    {
        constexpr std::uint32_t ROM_SIZE = 131072;
    }

    namespace GEN1
    {
		namespace SIZES
		{
			constexpr std::uint32_t FONT = 0x100;
			constexpr std::uint32_t FILE = 0x8000;
			constexpr std::uint32_t BOX = 20;
			constexpr std::uint32_t OPTIONS = 13;
		}

        constexpr std::array<std::uint8_t, C::GEN1::SIZES::FONT> FONT = {
            '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
            '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
            '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
            '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
            '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
            '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
            '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
            '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
            '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
            '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', ' ', 'A', 'B',
            'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
            'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '(', ')',
            ':', ';', '[', ']', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
            'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
            'w', 'x', 'y', 'z', '?', '?', '?', '?', '?', '?', '?', '?', '?',
            '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
            '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
            '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
            '?', '?', '?', '?', '?', '?', '?', '?', '.', '/', ',', '?', '0',
            '1', '2', '3', '4', '5', '6', '7', '8', '9'
        };

        namespace OPTIONS
		{
            constexpr std::array<std::uint8_t, C::GEN1::SIZES::OPTIONS> LOOKUP_TABLE = {
                0x1,  0x2,  0x5, 0x0,  0x0, 0x10, 0x10,
                0x20, 0x30, 0x0, 0x40, 0x0, 0x80
            };

            constexpr std::uint8_t OPTION_TEXT_SPEED_MASK = 0x7;
            constexpr std::uint8_t OPTION_SOUND_MASK = 0x30;
            constexpr std::uint8_t OPTION_BATTLE_STYLE_MASK = 0x40;
            constexpr std::uint8_t OPTION_BATTLE_EFFECTS_MASK = 0x80;
        }

        namespace ROM
        {
            constexpr std::uint32_t CHECKSUM_FROM = 0x2598;
            constexpr std::uint32_t CHECKSUM_TO = 0x3522;
        }

        namespace OFFSETS
        {
			constexpr std::uint16_t PLAYER_NAME = 0x2598;
			constexpr std::uint16_t POKEDEX_OWNED = 0x25A3;
			constexpr std::uint16_t POKEDEX_SEEN = 0x25B6;
			constexpr std::uint16_t MONEY = 0x25F3;
			constexpr std::uint16_t RIVAL_NAME = 0x25F6;
			constexpr std::uint16_t OPTIONS = 0x2601;
			constexpr std::uint16_t BADGES = 0x2602;
			constexpr std::uint16_t PLAYER_TRAINER_ID = 0x2605;
			constexpr std::uint16_t PIKACHU_FRIENDSHIP = 0x271C;
			constexpr std::uint16_t CURRENT_PC_BOX = 0x284C;
			constexpr std::uint16_t CASINO_COINS = 0x2850;
			constexpr std::uint16_t CURRENT_BOX_LIST = 0x30C0;
			constexpr std::uint16_t CHECKSUM = 0x3523;

            constexpr std::uint16_t CHECKSUM_INIT_OFFSET = 0x2598;
            constexpr std::uint16_t CHECKSUM_END_OFFSET = 0x3522;
        }
    }

    namespace GEN2
    {
        namespace OFFSETS
        {

        }
    }
}

#endif
