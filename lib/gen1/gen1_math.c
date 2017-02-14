#include "../../include/gen1/gen1_math.h"

#include <math.h>
#include <inttypes.h>
#include <string.h>

#include <sys/types.h>

/* uint8_t __bcd_to_dec(uint8_t _bcd) { */
/*     return (((_bcd & 0xF0) >> 4) * 10) + (_bcd & 0x0F); */
/* } */

/* uint8_t __dec_to_bcd(uint8_t _dec) { */
/*     return ((_dec / 10) << 4) | (_dec % 10); */
/* } */

uint32_t __int_concat(uint32_t x, uint32_t y) {
    uint32_t _p = 10;

    while(y >= _p) {
        _p *= 10;
    }

    return x * _p + y;
}

uint32_t __bcd_to_dec(const uint8_t* buffer, size_t num_bytes) {
    ssize_t i;
    uint32_t res;
    uint32_t mult = 100;

    res = (buffer[num_bytes-1] & 0x0F) + ((buffer[num_bytes-1] >> 4) * 10);

    for(i = (ssize_t)(num_bytes - 2); i >= 0; i--) {
        res  += (buffer[i] & 0x0F) * mult;
        mult *= 10;
        res  += (buffer[i] >> 4) * mult;
        mult *= 10;
    }

    return res;
}

// TODO modify return type
void __dec_to_bcd(uint32_t num, uint8_t* buffer_out) {
    size_t n_bytes;
    size_t mult = 100;
    uint32_t log10_res;

    // Find the number of needed bytes
    log10_res = (uint32_t)log10((double)num);
    n_bytes = (size_t)((log10_res + 1) / 2);
    if(log10_res % 2 == 0) {
        ++n_bytes;
    }

    memset(buffer_out, 0, n_bytes);

    buffer_out[n_bytes-1] = (((num % 100) / 10) << 4) | (num % 10);
    for(ssize_t i = (ssize_t)(n_bytes - 2); i >= 0; i--) {
        buffer_out[i] = (uint8_t)((((num % (mult*100)) / (mult*10)) << 4) |
                                  ((num % (mult*10)) / mult));
        mult *= 100;
    }
}
