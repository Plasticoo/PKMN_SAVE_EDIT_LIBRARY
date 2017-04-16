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

u8 player_pokedex_owned_index = 43;
u8 player_pokedex_owned_res = 1;

u8 player_pokedex_seen_index = 46;
u8 player_pokedex_seen_res = 1;

u32 player_money = 543354;
u16 player_casino_coins = 504;

u8 player_badge = 1;
u8 player_option = 1;

void test_player_name()
{
    char* save_name = gen1_get_name(save.player_name);

    TEST_ASSERT_EQUAL_STRING(player_name, save_name);

    free(save_name);
}

void test_pokedex_owned()
{
    u8 save_pokedex_owned = gen1_get_pokedex(save.pokedex_owned, player_pokedex_owned_index);

    TEST_ASSERT_EQUAL_UINT8(player_pokedex_owned_res, save_pokedex_owned);
}

void test_pokedex_seen()
{
    u8 save_pokedex_seen = gen1_get_pokedex(save.pokedex_seen, player_pokedex_seen_index);

    TEST_ASSERT_EQUAL_UINT8(player_pokedex_seen_res, save_pokedex_seen);
}

void test_money()
{
    u32 save_money = gen1_get_money(save.money);

    TEST_ASSERT_EQUAL_UINT32(player_money, save_money);
}

void test_casino_coins()
{
    u16 save_casino_coins = gen1_get_casino_coins(save.casino_coins);

    TEST_ASSERT_EQUAL_UINT16(player_casino_coins, save_casino_coins);
}

void test_badge()
{
	u8 save_badge = gen1_get_badge(save.badges, BADGE_EARTH);

	TEST_ASSERT_EQUAL_UINT8(player_badge, save_badge);
}

void test_options()
{
	u8 save_option = gen1_get_option(save.options, OPTION_TEXT_SPEED_FAST);

	TEST_ASSERT_EQUAL_UINT8(player_option, save_option);
}

void write_to_save(struct gen1_pkmn_file_struct *sav)
{
    gen1_set_name(sav->player_name, player_name, strlen(player_name));
    gen1_set_pokedex(sav->pokedex_owned, player_pokedex_owned_index);
    gen1_set_pokedex(sav->pokedex_seen, player_pokedex_seen_index);
    gen1_set_money(sav->money, player_money);
    gen1_set_casino_coins(sav->casino_coins, player_casino_coins);
	gen1_set_badge(sav->badges, BADGE_EARTH);
	gen1_set_option(sav->options, OPTION_TEXT_SPEED_FAST);
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
    RUN_TEST(test_pokedex_owned);
    RUN_TEST(test_pokedex_seen);
    RUN_TEST(test_money);
	RUN_TEST(test_badge);
	RUN_TEST(test_casino_coins);
	RUN_TEST(test_options);

    return UNITY_END();
}
