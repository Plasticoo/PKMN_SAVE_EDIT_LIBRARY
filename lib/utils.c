#include "utils.h"

#include <stdio.h>
#include <string.h>

long get_file_size(FILE* f)
{
    long _s;

	fseek(f, 0L, SEEK_END);
    _s = ftell(f);
    fseek(f, 0L, SEEK_END);

	return _s;
}

FILE* _fopen(char* file_name, u32 fsize, int* errn)
{
    FILE* f;

    if ((f = fopen(file_name, "r")) == NULL) {
        *errn = FILE_OPEN_ERR;
        return NULL;
    }

    if (get_file_size(f) != fsize) {
        fclose(f);

        *errn = FILE_SIZE_ERR;
        return NULL;
    }

    return f;
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
