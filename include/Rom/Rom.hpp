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

    void load(std::filesystem::path& file);
    std::size_t get_size() const;
    std::uint8_t get_type() const;

    void set_type();
};

#endif
