#include "../../include/gen1/gen1_math.h"

#include <inttypes.h>

uint8_t __bcd_to_dec(uint8_t _bcd) {
    return (((_bcd & 0xF0) >> 4) * 10) + (_bcd & 0x0F);
}

uint8_t __dec_to_bcd(uint8_t _dec) {
    return ((_dec / 10) << 4) | (_dec % 10);
}

uint32_t __int_concat(uint32_t x, uint32_t y) {
    uint32_t _p = 10;

    while(y >= _p) {
        _p *= 10;
    }

    return x * _p + y;
}
