#include "../../include/gen1/gen1_funcs.h"

#define CHECKSUM_INIT_OFFSET 0x2598
#define CHECKSUM_END_OFFSET  0x3522

// TODO move to general purpose c file
// that works for any gen
long get_file_size(FILE* f) {
    long _s;

    fseek(f, 0L, SEEK_END);
    _s = ftell(f);

    return _s;
}

// TODO add pointer to value for error check
FILE* _fopen(char* file_name) {
    FILE* f;

    if ((f = fopen(file_name, "r")) == NULL) {
        return NULL;
    }

    if (get_file_size(f) != 32768) {
        return NULL;
    }

    return f;
}

// TODO change 'file_name'
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
