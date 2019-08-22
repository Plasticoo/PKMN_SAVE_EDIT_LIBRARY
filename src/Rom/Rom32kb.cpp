#include "Rom32kb.hpp"

#include "Constants.hpp"

#include <fstream>

Rom32kb::Rom32kb(std::filesystem::path const& file)
{
    this->load(file);
}

auto Rom32kb::load(std::filesystem::path const& file) -> void
{
    std::ifstream ifs(file, std::ios::binary | std::ios::in);
    if (!ifs) {
        return;
    }

    auto size = std::filesystem::file_size(file);
    if (size == 0 || size != C::SIZES::ROM32KB) {
        return;
    }

    ifs.read((char*)this->data.data(), size);
    ifs.close();
}

auto Rom32kb::get_size() const -> std::size_t
{
    return this->data.size();
}
