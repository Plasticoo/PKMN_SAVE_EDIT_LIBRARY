#!/bin/bash

gcc -Wall checksum_test.c ../lib/gen1/gen1_funcs.c -o checksum_test
gcc -Wall file_load_test.c ../lib/gen1/gen1_funcs.c ../lib/gen1/gen1_prints.c -o file_load_test
