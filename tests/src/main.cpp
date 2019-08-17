#define CATCH_CONFIG_MAIN

#include <iostream>
#include <cstdio>

#include "catch2/catch.hpp"

#include "RomInterface.hpp"
#include "Gen1.hpp"

TEST_CASE("Generation 1 class gets correct information")
{
	auto _rom = std::make_unique<Rom32kb>("../../games/yellow.sav");

	SECTION("File is loaded correctly and has correct size")
    {
        REQUIRE(_rom->get_size() == 0x8000);
    }

    auto gen1 = new Gen1(std::move(_rom));

	SECTION("Player name is ROMEU")
	{
		REQUIRE(gen1->get_player_name() == "ROMEU");
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

    SECTION("Money is 3175")
    {
        REQUIRE(gen1->get_money() == 3175);
    }

	SECTION("Casino Coins is 0")
    {
        REQUIRE(gen1->get_casino_coins() == 0);
    }

	SECTION("Time played is 00:01:00")
	{
		auto time_played = Gen1Structs::pkmn_time();
		gen1->get_time_played(&time_played);

		SECTION("Hours is XX")
		{
			REQUIRE(time_played.hours == 0);
		}

		SECTION("Minutes is XX")
		{
			REQUIRE(time_played.minutes == 1);
		}

		SECTION("Seconds is XX")
		{
			REQUIRE(time_played.seconds == 0);
		}
	}
}
