#include "unity/unity.h"

#include "defines.h"
#include "utils.h"

#include "gen1/gen1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

FILE* f;
struct gen1_pkmn_file_struct save;

char *player_name = "teste";
char *rival_name = "topkek";

u8 player_pokedex_owned_index = 43;
u8 player_pokedex_owned_res = 1;

u8 player_pokedex_seen_index = 46;
u8 player_pokedex_seen_res = 1;

u32 player_money = 543354;
u16 player_casino_coins = 504;

u8 player_badge = 1;
u8 player_option = 1;

u8 current_pc_box = 13;

u16 hours = 867;
u8 minutes = 34;
u8 seconds = 54;

void test_player_name()
{
    char* save_name = gen1_get_name(save.player_name);

    TEST_ASSERT_EQUAL_STRING(player_name, save_name);

    free(save_name);
}

void test_rival_name()
{
	char* save_name = gen1_get_name(save.rival_name);

	TEST_ASSERT_EQUAL_STRING(rival_name, save_name);

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

void test_current_pc_box()
{
	u8 save_current_pc_box = gen1_get_current_pc_box(save.current_pc_box);

	TEST_ASSERT_EQUAL_UINT8(current_pc_box, save_current_pc_box);
}

void test_time()
{
	struct gen1_pkmn_time _t = {.hours = 0, .minutes = 0, .seconds = 0};

	gen1_get_time_played(save.time_played, &_t);

	TEST_ASSERT_EQUAL_UINT16(hours, _t.hours);
	TEST_ASSERT_EQUAL_UINT8(minutes, _t.minutes);
	TEST_ASSERT_EQUAL_UINT8(seconds, _t.seconds);
}

void write_to_save(struct gen1_pkmn_file_struct *sav)
{
    gen1_set_name(sav->player_name, player_name, strlen(player_name));
    gen1_set_name(sav->rival_name, rival_name, strlen(rival_name));
    gen1_set_pokedex(sav->pokedex_owned, player_pokedex_owned_index);
    gen1_set_pokedex(sav->pokedex_seen, player_pokedex_seen_index);
    gen1_set_money(sav->money, player_money);
    gen1_set_casino_coins(sav->casino_coins, player_casino_coins);
	gen1_set_option(sav->options, OPTION_TEXT_SPEED_FAST);
	gen1_set_badge(sav->badges, BADGE_EARTH);
	//gen1_set_pikachu_friendship(sav->pikachu_friendship, 36);
	gen1_set_current_pc_box(sav->current_pc_box, current_pc_box);
	gen1_set_time_played(sav->time_played, hours,  minutes,  seconds);
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
	RUN_TEST(test_rival_name);
    RUN_TEST(test_pokedex_owned);
    RUN_TEST(test_pokedex_seen);
    RUN_TEST(test_money);
	RUN_TEST(test_badge);
	RUN_TEST(test_casino_coins);
	RUN_TEST(test_options);
	RUN_TEST(test_current_pc_box);
	RUN_TEST(test_time);

    return UNITY_END();
}
