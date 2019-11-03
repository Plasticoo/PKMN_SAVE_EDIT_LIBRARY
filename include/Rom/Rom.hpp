#ifndef _PKMN_ROM_HPP_
#define _PKMN_ROM_HPP_

#include "Constants.hpp"
#include "RomInterface.hpp"
#include "Utils.hpp"

#include <array>
#include <cinttypes>
#include <filesystem>
#include <fstream>

enum class RomType {
    Rom32kb,
    Rom64kb,
    Unknown
};

RomType get_string_romtype(std::string const & s)
{
    if (s == "Rom32kb") {
        return RomType::Rom32kb;
    }
    if (s == "Rom64kb") {
        return RomType::Rom64kb;
    }

    return RomType::Unknown;
}

struct Rom32kb {
    std::array<std::uint8_t, 0x8000> data;

    Rom32kb(){};

    auto load(std::filesystem::path const& file) -> void
    {
        std::ifstream ifs(file, std::ios::binary | std::ios::in);
        if (!ifs) {
            return;
        }

        auto size = std::filesystem::file_size(file);
        if (size == 0 || size != C::GB::ROM_SIZE) {
            return;
        }

        if (ifs.read((char*)this->data.data(), size)) {
            return;
        }
    }

    auto get_size() const -> std::size_t
    {
        return this->data.size();
    }
};

struct Rom64kb {
    std::array<std::uint8_t, 0x10000> data;

    Rom64kb(){};

    auto load(std::filesystem::path const& file) -> void
    {
        std::ifstream ifs(file, std::ios::binary | std::ios::in);
        if (!ifs) {
            return;
        }

        auto size = std::filesystem::file_size(file);
        if (size == 0 || size != C::GB::ROM_SIZE) {
            return;
        }

        if (ifs.read((char*)this->data.data(), size)) {
            return;
        }
    }

    auto get_size() const -> std::size_t
    {
        return this->data.size();
    }
};

#endif
