#include <iostream>
#include <cstdio>

#include "RomInterface.hpp"

int main()
{
	auto _rom = RomInterface::make_rom("../../games/yellow.sav");
	std::printf("Save file size: %d\n", _rom->get_size());
    return 0;
}
