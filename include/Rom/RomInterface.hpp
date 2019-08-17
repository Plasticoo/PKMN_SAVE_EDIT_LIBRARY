#ifndef _PKMN_ROMINTERFACE_HPP_
#define _PKMN_ROMINTERFACE_HPP_

#include <array>
#include <cinttypes>
#include <filesystem>
#include <memory>

struct RomInterface
{
    static auto make_rom(std::filesystem::path const& file) -> std::unique_ptr<RomInterface>;

    virtual auto load(std::filesystem::path& file) -> void;
    virtual auto get_size() const -> std::size_t;
};

#endif
