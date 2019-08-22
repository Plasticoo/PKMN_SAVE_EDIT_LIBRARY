#ifndef _PKMN_ROM64KB_HPP_
#define _PKMN_ROM64KB_HPP_

#include "RomInterface.hpp"

#include <array>
#include <cinttypes>
#include <filesystem>

struct Rom64kb: RomInterface {
    std::array<std::uint8_t, 0xffff> data;
    std::uint8_t type;

    Rom64kb(std::filesystem::path const& file);

    auto load(std::filesystem::path const& file) -> void;
    auto get_size() const -> std::size_t;
};

#endif
