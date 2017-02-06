#include "../../include/gen1/gen1_funcs.h"

#define CHECKSUM_INIT_OFFSET 0x2598
#define CHECKSUM_END_OFFSET  0x3522

#define FILE_OPEN_ERR 1
#define FILE_SIZE_ERR 2

#define FILE_SIZE 32768
#define FILE_CONTENTS_SIZE 0x54B4
#define FILE_INIT_ADDRESS 0x2598

// TODO move to general purpose c file
// that works for any gen
long get_file_size(FILE* f) {
    long _s;

    fseek(f, 0L, SEEK_END);
    _s = ftell(f);

    return _s;
}

FILE* _fopen(char* file_name, int* errn) {
    FILE* f;

    if ((f = fopen(file_name, "r")) == NULL) {
        *errn = FILE_OPEN_ERR;
        return NULL;
    }

    if (get_file_size(f) != 32768) {
        fclose(f);

        *errn = FILE_SIZE_ERR;
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

void load_file(FILE* f, uint8_t *file_map) {
    int i;

    for (i = 0; i < FILE_SIZE; i++) {
        fread(&file_map[i], 1, 1, f);
    }
}

// TODO Create function to print hex of file contents
/* uint8_t gen1_load_file(struct gen1_pkmn_file_struct* file_struct, FILE* f) { */
/*     int i; */

/*     uint8_t file_map[FILE_SIZE]; */

/*     for (i = 0; i < FILE_SIZE; i++) { */
/*         fread(&file_map[i], 1, 1, f); */
/*     } */

/*     file_struct */
/* } */
