#!/bin/bash

gcc -Wall -ggdb checksum_test.c ../lib/gen1/gen1_funcs.c -o checksum_test
gcc -Wall -ggdb file_load_test.c ../lib/gen1/gen1_structs.c ../lib/gen1/gen1_funcs.c ../lib/gen1/gen1_prints.c -o file_load_test
gcc -Wall -ggdb number_concat_test.c ../lib/gen1/gen1_math.c -o number_concat_test
