#include "../include/utils.h"

static inline void set_bit(u8 *x, u8 n)
{
    *x |= (1 << n);
}

static inline void clear_bit(u8 *x, u8 n)
{
    *x &= ~(1 << n);
}

static inline void set_clear_bit(u8 *x, u8 n)
{
    *x = (*x & ~(1 << n)) | (1 << n);
}

static inline void set_clear_bits(u8 *x, u8 n)
{
    *x = (*x & n) | n;
}
