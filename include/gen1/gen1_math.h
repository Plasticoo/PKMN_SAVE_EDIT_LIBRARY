#ifndef __GEN1_MATH_H_
#define __GEN1_MATH_H_

#include <inttypes.h>

#include <sys/types.h>

u32 __bcd_to_dec(const u8* buffer, size_t num_bytes);
void __dec_to_bcd(u32 num, u8* buffer_out);
u32 __int_concat(u32 x, u32 y);

#endif
