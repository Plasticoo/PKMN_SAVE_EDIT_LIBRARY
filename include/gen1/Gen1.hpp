#ifndef _PKMN_GEN1_HPP_
#define _PKMN_GEN1_HPP_

#include "Constants.hpp"
#include "IGlobal.hpp"
#include "Rom.hpp"

#include <memory>

struct Gen1 : IGlobal {
    Gen1(std::unique_ptr<Rom>&& r) : m_rom(std::move(r))
    {
    }

    std::uint8_t get_checksum() const override;
    std::uint8_t calc_checksum() override;

    private:
        std::unique_ptr<Rom> m_rom;
};

#endif
