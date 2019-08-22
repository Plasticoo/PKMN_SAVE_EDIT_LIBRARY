#include "Rom.hpp"

#include "Constants.hpp"

#include <fstream>

Rom::Rom(std::filesystem::path const& file)
{
    this->load(file);
}

auto Rom::load(std::filesystem::path const& file) -> void
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
