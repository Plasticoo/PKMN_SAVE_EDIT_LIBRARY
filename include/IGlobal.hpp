#ifndef _PKMN_IGLOBAL_HPP_
#define _PKMN_IGLOBAL_HPP_

#include <cinttypes>

struct IGlobal {
    virtual auto get_checksum() const -> std::uint8_t = 0;
    virtual auto calc_checksum() const -> std::uint8_t = 0;
};

#endif
