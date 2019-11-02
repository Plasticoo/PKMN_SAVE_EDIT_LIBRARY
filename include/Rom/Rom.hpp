#ifndef _PKMN_ROM_HPP_
#define _PKMN_ROM_HPP_

#include "Constants.hpp"
#include "RomInterface.hpp"

#include <array>
#include <cinttypes>
#include <filesystem>
#include <fstream>
#include <memory>

struct Rom32kb{};
struct Rom64kb{};

template<typename T>
struct Rom : RomInterface {

	std::array<std::uint8_t, 0x8000> data;

	Rom(std::filesystem::path const& file) {
		this->load(file);
	}

    auto load(std::filesystem::path const& file) -> void override
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

    auto get_size() const -> std::size_t override {
		return this->data.size();
	}
};

template<>
struct Rom<Rom32kb> : RomInterface
{
	bool a = true;
	std::array<std::uint8_t, 0x8000> data;

	Rom(std::filesystem::path const& file) {
		this->load(file);
	}

    auto load(std::filesystem::path const& file) -> void override
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

    auto get_size() const -> std::size_t override {
		return this->data.size();
	}
};

template<>
struct Rom<Rom64kb> : RomInterface
{
	std::array<std::uint8_t, 0x10000> data;

	Rom(std::filesystem::path const& file) {
		this->load(file);
	}

    auto load(std::filesystem::path const& file) -> void override
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

    auto get_size() const -> std::size_t override {
		return this->data.size();
	}
};

#endif
