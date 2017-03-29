#include "unity/unity.h"
#include "../include/gen1/gen1.h"

#include <stdio.h>
#include <stdlib.h>

FILE* f;
struct gen1_pkmn_file_struct save;

static const char player_name[] = "john";

void test_player_name(void)
{
    TEST_ASSERT_EQUAL_STRING(player_name, gen1_get_name(save.player_name));
}

void test_pokedex_owned(void)
{
    TEST_ASSERT_EQUAL_INT16();
}

int main(int argc, char** argv)
{
    if(argc != 2) {
        return EXIT_FAILURE;
    }

    if((f = fopen(argv[1], "r"))) {
        return EXIT_FAILURE;
    }

    gen1_load_file(&save);

    UNITY_BEGIN();

    RUN_TEST(test_player_name);

    return UNITY_END();
}
