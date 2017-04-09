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
u32 player_money = 12345;
u16 player_casino_coins = 3044;

void test_player_name(void)
{
    char* save_name = gen1_get_name(save.player_name);

    TEST_ASSERT_EQUAL_STRING(player_name, save_name);

    free(save_name);
}

void test_money(void)
{
    u32 save_money = gen1_get_money(save.money);

    TEST_ASSERT_EQUAL_UINT32(player_money, save_money);
}

void test_casino_coins()
{
    u16 save_casino_coins = gen1_get_casino_coins(save.casino_coins);

    TEST_ASSERT_EQUAL_UINT16(player_casino_coins, save_casino_coins);
}

void write_to_save(struct gen1_pkmn_file_struct *sav)
{
    gen1_set_name(sav->player_name, player_name, strlen(player_name));
    gen1_set_money(sav->money, player_money);
    gen1_set_casino_coins(sav->casino_coins, player_casino_coins);
}

int main(int argc, char** argv)
{
    int errn;

    if(argc != 2) {
        PDEBUG("number of arguments invalid");
        return EXIT_FAILURE;
    }

    if((f = gen1_fopen(argv[1], &save, &errn)) == NULL) {
        PDEBUG("error opening file: %d\n", errn);
        return EXIT_FAILURE;
    }

    printf("File loaded.\n");

    write_to_save(&save);
    printf("Wrote to save.\n");
    gen1_set_checksum(&save);

    printf("Preparing for unit tests...\n");

    UNITY_BEGIN();

    RUN_TEST(test_player_name);
    RUN_TEST(test_money);
    RUN_TEST(test_casino_coins);

    return UNITY_END();
}
