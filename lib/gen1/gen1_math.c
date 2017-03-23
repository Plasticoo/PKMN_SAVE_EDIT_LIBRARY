#include "../../include/gen1/gen1.h"

#include <math.h>
#include <inttypes.h>
#include <string.h>

#include <sys/types.h>

u32 __int_concat(u32 x, u32 y)
{
    u32 _p = 10;

    while(y >= _p) {
        _p *= 10;
    }

    return x * _p + y;
}

u32 __bcd_to_dec(const u8* buffer, size_t num_bytes)
{
    ssize_t i;
    u32 res;
    u32 mult = 100;

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
void __dec_to_bcd(u32 num, u8* buffer_out)
{
    size_t n_bytes;
    size_t mult = 100;
    u32 log10_res;

    // Find the number of needed bytes
    log10_res = (u32)log10((double)num);
    n_bytes = (size_t)((log10_res + 1) / 2);
    if(log10_res % 2 == 0) {
        ++n_bytes;
    }

    memset(buffer_out, 0, n_bytes);

    buffer_out[n_bytes-1] = (((num % 100) / 10) << 4) | (num % 10);
    for(ssize_t i = (ssize_t)(n_bytes - 2); i >= 0; i--) {
        buffer_out[i] = (u8)((((num % (mult*100)) / (mult*10)) << 4) |
                                  ((num % (mult*10)) / mult));
        mult *= 100;
    }
}
