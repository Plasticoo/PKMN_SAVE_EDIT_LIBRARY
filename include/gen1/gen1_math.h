#ifndef __GEN1_MATH_H_
#define __GEN1_MATH_H_

#include <inttypes.h>

#include <sys/types.h>

uint32_t __bcd_to_dec(const uint8_t* buffer, size_t num_bytes);
void __dec_to_bcd(uint32_t num, uint8_t* buffer_out);
uint32_t __int_concat(uint32_t x, uint32_t y);

#endif
