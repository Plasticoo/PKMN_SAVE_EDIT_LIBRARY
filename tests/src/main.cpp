#define CATCH_CONFIG_MAIN

#include "Gen1.hpp"
#include "Rom.hpp"
#include "RomInterface.hpp"
#include "catch2/catch.hpp"

#include <cstdio>
#include <iostream>

std::filesystem::path file_;
std::uintmax_t file_size_;
std::string rom_type;

TEST_CASE("Generation 1 class gets correct information")
{
    file_ = std::filesystem::path("../../saves/yellow.sav");
    file_size_ = std::filesystem::file_size(file_);
    rom_type = Gen1::get_rom_type(file_size_);

    auto gen1 = Gen1::make_templated(rom_type, file_);

    SECTION("File is loaded correctly and has correct size")
    {
        REQUIRE(gen1->get_rom_size() == 0x8000);
    }

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
        auto time_played = Gen1::Structs::pkmn_time();
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

    SECTION("Current PC Box has correct information")
    {
        SECTION("Current PC box that is selected is number 12")
        {
            REQUIRE(gen1->get_current_pc_box() == 12);
        }

        SECTION("Current selected PC Box has 19 Pokemons in it")
        {
            auto current_box = gen1->get_current_pc_box_list();
            if (current_box) {
                REQUIRE(current_box->count == 18);
            }
        }

        SECTION("First Pokemon in Current PC Box is called POLIWRATH")
        {
            auto pokemon_name = gen1->get_pokemon_in_current_box_name(0);
            if (pokemon_name != "") {
                REQUIRE(pokemon_name == "POLIWRATH");
            }
        }

        SECTION("Second Pokemon in Current PC Box is called RAPIDASH")
        {
            auto pokemon_name = gen1->get_pokemon_in_current_box_name(1);
            if (pokemon_name != "") {
                REQUIRE(pokemon_name == "RAPIDASH");
            }
        }

        SECTION("Last Pokemon in Current PC Box is called MEWTWO")
        {
            auto pokemon_name = gen1->get_pokemon_in_current_box_name(17);
            if (pokemon_name != "") {
                REQUIRE(pokemon_name == "MEWTWO");
            }
        }

        SECTION("First Pokemon in Current PC Box is level 55")
        {
            auto pokemon = gen1->get_pokemon_in_current_box(0);
            if (pokemon) {
                REQUIRE(pokemon->level == 55);
            }
        }

        SECTION("Second Pokemon in Current PC Box is level 43")
        {
            auto pokemon = gen1->get_pokemon_in_current_box(1);
            if (pokemon) {
                REQUIRE(pokemon->level == 43);
            }
        }

        SECTION("Last Pokemon in Current PC Box is level 72")
        {
            auto pokemon = gen1->get_pokemon_in_current_box(17);
            if (pokemon) {
                REQUIRE(pokemon->level == 72);
            }
        }
    }

    SECTION("Every gym is completed")
    {
        REQUIRE(gen1->get_badge(Gen1::Enums::badges::BOULDER) == true);
        REQUIRE(gen1->get_badge(Gen1::Enums::badges::CASCADE) == true);
        REQUIRE(gen1->get_badge(Gen1::Enums::badges::THUNDER) == true);
        REQUIRE(gen1->get_badge(Gen1::Enums::badges::RAINBOW) == true);
        REQUIRE(gen1->get_badge(Gen1::Enums::badges::SOUL) == true);
        REQUIRE(gen1->get_badge(Gen1::Enums::badges::MARSH) == true);
        REQUIRE(gen1->get_badge(Gen1::Enums::badges::VOLCANO) == true);
        REQUIRE(gen1->get_badge(Gen1::Enums::badges::EARTH) == true);
    }

    SECTION("Options are all set")
    {
        REQUIRE(gen1->get_option(Gen1::Enums::options::TEXT_SPEED) == Gen1::Enums::options_flags::TEXT_SPEED_FAST);
        REQUIRE(gen1->get_option(Gen1::Enums::options::SOUND) == Gen1::Enums::options_flags::SOUND_EARPHONE3);
        REQUIRE(gen1->get_option(Gen1::Enums::options::BATTLE_STYLE) == Gen1::Enums::options_flags::BATTLE_STYLE_SET);
        REQUIRE(gen1->get_option(Gen1::Enums::options::BATTLE_EFFECTS) == Gen1::Enums::options_flags::BATTLE_EFFECTS_ON);
    }

    SECTION("Pikachu friendship is 103")
    {
        REQUIRE(gen1->get_pikachu_friendship() == 103);
    }

    SECTION("Bag unique item quantity is 19")
    {
        REQUIRE(gen1->get_item_bag_count() == 19);
    }

    SECTION("First item in the bag is an Ultra Ball")
    {
        auto item = gen1->get_item_bag(0);
        REQUIRE(item->index == Gen1::Enums::ULTRA_BALL);
    }

    SECTION("There are 3 Ultra Balls in the bag item list")
    {
        auto item = gen1->get_item_bag(0);
        REQUIRE(item->count == 3);
    }

    SECTION("Last item in the bag is a Poke Flute")
    {
        auto item = gen1->get_item_bag(gen1->get_item_bag_count() - 1);
        REQUIRE(item->index == Gen1::Enums::POKE_FLUTE);
    }

    SECTION("There is 1 Poke Flute in the bag item list")
    {
        auto item = gen1->get_item_bag(gen1->get_item_bag_count() - 1);
        REQUIRE(item->count == 1);
    }

    SECTION("PC unique item quantity is 47")
    {
        REQUIRE(gen1->get_item_pc_count() == 47);
    }

    SECTION("First item in PC is a TM12")
    {
        auto item = gen1->get_item_pc(0);
        REQUIRE(item->index == Gen1::Enums::TM12);
    }

    SECTION("There is 1 TM12 in the PC item list")
    {
        auto item = gen1->get_item_pc(0);
        REQUIRE(item->count == 1);
    }

    SECTION("Last item in PC is a TM45")
    {
        auto item = gen1->get_item_pc(gen1->get_item_pc_count() - 1);
        REQUIRE(item->index == Gen1::Enums::TM45);
    }

    SECTION("There is 1 TM45 in the PC item list")
    {
        auto item = gen1->get_item_pc(gen1->get_item_pc_count() - 1);
        REQUIRE(item->count == 1);
    }

    SECTION("Party information is correct")
    {
        SECTION("First Pokemon information matches")
        {
            auto pokemon_name = gen1->get_pokemon_in_party_name(0);
            if (pokemon_name != "") {
                REQUIRE(pokemon_name == "PIKACHU");
            }
        }

        SECTION("Second Pokemon in the party is called MEW")
        {
            auto pokemon_name = gen1->get_pokemon_in_party_name(1);
            if (pokemon_name != "") {
                REQUIRE(pokemon_name == "MEW");
            }
        }

        SECTION("Last Pokemon in the party is called DUGTRIO")
        {
            auto pokemon_name = gen1->get_pokemon_in_party_name(5);
            if (pokemon_name != "") {
                REQUIRE(pokemon_name == "DUGTRIO");
            }
        }

        SECTION("First Pokemon is level 55")
        {
            auto pokemon = gen1->get_pokemon_in_party(0);
            if (pokemon) {
                REQUIRE(pokemon->level == 55);
            }
        }

        // TODO: why isnt this working
        // SECTION("Second  Pokemon is level 70")
        // {
        // 	auto pokemon = gen1->get_pokemon_in_party(1);
        // 	if (pokemon) {
        // 		REQUIRE(pokemon->level == 70);
        // 	}
        // }

        SECTION("Last Pokemon is level 43")
        {
            auto pokemon = gen1->get_pokemon_in_party(5);
            if (pokemon) {
                REQUIRE(pokemon->level == 43);
            }
        }

        SECTION("First Pokemon HP is 134")
        {
            auto pokemon = gen1->get_pokemon_in_party(0);
            if (pokemon) {
                REQUIRE(Utils::swap_endian<std::uint16_t>(pokemon->hp) == 134);
            }
        }

        SECTION("Second  Pokemon HP is 257")
        {
            auto pokemon = gen1->get_pokemon_in_party(1);
            if (pokemon) {
                REQUIRE(Utils::swap_endian<std::uint16_t>(pokemon->hp) == 257);
            }
        }

        SECTION("Last Pokemon HP is 95")
        {
            auto pokemon = gen1->get_pokemon_in_party(5);
            if (pokemon) {
                REQUIRE(Utils::swap_endian<std::uint16_t>(pokemon->hp) == 95);
            }
        }
    }

    SECTION("Box information is correct")
    {
        SECTION("Pokemon count in all Boxes")
        {
            REQUIRE(gen1->get_pokemon_box(0)->count == 1);
            REQUIRE(gen1->get_pokemon_box(1)->count == 0);
            REQUIRE(gen1->get_pokemon_box(2)->count == 0);
            REQUIRE(gen1->get_pokemon_box(3)->count == 5);
            REQUIRE(gen1->get_pokemon_box(4)->count == 0);
            REQUIRE(gen1->get_pokemon_box(5)->count == 20);
            REQUIRE(gen1->get_pokemon_box(6)->count == 20);
            REQUIRE(gen1->get_pokemon_box(7)->count == 12);
            REQUIRE(gen1->get_pokemon_box(8)->count == 0);
            REQUIRE(gen1->get_pokemon_box(9)->count == 1);
            REQUIRE(gen1->get_pokemon_box(10)->count == 0);
            // NOTE: box in use, therefore count == 0 and not count == 18
            REQUIRE(gen1->get_pokemon_box(11)->count == 0);
        }

        SECTION("First Pokemon in Box 1 is called LAPRAS")
        {
            auto pokemon_name = gen1->get_pokemon_in_box_name(0, 0);
            if (pokemon_name != "") {
                REQUIRE(pokemon_name == "LAPRAS");
            }
        }

        SECTION("First Pokemon in Box 4 is called BEEDRILL")
        {
            auto pokemon_name = gen1->get_pokemon_in_box_name(3, 0);
            if (pokemon_name != "") {
                REQUIRE(pokemon_name == "BEEDRILL");
            }
        }

        SECTION("Second Pokemon in Box 4 is called WEEZING")
        {
            auto pokemon_name = gen1->get_pokemon_in_box_name(3, 1);
            if (pokemon_name != "") {
                REQUIRE(pokemon_name == "WEEZING");
            }
        }

        SECTION("First Pokemon in Box 12 is called POLIWRATH")
        {
            auto pokemon_name = gen1->get_pokemon_in_box_name(11, 0);
            if (pokemon_name != "") {
                REQUIRE(pokemon_name == "POLIWRATH");
            }
        }

        SECTION("Second Pokemon in Box 12 is called RAPIDASH")
        {
            auto pokemon_name = gen1->get_pokemon_in_box_name(11, 1);
            if (pokemon_name != "") {
                REQUIRE(pokemon_name == "RAPIDASH");
            }
        }
    }

    SECTION("Checksum value is 183")
    {
        auto checksum = gen1->get_checksum();
        REQUIRE(checksum == 183);
    }

    SECTION("Checksum is calculated correctly")
    {
        auto checksum = gen1->get_checksum();
        auto calculated = gen1->calc_checksum();

        REQUIRE(checksum == calculated);
    }

    // TODO: test file size and file consistency between
    // old and new
    // save bytes from loaded file in new file
    // gen1->save_changes("../../games/yellow_new.sav");
}

TEST_CASE("Generation I save changes are reflected correctly in new save file")
{
    auto gen1 = Gen1::make_templated(rom_type, file_);

    // make changes
    gen1->set_player_name("JOHN");
    gen1->set_rival_name("MATT");

    gen1->set_pokedex_owned(65, false);
    gen1->set_pokedex_seen(65, false);

    gen1->set_money(5000);
    gen1->set_casino_coins(5);

    gen1->set_time_played(50, 45, 10, 15);

    gen1->set_current_pc_box(4);

    gen1->set_badge(Gen1::Enums::badges::BOULDER, false);
    gen1->set_badge(Gen1::Enums::badges::CASCADE, false);
    gen1->set_badge(Gen1::Enums::badges::EARTH, false);
    gen1->set_badge(Gen1::Enums::badges::MARSH, false);
    gen1->set_badge(Gen1::Enums::badges::RAINBOW, false);
    gen1->set_badge(Gen1::Enums::badges::SOUL, false);
    gen1->set_badge(Gen1::Enums::badges::THUNDER, false);
    gen1->set_badge(Gen1::Enums::badges::VOLCANO, false);

    gen1->set_option(Gen1::Enums::options::TEXT_SPEED, Gen1::Enums::options_flags::TEXT_SPEED_SLOW);
    gen1->set_option(Gen1::Enums::options::SOUND, Gen1::Enums::options_flags::SOUND_STEREO);
    gen1->set_option(Gen1::Enums::options::BATTLE_STYLE, Gen1::Enums::options_flags::BATTLE_STYLE_SWITCH);
    gen1->set_option(Gen1::Enums::options::BATTLE_EFFECTS, Gen1::Enums::options_flags::BATTLE_EFFECTS_OFF);

    gen1->set_item_pc(0, Gen1::Enums::item::FULL_RESTORE, 2);
    gen1->set_item_pc(1, Gen1::Enums::item::ANTIDOTE, 3);
    gen1->set_item_pc(49, Gen1::Enums::item::SAFARI_BALL, 10);

    gen1->set_item_bag(0, Gen1::Enums::item::FULL_RESTORE, 2);
    gen1->set_item_bag(1, Gen1::Enums::item::ANTIDOTE, 3);
    gen1->set_item_bag(19, Gen1::Enums::item::SAFARI_BALL, 10);

    // save changes
    gen1->save_changes("../../saves/yellow_test.sav");

    // TODO: test changes
    auto file2_ = std::filesystem::path("../../saves/yellow_test.sav");
    auto file_size2_ = std::filesystem::file_size(file2_);
    std::string rom_type2 = Gen1::get_rom_type(file_size2_);

    auto gen1c = Gen1::make_templated(rom_type2, file2_);

    SECTION("New names are correct")
    {
        REQUIRE(gen1c->get_player_name() == "JOHN");
        REQUIRE(gen1c->get_rival_name() == "MATT");
    }

    SECTION("Pokedex function changes are correct")
    {
        REQUIRE(gen1c->get_pokedex_owned(65) == false);
        REQUIRE(gen1c->get_pokedex_seen(65) == false);
    }

    SECTION("Money changes are correct")
    {
        REQUIRE(gen1c->get_money() == 5000);
    }

    SECTION("Casino coin changes are correct")
    {
        REQUIRE(gen1c->get_casino_coins() == 5);
    }

    SECTION("Time played changes are correct")
    {
        auto time_played = Gen1::Structs::pkmn_time();
        gen1c->get_time_played(&time_played);

        SECTION("Maximum time not reached")
        {
            REQUIRE(time_played.maxed == 0);
        }

        SECTION("Hours is 50")
        {
            REQUIRE(time_played.hours == 50);
        }

        SECTION("Minutes is 45")
        {
            REQUIRE(time_played.minutes == 45);
        }

        SECTION("Seconds is 10")
        {
            REQUIRE(time_played.seconds == 10);
        }

        SECTION("Frames is 15")
        {
            REQUIRE(time_played.frames == 15);
        }
    }

    SECTION("Current PC Box is correct")
    {
        REQUIRE(gen1c->get_current_pc_box() == 4);
    }

    SECTION("Gym Badge changes are correct")
    {
        REQUIRE(gen1c->get_badge(Gen1::Enums::badges::BOULDER) == false);
        REQUIRE(gen1c->get_badge(Gen1::Enums::badges::CASCADE) == false);
        REQUIRE(gen1c->get_badge(Gen1::Enums::badges::THUNDER) == false);
        REQUIRE(gen1c->get_badge(Gen1::Enums::badges::RAINBOW) == false);
        REQUIRE(gen1c->get_badge(Gen1::Enums::badges::SOUL) == false);
        REQUIRE(gen1c->get_badge(Gen1::Enums::badges::MARSH) == false);
        REQUIRE(gen1c->get_badge(Gen1::Enums::badges::VOLCANO) == false);
        REQUIRE(gen1c->get_badge(Gen1::Enums::badges::EARTH) == false);
    }

    SECTION("Options are correct")
    {
        REQUIRE(gen1c->get_option(Gen1::Enums::options::TEXT_SPEED) == Gen1::Enums::options_flags::TEXT_SPEED_SLOW);
        REQUIRE(gen1c->get_option(Gen1::Enums::options::SOUND) == Gen1::Enums::options_flags::SOUND_STEREO);
        REQUIRE(gen1c->get_option(Gen1::Enums::options::BATTLE_STYLE) == Gen1::Enums::options_flags::BATTLE_STYLE_SWITCH);
        REQUIRE(gen1c->get_option(Gen1::Enums::options::BATTLE_EFFECTS) == Gen1::Enums::options_flags::BATTLE_EFFECTS_OFF);
    }

    SECTION("PC items are correct")
    {
        auto item0 = gen1c->get_item_pc(0);
        auto item1 = gen1c->get_item_pc(1);
        auto item2 = gen1c->get_item_pc(49);

        REQUIRE(item0->index == Gen1::Enums::item::FULL_RESTORE);
        REQUIRE(item0->count == 2);

        REQUIRE(item1->index == Gen1::Enums::item::ANTIDOTE);
        REQUIRE(item1->count == 3);

        REQUIRE(item2->index == Gen1::Enums::item::SAFARI_BALL);
        REQUIRE(item2->count == 10);
    }

    SECTION("Bag items are correct")
    {
        auto item0 = gen1c->get_item_bag(0);
        auto item1 = gen1c->get_item_bag(1);
        auto item2 = gen1c->get_item_bag(19);

        REQUIRE(item0->index == Gen1::Enums::item::FULL_RESTORE);
        REQUIRE(item0->count == 2);

        REQUIRE(item1->index == Gen1::Enums::item::ANTIDOTE);
        REQUIRE(item1->count == 3);

        REQUIRE(item2->index == Gen1::Enums::item::SAFARI_BALL);
        REQUIRE(item2->count == 10);
    }
}
