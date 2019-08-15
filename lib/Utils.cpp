#include "Utils.hpp"

namespace Utils {

constexpr auto __int_concat(const std::uint32_t x, const std::uint32_t y) -> std::uint32_t
{
    std::uint32_t _p = 10;

    while(y >= _p) {
        _p *= 10;
    }

    return x * _p + y;
}

auto __bcd_to_dec(const std::uint8_t* buffer, const std::size_t num_bytes) -> std::uint32_t
{
    ssize_t i;
    std::uint32_t res;
    std::uint32_t mult = 100;
    res = (buffer[num_bytes-1] & 0x0F) + ((buffer[num_bytes-1] >> 4) * 10);

    for(i = (ssize_t)(num_bytes-2); i >= 0; i--) {
        res  += ((buffer[i] & 0x0F) * mult);
        mult *= 10;
        res  += ((buffer[i] >> 4) * mult);
        mult *= 10;
    }

    return res;
}

auto __dec_to_bcd(const std::uint32_t num, std::uint8_t* buffer_out) -> void
{
    std::uint32_t log10_num = (std::uint32_t)log10((double)num);
	std::size_t num_bytes = (std::size_t)((log10_num + 1) / 2);

    if(log10_num % 2 == 0) {
        ++num_bytes;
    }

    std::memset(buffer_out, 0, num_bytes);
	std::size_t mult = 100;

    buffer_out[num_bytes-1] = (((num % 100) / 10) << 4) | (num % 10);
    for(ssize_t i = (ssize_t)(num_bytes-2); i >= 0; i--) {
        buffer_out[i] = (uint8_t)((((num % (mult*100)) / (mult*10)) << 4) |
                                  ((num % (mult*10)) / mult));
        mult *= 100;
    }
}

auto set_clear_bits(std::uint8_t *x, std::uint8_t n) -> void
{
    *x = (*x & n) | n;
}

}
