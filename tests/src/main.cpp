#include <iostream>
#include <cstdio>

#include "RomInterface.hpp"
#include "Gen1.hpp"

int main()
{
	auto _rom = std::make_unique<Rom32kb>("../../games/yellow.sav");
	std::printf("Save file size: %lu\n", _rom->get_size());

	auto gen1 = new Gen1(std::move(_rom));
	gen1->load_file();

	std::printf("Money: %d\n", gen1->get_money());

    return 0;
}
