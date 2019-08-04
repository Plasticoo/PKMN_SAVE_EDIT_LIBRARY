#ifndef _PKMN_BITSET_HPP_
#define _PKMN_BITSET_HPP_

#include <bitset>
#include <climits>

/// Returns the number of bits used to represent type `T`.
template <typename T>
constexpr unsigned num_bits(T = 0) {
    return sizeof(T) * CHAR_BIT;
}

/// Returns index of the most significant bit of type `T`.
template <typename T>
constexpr unsigned msb_idx(T = 0) {
    return num_bits<T>() - 1;
}

/// Returns a value of type `T` with a single bit set at index `idx`.
template <typename T>
constexpr T bit_flag(unsigned idx) {
    return static_cast<T>(1) << idx;
}

/// Returns a value of type `T` with MSB set only.
template <typename T>
constexpr T msb_flag() {
    return static_cast<T>(1) << msb_idx<T>();
}

/// Tests if the bit at index `idx` of `x` is set.
template <typename T>
constexpr bool test_bit(T x, unsigned idx) {
    return x & bit_flag<T>(idx);
}

/// Tests if the MSB of `x` is set.
template <typename T>
constexpr bool test_msb(T x) {
    return test_bit(x, msb_idx(x));
}

/// Sets the bit at index `idx` of `x` and returns the result.
template <typename T>
constexpr T set_bit(T x, unsigned idx) {
    return x | bit_flag<T>(idx);
}

/// Sets the MSB of `x` and returns the result.
template <typename T>
constexpr T set_msb(T x) {
    return set_bit(x, msb_idx<T>());
}

/// Clears the bit at index `idx` of `x` and returns the result.
template <typename T>
constexpr T clear_bit(T x, unsigned idx) {
    return x & ~bit_flag<T>(idx);
}

/// Clears the MSB of `x` and returns the result.
template <typename T>
constexpr T clear_msb(T x) {
    return clear_bit(x, msb_idx<T>());
}

/// Flips the bit at index `idx` of `x` and returns the result.
template <typename T>
constexpr T flip_bit(T x, unsigned idx) {
    return x ^ bit_flag<T>(idx);
}

/// Flips the MSB of `x` and returns the result.
template <typename T>
constexpr T flip_msb(T x) {
    return flip_bit(x, msb_idx<T>());
}

/// Returns the number of bits set in `x`.
template <typename T>
unsigned num_bits_set(T x)
{
    return static_cast<unsigned>(std::bitset<num_bits<T>()>(x).count());
}

#endif
