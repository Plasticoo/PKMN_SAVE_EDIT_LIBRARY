#ifndef __UTILS_H_
#define __UTILS_H_

#include "defines.h"
#include <inttypes.h>

// bit operations
static inline void set_bit(u8 *x, u8 n);
static inline void clear_bit(u8 *x, u8 n);
static inline void set_clear_bit(u8 *x, u8 n);
static inline void set_clear_bits(u8 *x, u8 n);

// prints
void print_hexmap(u8* array, int size);

#endif
