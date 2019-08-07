#include "Gen1.hpp"

std::uint8_t Gen1::get_checksum() const
{
    return this->m_rom->data[C::GEN1::OFFSETS::CHECKSUM];
}

std::uint8_t Gen1::calc_checksum()
{
    std::uint8_t checksum{ 0 };
    for (auto i = C::GEN1::OFFSETS::CHECKSUM_INIT_OFFSET;
         i <= C::GEN1::OFFSETS::CHECKSUM_END_OFFSET; i++) {
        checksum += m_rom->data[i];
    }
    return ~checksum;
}

void Gen1::load_file()
{
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

	this->pocket_items = (struct Gen1Structs::items_bag*)&this->m_rom->data[C::GEN1::OFFSETS::POCKET_ITEM_LIST];
	this->pc_item_list = (struct Gen1Structs::items_pc*)&this->m_rom->data[C::GEN1::OFFSETS::PC_ITEM_LIST];
	this->time_played = (struct Gen1Structs::pkmn_time*)&this->m_rom->data[C::GEN1::OFFSETS::TIME_PLAYED];
	this->team_pokemon_list = (struct Gen1Structs::pkmn_data_struct*)&this->m_rom->data[C::GEN1::OFFSETS::TEAM_POKEMON_LIST];

	auto offset = C::GEN1::OFFSETS::PC_BOX_1_POKEMON_LIST;
	for (auto i = 0; i < 12; i++) {
		this->pc_box[i] = (struct Gen1Structs::pkmn_box*)&this->m_rom->data[offset];
		offset += (sizeof(struct Gen1Structs::pkmn_box) * i);
	}
}
