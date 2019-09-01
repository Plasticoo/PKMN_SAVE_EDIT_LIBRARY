#ifndef _PKMN_UTILS_HPP_
#define _PKMN_UTILS_HPP_

#include "Rom/Rom32kb.hpp"
#include "Rom/Rom64kb.hpp"

#include <cinttypes>
#include <climits>
#include <cstring>
#include <math.h>

namespace Utils
{
constexpr auto __int_concat(const std::uint32_t x, const std::uint32_t y) -> std::uint32_t;

auto __bcd_to_dec(const std::uint8_t* buffer, const std::size_t num_bytes) -> std::uint32_t;
auto __dec_to_bcd(const std::uint32_t num, std::uint8_t* buffer_out) -> void;

auto set_clear_bits(std::uint8_t* x, std::uint8_t n) -> void;

template<typename T>
T swap_endian(T u)
{
	static_assert(CHAR_BIT == 8, "CHAR_BIT != 8");

	union {
		T u;
		unsigned char u8[sizeof(T)];
	} source, dest;

	source.u = u;

	for (size_t k = 0; k < sizeof(T); k++)
		dest.u8[k] = source.u8[sizeof(T) - k - 1];

	return dest.u;
}
}

#endif
