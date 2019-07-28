#include "Rom.hpp"

#include "Constants.hpp"

#include <fstream>

Rom::Rom(std::filesystem::path& file)
{
    this->load(file);
    this->set_type();
}

void Rom::set_type()
{
    if (this->data.size() == C::GB::ROM_SIZE) {
        // checksum values comparison
        this->type = 1;
    } else if (this->data.size() == C::GBA::ROM_SIZE) {
        // more checks
        this->type = 2;
    }
}

std::uint8_t Rom::get_type() const
{
    return this->type;
}

void Rom::load(std::filesystem::path& file)
{
    std::ifstream ifs(file, std::ios::binary | std::ios::ate);
    if (!ifs) {
        return;
    }

    auto size = std::filesystem::file_size(file);
    if (size == 0 || size != C::GB::ROM_SIZE) {
        return;
    }

    if (ifs.read((char*)this->data.data(), size)) {
        return;
    }
}

std::size_t Rom::get_size() const
{
    return this->data.size();
}
