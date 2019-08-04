#ifndef _PKMN_UTILS_HPP_
#define _PKMN_UTILS_HPP_

#include <cinttypes>
#include <cstring>

#include <math.h>

constexpr std::uint32_t __int_concat(const std::uint32_t x, const std::uint32_t y);
std::uint32_t __bcd_to_dec(const std::uint8_t* buffer, const std::size_t num_bytes);
void __dec_to_bcd(const std::uint32_t num, std::uint8_t* buffer_out);

#endif
