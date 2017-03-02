#include "../../include/gen1/gen1_prints.h"
#include "../../include/gen1/gen1_defines.h"

#include <inttypes.h>
#include <stdio.h>

void print_hexmap(uint8_t* array, int size)
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
