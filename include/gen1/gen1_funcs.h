#ifndef __GEN1_FUNCS_H_
#define __GEN1_FUNCS_H_

#include "gen1_structs.h"

#include <stdio.h>

FILE* _fopen(char* file_name, u32 fsize, int* errn);


u8 gen1_checksum_file(FILE* f);
u8 gen1_checksum_map(u8* file_map);

// TODO give different names
u8* load_file(FILE* f);
void gen1_load_file(struct gen1_pkmn_file_struct *file_struct, FILE* f);

#endif
