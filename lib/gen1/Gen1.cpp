#include "Gen1.hpp"

std::uint8_t Gen1::get_checksum() const
{
    return m_rom->data[0];
}

std::uint8_t Gen1::calc_checksum()
{
    std::uint8_t checksum{ 0 };
    for (auto i = C::GEN1::OFFSETS::CHECKSUM_INIT_OFFSET;
         i <= C::GEN1::OFFSETS::CHECKSUM_END_OFFSET; i++) {
        checksum += m_rom->data[i];
    }
    return ~checksum;
}
