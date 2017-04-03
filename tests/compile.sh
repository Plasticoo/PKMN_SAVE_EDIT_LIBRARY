#!/bin/bash

gcc -Wall -Wextra -ggdb -I../include checksum_test.c ../lib/gen1/gen1_funcs.c -o checksum_test
gcc -Wall -Wextra -ggdb -I../include file_load_test.c ../lib/gen1/gen1_structs.c ../lib/gen1/gen1_funcs.c ../lib/gen1/gen1_math.c -o file_load_test -lm
gcc -Wall -Wextra -ggdb -I../include number_concat_test.c ../lib/gen1/gen1_math.c -o number_concat_test -lm

gcc -std=gnu11 -Wall -Wextra -ggdb -I../include unit_tests.c unity/unity.c ../lib/utils.c ../lib/gen1/gen1_funcs.c ../lib/gen1/gen1_math.c ../lib/gen1/gen1_structs.c -o unit_tests -lm -DDEBUG
