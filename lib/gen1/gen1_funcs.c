#include "../../include/gen1/gen1_funcs.h"

#define CHECKSUM_INIT_OFFSET 0x2598
#define CHECKSUM_END_OFFSET  0x3522

uint8_t gen1_checksum(FILE* file_name) {
    int i;

    uint8_t checksum = 0;
    uint8_t byte;

    fseek(file_name, CHECKSUM_INIT_OFFSET, SEEK_SET);

    for (i = 0; i <= CHECKSUM_END_OFFSET - CHECKSUM_INIT_OFFSET; i++) {
        fread(&byte, 1, 1, file_name);
        checksum += byte;
    }

    return ~checksum;
}
