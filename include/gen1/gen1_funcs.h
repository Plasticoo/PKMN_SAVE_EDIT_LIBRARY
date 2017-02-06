#ifndef __GEN1_FUNCS_H_
#define __GEN1_FUNCS_H_

#include "gen1_structs.h"

#include <stdio.h>

uint8_t gen1_checksum(FILE* file_name);
FILE* _fopen(char* file_name, int* errn);

#endif
