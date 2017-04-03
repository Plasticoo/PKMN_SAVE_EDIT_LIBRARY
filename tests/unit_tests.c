#include "unity/unity.h"

#include "defines.h"
#include "utils.h"

#include "gen1/gen1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* f;
struct gen1_pkmn_file_struct save;

char *player_name = "teste";

void test_player_name(void)
{
    TEST_ASSERT_EQUAL_STRING(player_name, gen1_get_name(save.player_name));
}

void write_to_save(struct gen1_pkmn_file_struct *sav)
{
    gen1_set_name(sav->player_name, player_name, strlen(player_name));
}

int main(int argc, char** argv)
{
    int errn;

    if(argc != 2) {
        PDEBUG("number of arguments invalid");
        return EXIT_FAILURE;
    }

    if((f = _fopen(argv[1], 32768, &errn)) == NULL) {
        PDEBUG("error opening file.");
        return EXIT_FAILURE;
    }

    gen1_load_file(&save, f);
    printf("File loaded.\n");
    write_to_save(&save);
    printf("Wrote to save.\n");
    gen1_set_checksum(&save);

    printf("Preparing for unit tests...\n");

    UNITY_BEGIN();

    RUN_TEST(test_player_name);

    return UNITY_END();
}
