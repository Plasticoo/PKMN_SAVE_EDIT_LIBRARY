#ifndef _PKMN_UTILS_HPP_
#define _PKMN_UTILS_HPP_

#include <cinttypes>
#include <climits>
#include <cstring>
#include <math.h>
#include <bitset>
#include <vector>
#include <algorithm>

namespace Utils
{
constexpr auto __int_concat(const std::uint32_t x, const std::uint32_t y) -> std::uint32_t;

auto __bcd_to_dec(std::uint8_t const * buffer, std::size_t const num_bytes) -> std::uint32_t;
auto __dec_to_bcd(std::uint32_t const num, std::uint8_t* buffer_out) -> void;

auto __bcd_to_dec_alt(std::uint8_t const * buffer, std::size_t const num_bytes, int const offset) -> std::uint32_t;
auto __dec_to_bcd_alt(std::uint32_t const num, std::uint8_t* buffer_out, int size) -> void;

auto set_clear_bits(std::uint8_t* x, std::uint8_t n) -> void;

auto n_digits(std::uint32_t n) -> std::uint8_t;

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
