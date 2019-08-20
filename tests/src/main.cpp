#define CATCH_CONFIG_MAIN

#include <iostream>
#include <cstdio>

#include "catch2/catch.hpp"

#include "RomInterface.hpp"
#include "Gen1.hpp"

TEST_CASE("Generation 1 class gets correct information")
{
	auto _rom = std::make_unique<Rom32kb>("../../saves/yellow.sav");

	SECTION("File is loaded correctly and has correct size")
    {
        REQUIRE(_rom->get_size() == 0x8000);
    }

    auto gen1 = new Gen1(std::move(_rom));

	SECTION("Player name is ASH")
	{
		REQUIRE(gen1->get_player_name() == "ASH");
	}

	SECTION("Rival name is GARY")
	{
		REQUIRE(gen1->get_rival_name() == "GARY");
	}

    SECTION("Number in Pokedex Owned is 151")
    {
        REQUIRE(gen1->get_pokedex_owned(151 - 1) == true);
    }

    SECTION("Number in Pokedex Owned is 151")
    {
        REQUIRE(gen1->get_pokedex_seen(151 - 1) == true);
    }

    SECTION("Money is 390890")
    {
        REQUIRE(gen1->get_money() == 390890);
    }

	SECTION("Casino Coins is 0")
    {
        REQUIRE(gen1->get_casino_coins() == 0);
    }

	SECTION("Time played is 122:20:58:10")
	{
		auto time_played = Gen1Structs::pkmn_time();
		gen1->get_time_played(&time_played);

		SECTION("Maximum time not reached")
		{
			REQUIRE(time_played.maxed == 0);
		}

		SECTION("Hours is 122")
		{
			REQUIRE(time_played.hours == 122);
		}

		SECTION("Minutes is 20")
		{
			REQUIRE(time_played.minutes == 20);
		}

		SECTION("Seconds is 58")
		{
			REQUIRE(time_played.seconds == 58);
		}

		SECTION("Frames is 10")
		{
			REQUIRE(time_played.frames == 10);
		}
	}

//

	SECTION("Every gym is completed")
	{
		REQUIRE(gen1->get_badge(Gen1Enums::badges::BADGE_BOULDER) == 1);
		REQUIRE(gen1->get_badge(Gen1Enums::badges::BADGE_CASCADE) == 1);
		REQUIRE(gen1->get_badge(Gen1Enums::badges::BADGE_THUNDER) == 1);
		REQUIRE(gen1->get_badge(Gen1Enums::badges::BADGE_RAINBOW) == 1);
		REQUIRE(gen1->get_badge(Gen1Enums::badges::BADGE_SOUL) == 1);
		REQUIRE(gen1->get_badge(Gen1Enums::badges::BADGE_MARSH) == 1);
		REQUIRE(gen1->get_badge(Gen1Enums::badges::BADGE_VOLCANO) == 1);
		REQUIRE(gen1->get_badge(Gen1Enums::badges::BADGE_EARTH) == 1);
	}

	SECTION("Options are all set")
	{
		REQUIRE(gen1->get_option(Gen1Enums::options::TEXT_SPEED) == 1);
		REQUIRE(gen1->get_option(Gen1Enums::options::SOUND) == 0);
		REQUIRE(gen1->get_option(Gen1Enums::options::BATTLE_STYLE) == 0);
		REQUIRE(gen1->get_option(Gen1Enums::options::BATTLE_EFFECTS) == 1);
	}

	SECTION("Pikachu friendship is 103")
	{
		REQUIRE(gen1->get_pikachu_friendship() == 103);
	}
}
