#ifndef _PKMN_ROM_HPP_
#define _PKMN_ROM_HPP_

#include <array>
#include <cinttypes>
#include <filesystem>

struct Rom
{
    // TODO: array is the best
    //std::vector<std::uint8_t> data;
    std::array<std::uint8_t, 131072> data;
    std::uint8_t type;

    Rom(std::filesystem::path& file);

    auto load(std::filesystem::path& file) -> void;
    auto get_size() const -> std::size_t;
    auto get_type() const -> std::uint8_t;

    auto set_type() -> void;
};

#endif
