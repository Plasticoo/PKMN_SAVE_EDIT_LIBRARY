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

void print_hexmap(u8* array, int size)
{
	int i;

	for(i = 0; i < size; i++) {
		if(i == 0) {
			printf("\n0x%04X - %02X ", i, array[i]);
		} else if(i >= 32 && i % 32 == 0) {
			printf("\n0x%04X - %02X ", i, array[i]);
		} else {
			printf("%02X ", array[i]);
		}
	}

	putchar('\n');
}
