#ifndef __GEN1_FUNCS_H_
#define __GEN1_FUNCS_H_

#include "gen1_structs.h"

#include <stdio.h>

FILE* _fopen(char* file_name, int* errn);


uint8_t gen1_checksum_file(FILE* f);
uint8_t gen1_checksum_map(uint8_t* file_map);

// TODO give different names
uint8_t* load_file(FILE* f);
void gen1_load_file(struct gen1_pkmn_file_struct *file_struct, uint8_t *file_map);

#endif
