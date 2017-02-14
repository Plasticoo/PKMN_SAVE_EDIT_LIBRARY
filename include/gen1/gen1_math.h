#ifndef __GEN1_MATH_H_
#define __GEN1_MATH_H_

#include <inttypes.h>

uint8_t __bcd_to_dec(uint8_t _bcd);
uint8_t __dec_to_bcd(uint8_t _dec);
uint32_t __int_concat(uint32_t x, uint32_t y);

#endif
