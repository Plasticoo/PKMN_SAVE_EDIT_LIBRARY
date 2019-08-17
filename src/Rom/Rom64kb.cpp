#include "Rom64kb.hpp"

#include "Constants.hpp"

#include <fstream>

Rom64kb::Rom64kb(std::filesystem::path const & file)
{
    this->load(file);
}

auto Rom64kb::load(std::filesystem::path const & file) -> void
{
    std::ifstream ifs(file, std::ios::binary | std::ios::ate);
    if (!ifs) {
        return;
    }

    auto size = std::filesystem::file_size(file);
    if (size == 0 || size != C::SIZES::ROM64KB) {
        return;
    }

    if (ifs.read((char*)this->data.data(), size)) {
        return;
    }
}

auto Rom64kb::get_size() const -> std::size_t
{
    return this->data.size();
}
