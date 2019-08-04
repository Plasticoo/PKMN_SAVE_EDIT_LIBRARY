#ifndef _PKMN_GEN1_HPP_
#define _PKMN_GEN1_HPP_

#include "Constants.hpp"
#include "IGlobal.hpp"
#include "Rom.hpp"

#include <memory>

//template<class Derived>
struct Gen1 : IGlobal {
    Gen1(std::unique_ptr<Rom>&& r) : m_rom(std::move(r))
    {
		//static_assert(std::is_base_of<Rom, Derived>::value, "Derived not derivative of Rom.");
    }

    std::uint8_t get_checksum() const override;
    std::uint8_t calc_checksum() override;

    private:
        std::unique_ptr<Rom> m_rom;
};

#endif
