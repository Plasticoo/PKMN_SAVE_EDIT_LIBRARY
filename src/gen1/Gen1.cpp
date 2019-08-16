#include "Gen1.hpp"

static inline std::uint8_t n_digits(std::uint32_t n) {
	std::uint8_t count = 0;

    while(n != 0) {
        n /= 10;
        count++;
    }

    return count;
}

auto Gen1::get_checksum() const -> std::uint8_t
{
    return this->m_rom->data[C::GEN1::OFFSETS::CHECKSUM];
}

auto Gen1::calc_checksum() const -> std::uint8_t
{
    std::uint8_t checksum{ 0 };
    for (auto i = C::GEN1::OFFSETS::CHECKSUM_INIT_OFFSET;
         i <= C::GEN1::OFFSETS::CHECKSUM_END_OFFSET; i++) {
        checksum += m_rom->data[i];
    }
    return ~checksum;
}

auto Gen1::set_checksum() -> void
{
	auto checksum = this->calc_checksum();
	// NOTE: *(this->checksum) = checksum
	this->checksum[0] = checksum;
}

auto Gen1::load_file() -> void
{
	if (this->m_rom == nullptr) {
		return;
	}

	this->player_name = &this->m_rom->data[C::GEN1::OFFSETS::PLAYER_NAME];
	this->pokedex_owned = &this->m_rom->data[C::GEN1::OFFSETS::POKEDEX_OWNED];
	this->pokedex_seen = &this->m_rom->data[C::GEN1::OFFSETS::POKEDEX_SEEN];
	this->money = &this->m_rom->data[C::GEN1::OFFSETS::MONEY];
	this->rival_name = &this->m_rom->data[C::GEN1::OFFSETS::RIVAL_NAME];
	this->options = &this->m_rom->data[C::GEN1::OFFSETS::OPTIONS];
	this->badges = &this->m_rom->data[C::GEN1::OFFSETS::BADGES];
	this->player_trainer_id = (std::uint16_t*)&this->m_rom->data[C::GEN1::OFFSETS::PLAYER_TRAINER_ID];
	this->pikachu_friendship = &this->m_rom->data[C::GEN1::OFFSETS::PIKACHU_FRIENDSHIP];
	this->current_pc_box = &this->m_rom->data[C::GEN1::OFFSETS::CURRENT_PC_BOX];
	this->casino_coins = &this->m_rom->data[C::GEN1::OFFSETS::CASINO_COINS];
	this->current_box_list = &this->m_rom->data[C::GEN1::OFFSETS::CURRENT_BOX_LIST];
	this->checksum = &this->m_rom->data[C::GEN1::OFFSETS::CHECKSUM];

	this->pocket_item_list = (struct Gen1Structs::items_bag*)&this->m_rom->data[C::GEN1::OFFSETS::POCKET_ITEM_LIST];
	this->pc_item_list = (struct Gen1Structs::items_pc*)&this->m_rom->data[C::GEN1::OFFSETS::PC_ITEM_LIST];
	this->time_played = (struct Gen1Structs::pkmn_time*)&this->m_rom->data[C::GEN1::OFFSETS::TIME_PLAYED];
	this->team_pokemon_list = (struct Gen1Structs::pkmn_data_struct*)&this->m_rom->data[C::GEN1::OFFSETS::TEAM_POKEMON_LIST];

	auto offset = C::GEN1::OFFSETS::PC_BOX_1_POKEMON_LIST;
	for (auto i = 0; i < 12; i++) {
		this->pc_box[i] = (struct Gen1Structs::pkmn_box*)&this->m_rom->data[offset];
		offset += (sizeof(struct Gen1Structs::pkmn_box) * i);
	}
}

auto Gen1::save_changes(std::filesystem::path& file_name) -> bool
{
	std::ofstream out;

    if(!this->m_rom) {
        return false;
    }

	out.open(file_name, std::ios::out | std::ios::binary);

    if (!out.is_open()) {
		return false;
	}

    for (auto i = 0; i < C::GEN1::SIZES::FILE; i++) {
		out.write((char*)&this->m_rom->data[i], 1);
    }

    return true;
}

// NOTE: can probably be reused for any other names?
auto Gen1::get_player_name() const -> std::string
{
	if (this->player_name == nullptr) {
		return nullptr;
	}

	std::string name = "";
	for (auto i = 0; i < C::GEN1::SIZES::PLAYER_NAME; i++) {
        if(this->player_name[i] == 'P') {
			break;
		}

        name += C::GEN1::FONT[this->player_name[i]];
    }

    return name;
}

auto Gen1::set_player_name(std::string name) -> void
{
	std::size_t size = name.size();

	if (this->player_name == nullptr || name.empty()) {
		return;
	}

	if (size >= 7) {
		size = 7;
	}

	for (auto i = 0; i < size; i++) {
		this->player_name[i] = this->get_character_code(name[i]);
	}

	this->player_name[++size] = 'P';

	while (size < 11) {
		this->player_name[++size] = 0x0;
	}
}

auto Gen1::get_pokedex_owned(std::uint8_t index) const -> bool
{
	if (this->pokedex_owned && index < 152) {
		return (this->pokedex_owned[index >> 3] >> (index & 7) & 1) == 1;
	}

	return false;
}

auto Gen1::get_pokedex_seen(std::uint8_t index) const -> bool
{
	if (this->pokedex_seen && index < 152) {
		return (this->pokedex_seen[index >> 3] >> (index & 7) & 1) == 1;
	}

	return false;
}

auto Gen1::set_pokedex_owned(std::uint8_t index, bool owned) -> void
{
    if (owned) {
        this->pokedex_owned[index >> 3] |= 1 << (index & 7);
    } else {
		this->pokedex_owned[index >> 3] &= ~(1 << (index & 7));
	}
}

auto Gen1::set_pokedex_seen(std::uint8_t index, bool seen) -> void
{
    if (seen) {
        this->pokedex_seen[index >> 3] |= 1 << (index & 7);
    } else {
		this->pokedex_seen[index >> 3] &= ~(1 << (index & 7));
	}
}

auto Gen1::get_money() -> std::uint32_t
{
	if (!this->money) {
		return 0x7FFFFFFF;
	}

	if(this->money[1] == 0 && this->money[2] == 0) {
        return Utils::__bcd_to_dec(this->money, 1);
    } else if(this->money[1] != 0 && this->money[2] == 0) {
        return Utils::__bcd_to_dec(this->money, 2);
    }

    return Utils::__bcd_to_dec(this->money, C::GEN1::SIZES::MONEY);
}

auto Gen1::set_money(std::uint32_t value) -> void
{
	if (!this->money) {
		return;
	}

	std::uint8_t buffer[C::GEN1::SIZES::MONEY];
	Utils::__dec_to_bcd(value, buffer);

	std::memcpy(this->money, buffer,C::GEN1::SIZES::MONEY);
}

auto Gen1::get_casino_coins() -> std::uint16_t
{
    if(!this->casino_coins) {
        return 0;
    }

    if(this->casino_coins[1] == 0) {
        return Utils::__bcd_to_dec(this->casino_coins, 1);
    }

    return Utils::__bcd_to_dec(this->casino_coins, C::GEN1::SIZES::CASINO_COINS);
}

auto Gen1::set_casino_coins(std::uint16_t value) -> void
{
    if(!this->casino_coins) {
        return;
    }

	std::uint8_t buffer[C::GEN1::SIZES::CASINO_COINS];

	Utils::__dec_to_bcd(value, buffer);

    if(n_digits(value) == 1 || n_digits(value) == 2) {
        this->casino_coins[0] = buffer[0];
        this->casino_coins[1] = 0;

        return;
    }

    memcpy(this->casino_coins, buffer, C::GEN1::SIZES::CASINO_COINS);
}

auto Gen1::get_time_played(struct Gen1Structs::pkmn_time *dest) -> void
{
    if(this->time_played && dest) {
		dest->hours = this->time_played->hours;
		dest->minutes = this->time_played->minutes;
		dest->seconds = this->time_played->seconds;

		return;
    }
}

auto Gen1::set_time_played(std::uint16_t hours, std::uint8_t minutes, std::uint8_t seconds) -> void
{
    if(hours < 1000 &&
       minutes < 100 &&
       seconds < 100 &&
        this->time_played) {
        this->time_played->seconds = seconds;
        this->time_played->minutes = minutes;
        this->time_played->hours = hours;

        return;
    }
}

auto Gen1::get_current_pc_box() -> std::uint8_t
{
	if (this->current_pc_box) {
		return current_pc_box[0] + 1;
	}

	return 0;
}

auto Gen1::set_current_pc_box(std::uint8_t index) -> void
{
	std::uint8_t idx;

    if (current_pc_box && index <= 20) {
        if (index == 0) {
            idx = 0;
        } else {
            idx = index - 1;
        }

        current_pc_box[0] = idx;
    }
}

auto Gen1::get_badge(enum Gen1Enums::badges badge) -> std::uint8_t
{
    if (this->badges) {
        return (this->badges[0] & (1 << badge)) >> badge;
    }

    return 0;
}

auto Gen1::set_badge(enum Gen1Enums::badges badge) -> void
{
    if (this->badges) {
        this->badges[0] ^= (1 << badge);
    }
}

auto Gen1::get_option(enum Gen1Enums::options_flags flag) -> std::uint8_t
{
	if (!this->options) {
		return 0;
	}

	return options[0] & C::GEN1::OPTIONS::LOOKUP_TABLE[flag];
}

auto Gen1::set_option(enum Gen1Enums::options_flags flag) -> void
{
	if (!this->options) {
		return;
	}

	Utils::set_clear_bits(&this->options[0], C::GEN1::OPTIONS::LOOKUP_TABLE[flag]);
}

auto Gen1::get_pikachu_friendship() -> std::uint8_t
{
    if(this->pikachu_friendship) {
        return this->pikachu_friendship[0];
    }

    return 0;
}

auto Gen1::set_pikachu_friendship(std::uint8_t value) -> void
{
    if(this->pikachu_friendship) {
        this->pikachu_friendship[0] = value;
        return;
    }
}

auto Gen1::get_item_bag(std::uint8_t index) -> struct Gen1Structs::item *
{
	if(index <= C::GEN1::SIZES::BAG_ITEM) {
		return &this->pocket_item_list->item[index];
	}

	return nullptr;
}

// TODO: This is not doing what it is supposed to do
auto Gen1::set_item_bag(struct Gen1Structs::item *items, std::uint8_t index, std::uint8_t item, std::uint8_t count) -> void
{
	if(index <= C::GEN1::SIZES::BAG_ITEM) {
		items[index].index = item;
		items[index].count = count;

		return;
	}
}

auto Gen1::get_item_pc(std::uint8_t index) -> struct Gen1Structs::item *
{
	if(index <= C::GEN1::SIZES::PC_ITEM) {
		return &this->pc_item_list->item[index];
	}

	return nullptr;
}

// TODO: This is not doing what it is supposed to do
auto Gen1::set_item_pc(struct Gen1Structs::item *items, std::uint8_t index, std::uint8_t item, std::uint8_t count) -> void
{
	if(index <= C::GEN1::SIZES::PC_ITEM) {
		items[index].index = item;
		items[index].count = count;

		return;
	}
}

auto Gen1::get_character_code(std::uint8_t const c) const -> std::uint8_t
{
    int i;

    for (i = 0; i < C::GEN1::SIZES::FONT; i++) {
        if (c == C::GEN1::FONT[i]) {
            return i;
        }
    }

    // return space code, as in, invalid character
    return 0x7F;
}
