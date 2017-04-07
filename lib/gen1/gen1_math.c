#include "gen1/gen1.h"

#include <math.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

#include <sys/types.h>

u32 __int_concat(u32 x, u32 y)
{
    u32 _p = 10;

    while(y >= _p) {
        _p *= 10;
    }

    return x * _p + y;
}

static int bcd_decimal(uint8_t hex)
{
    assert(((hex & 0xF0) >> 4) < 10);  // More significant nybble is valid
    assert((hex & 0x0F) < 10);         // Less significant nybble is valid
    int dec = ((hex & 0xF0) >> 4) * 10 + (hex & 0x0F);
    return dec;
}

static unsigned int dec2bcd(unsigned int num) // num is now 65535
{
    unsigned int ones = 0;
    unsigned int tens = 0;
    unsigned int temp = 0;

    ones = num%10; // 65535%10 = 5
    temp = num/10; // 65535/10 = 6553
    tens = temp<<4;  // what's displayed is by tens is actually the lower
                     // 4 bits of tens, so tens is 6553%16=9
    return (tens + ones);// so the result is 95
}

u32 HornerScheme(u32 Num,u32 Divider,u32 Factor)
{
   u32 Remainder=0,Quotient=0,Result=0;
   Remainder=Num%Divider;
   Quotient=Num/Divider;
   if(!(Quotient==0&&Remainder==0))
   Result+=HornerScheme(Quotient,Divider,Factor)*Factor+Remainder;
   return Result;
}

u32 __bcd_to_dec(const u8* buffer, size_t num_bytes)
{
    ssize_t i;
    u32 res;
    u32 mult = 100;

    res = (buffer[num_bytes-1] & 0x0F) + ((buffer[num_bytes-1] >> 4) * 10);

    for(i = (ssize_t)(num_bytes-2); i >= 0; i--) {
        res  += ((buffer[i] & 0x0F) * mult);
        mult *= 10;
        res  += ((buffer[i] >> 4) * mult);
        mult *= 10;
    }

    // tests
    int val1 = bcd_decimal(buffer[0]);
    int val2 = bcd_decimal(buffer[1]);
    int val3 = bcd_decimal(buffer[2]);

    PDEBUG("vals: %d %d %d - res: %u\n", val1, val2, val3, res);

    return res;
}

void __dec_to_bcd(u32 num, u8* buffer_out)
{
    u32 log10_num = (uint32_t)log10((double)num);
    size_t num_bytes = (size_t)((log10_num + 1) / 2);
    if(log10_num % 2 == 0) {
        ++num_bytes;
    }

    memset(buffer_out, 0, num_bytes);
    size_t mult = 100;

    buffer_out[num_bytes-1] = (((num % 100) / 10) << 4) | (num % 10);
    for(ssize_t i = (ssize_t)(num_bytes-2); i >= 0; i--) {
        buffer_out[i] = (uint8_t)((((num % (mult*100)) / (mult*10)) << 4) |
                                  ((num % (mult*10)) / mult));
        mult *= 100;
    }

    //u32 val = dec2bcd(num);
    u32 val = HornerScheme(num, 10, 0x10);
    u8 byte1 = (val & 255);
    u8 byte2 = (val & 65280) >> 8;
    u8 byte3 = (val & 16711680) >> 16;

    u8 buf[] = {byte3, byte2, byte1};
    u32 res = __bcd_to_dec(buf, 3);

    PDEBUG("val: %d %d %d %d | %d - res: 0x%.2X 0x%.2X 0x%.2X\n", val, byte1, byte2, byte3, res, buffer_out[0], buffer_out[1], buffer_out[2]);
}
