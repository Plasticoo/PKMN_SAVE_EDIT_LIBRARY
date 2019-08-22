#ifndef _PKMN_ROM_HPP_
#define _PKMN_ROM_HPP_

#include "RomInterface.hpp"

#include <array>
#include <cinttypes>
#include <filesystem>
#include <memory>

struct Rom: RomInterface {
    std::array<std::uint8_t, 131072> data;
    std::uint8_t type;

    Rom(std::filesystem::path const& file);

    auto load(std::filesystem::path const& file) -> void;
    auto get_size() const -> std::size_t;
};

#endif
