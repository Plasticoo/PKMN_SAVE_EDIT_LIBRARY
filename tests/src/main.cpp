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

    // SECTION("Number in Pokedex Owned is X")
    // {
    //     REQUIRE(gen1->get_pokede == "GARY");
    // }

    // SECTION("Number in Pokedex Owned is Y")
    // {
    //     REQUIRE(gen1->get_rival_name() == "GARY");
    // }

    SECTION("Money is 390890")
    {
        REQUIRE(gen1->get_money() == 390890);
    }

	SECTION("Casino Coins is 0")
    {
        REQUIRE(gen1->get_casino_coins() == 0);
    }

	SECTION("Time played is 00:01:00")
	{
		auto time_played = Gen1Structs::pkmn_time();
		gen1->get_time_played(&time_played);

		SECTION("Maximum time not reached")
		{
			REQUIRE(time_played.maxed == 0);
		}

		SECTION("Hours is XX")
		{
			REQUIRE(time_played.hours == 122);
		}

		SECTION("Minutes is XX")
		{
			REQUIRE(time_played.minutes == 20);
		}

		SECTION("Seconds is XX")
		{
			REQUIRE(time_played.seconds == 58);
		}

		SECTION("Frames is XX")
		{
			REQUIRE(time_played.frames == 10);
		}
	}
}
