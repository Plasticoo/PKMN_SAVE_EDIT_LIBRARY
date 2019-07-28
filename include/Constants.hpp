#ifndef _PKMN_CONSTANTS_HPP_
#define _PKMN_CONSTANTS_HPP_

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
        namespace ROM
        {
            constexpr std::uint32_t CHECKSUM_FROM = 0x2598;
            constexpr std::uint32_t CHECKSUM_TO = 0x3522;
        }

        namespace OFFSETS
        {
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
