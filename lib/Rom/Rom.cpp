#include "Rom.hpp"

#include "Constants.hpp"

#include <fstream>

Rom::Rom(std::filesystem::path& file)
{
    this->load(file);
    this->set_type();
}

auto Rom::set_type() -> void
{
    if (this->data.size() == C::GB::ROM_SIZE) {
        // checksum values comparison
        this->type = 1;
    } else if (this->data.size() == C::GBA::ROM_SIZE) {
        // more checks
        this->type = 2;
    }
}

auto Rom::get_type() const -> std::uint8_t
{
    return this->type;
}

auto Rom::load(std::filesystem::path& file) -> void
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

auto Rom::get_size() const -> std::size_t
{
    return this->data.size();
}
