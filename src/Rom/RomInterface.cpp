#include "RomInterface.hpp"

#include "Rom.hpp"
#include "Rom32kb.hpp"
#include "Rom64kb.hpp"

auto RomInterface::make_rom(std::filesystem::path const & file) -> std::unique_ptr<RomInterface>
{
    auto file_size = std::filesystem::file_size(file);

    if (file_size == 0x8000) {
        return std::make_unique<Rom32kb>(file);
    } else if (file_size == 0xffff) {
        return std::make_unique<Rom64kb>(file);
    }

    if (file_size > 0x0) {
        return std::make_unique<Rom>(file);
    }

    return nullptr;
}
