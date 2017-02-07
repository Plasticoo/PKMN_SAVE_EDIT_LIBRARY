#!/bin/bash

gcc checksum_test.c ../lib/gen1/gen1_funcs.c -o checksum_test
gcc file_load_test.c ../lib/gen1/gen1_funcs.c -o file_load_test
