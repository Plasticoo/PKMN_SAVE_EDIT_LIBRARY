#ifndef _PKMN_IGLOBAL_HPP_
#define _PKMN_IGLOBAL_HPP_

#include <cinttypes>

struct IGlobal
{
	virtual std::uint8_t get_checksum() const = 0;
	virtual std::uint8_t calc_checksum() = 0;
};

#endif
