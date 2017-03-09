#include "../../include/gen1/gen1_funcs.h"
#include "../../include/gen1/gen1_defines.h"
#include "../../include/gen1/gen1_structs.h"
#include "../../include/gen1/gen1_math.h"

#include <stdlib.h>
#include <stdbool.h>

// character map
// TODO check characters
const char fonts[] =
{'?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // 0
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // 1
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // 2
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // 3
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // 4
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // 5
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // 6
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',' ',   // 7
 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',   // 8
 'Q','R','S','T','U','V','W','X','Y','Z','(',')',':',';','[',']',   // 9
 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p',   // A
 'q','r','s','t','u','v','w','x','y','z','?','?','?','?','?','?',   // B
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // C
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // D
 '?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',   // E
 '?','?','.','/',',','?','0','1','2','3','4','5','6','7','8','9'};  // F

int get_character_code(char c)
{
    int i;

    for (i = 0; i < FONT_SIZE; i++) {
        if (c == fonts[i]) {
            return i;
        }
    }

    // return space code, as in, invalid character
    return 0x7F;
}

int gen1_save_changes(struct gen1_pkmn_file_struct *file_struct, char* file_name)
{
    int i;
    FILE* _f;

    if((_f = fopen(file_name, "wb")) == NULL) {
        return -1;
    }

    for (i = 0; i < FILE_SIZE; i++) {
        fwrite(&file_struct->file_map[i], 1, 1, _f);
    }

    fclose(_f);

    return 0;
}

void gen1_set_checksum(struct gen1_pkmn_file_struct *file_struct)
{
    u8 checksum = gen1_checksum_map(file_struct->file_map);
    file_struct->checksum[0] = checksum;
}

char* gen1_get_name(u8 *name)
{
    int i;

    char *_name = calloc(PLAYER_NAME_SIZE, sizeof(char));

    for (i = 0; i < PLAYER_NAME_SIZE; i++) {
        if(name[i] == 'P') break;
        _name[i] = fonts[name[i]];
    }

    _name[i] = '\0';
    return _name;
}

// TODO handling of the 'P' character that is needed for string termination
void gen1_set_name(u8* name, char* new_name, size_t size)
{
    size_t i;
    size_t _s = size;

    if (size >= 7) {
        _s = 7;
    }

    for (i = 0; i < _s; i++) {
        name[i] = get_character_code(new_name[i]);
    }
}

u8 gen1_get_pokedex(u8 *pokedex, u8 index)
{
    return pokedex[index >> 3] >> (index & 7) & 1;
}

void gen1_set_pokedex(u8 *pokedex, u8 index)
{
    pokedex[index >> 3] |= 1 << (index & 7);
}

void gen1_unset_pokedex(u8 *pokedex, u8 index)
{
    pokedex[index >> 3] &= ~(1 << (index & 7));
}

u32 gen1_get_money(struct gen1_pkmn_file_struct *file_struct)
{
    return __bcd_to_dec(file_struct->money, MONEY_SIZE);
}

void gen1_set_money(struct gen1_pkmn_file_struct *file_struct, u32 value)
{
    u8 buffer[MONEY_SIZE];

    __dec_to_bcd(value, buffer);

    file_struct->money[0] = buffer[0];
    file_struct->money[1] = buffer[1];
    file_struct->money[2] = buffer[2];
}

u16 gen1_get_casino_coins(struct gen1_pkmn_file_struct *file_struct)
{
    return __bcd_to_dec(file_struct->casino_coins, CASINO_COINS_SIZE);
}

void gen1_set_casino_coins(struct gen1_pkmn_file_struct *file_struct, u16 value)
{
    u8 buffer[CASINO_COINS_SIZE];

    __dec_to_bcd(value, buffer);

    file_struct->casino_coins[0] = buffer[0];
    file_struct->casino_coins[1] = buffer[1];
}

// TODO take care of pokemon yellow options (1 extra)
u8 gen1_get_option(struct gen1_pkmn_file_struct *file_struct, enum options option)
{
    u8 result;

    switch(option) {
    case OPTION_TEXT_SPEED:
        result = file_struct->options[0] & OPTION_TEXT_SPEED_MASK;
        break;
    case OPTION_SOUND:
        result = file_struct->options[0] & OPTION_SOUND_MASK;
        break;
    case OPTION_BATTLE_STYLE:
        result = file_struct->options[0] & OPTION_BATTLE_STYLE_MASK;
        break;
    case OPTION_BATTLE_EFFECTS:
        result = file_struct->options[0] & OPTION_BATTLE_EFFECTS_MASK;
        break;
    }

    return result;
}

// TODO take care of pokemon yellow options
// TODO take care of text speed!
void gen1_set_option(struct gen1_pkmn_file_struct *file_struct, enum options option)
{
    switch(option) {
    case OPTION_TEXT_SPEED:
        file_struct->options[0] ^= 0;
        break;
    case OPTION_SOUND:
        file_struct->options[0] ^= OPTION_SOUND_MASK;
        break;
    case OPTION_BATTLE_STYLE:
        file_struct->options[0] ^= OPTION_BATTLE_STYLE_MASK;
        break;
    case OPTION_BATTLE_EFFECTS:
        file_struct->options[0] ^= OPTION_BATTLE_EFFECTS_MASK;
        break;
    }
}

void gen1_get_time_played(struct gen1_pkmn_file_struct *file_struct, struct gen1_pkmn_time *time)
{
    time->hours = file_struct->time_played[1] << 8 | file_struct->time_played[0];
    time->minutes = file_struct->time_played[2];
    time->seconds = file_struct->time_played[3];
}

void gen1_set_time_played(struct gen1_pkmn_file_struct *file_struct, struct gen1_pkmn_time *time)
{
    file_struct->time_played[0] = time->hours  & 0xFF;
    file_struct->time_played[1] = (time->hours >> 8) & 0xFF;
    file_struct->time_played[2] = time->minutes;
    file_struct->time_played[3] = time->seconds;
}

u8 gen1_get_badge(struct gen1_pkmn_file_struct *file_struct, enum badges badge)
{
    return file_struct->badges[0] & (1 << badge);
}

void gen1_set_badge(struct gen1_pkmn_file_struct *file_struct, enum badges badge)
{
    file_struct->badges[0] ^= badge;
}

u8 gen1_get_current_pc_box(struct gen1_pkmn_file_struct *file_struct)
{
    return file_struct->current_pc_box[0] + 1;
}

void gen1_set_current_pc_box(struct gen1_pkmn_file_struct *file_struct, u8 index)
{
    u8 idx;

    if(index == 0) {
        idx = 0;
    } else {
        idx = index - 1;
    }

    file_struct->current_pc_box[0] = idx;
}

struct gen1_pkmn_data_struct *gen1_get_pokemon_in_party(struct gen1_pkmn_file_struct *file_struct, u8 index)
{
    return file_struct->team_pokemon_list[index];
}

void gen1_set_pokemon_in_party(struct gen1_pkmn_file_struct *file_struct,
                               struct gen1_pkmn_data_struct pkmn_data,
                               u8 index)
{
    // index 0 - 5
    if (index >= 0 || index < 6) {
        file_struct->team_pokemon_list[index]->name        = pkmn_data.name;
        file_struct->team_pokemon_list[index]->ot_name     = pkmn_data.ot_name;
        file_struct->team_pokemon_list[index]->index       = pkmn_data.index;
        file_struct->team_pokemon_list[index]->hp          = pkmn_data.hp;
        file_struct->team_pokemon_list[index]->level       = pkmn_data.level;
        file_struct->team_pokemon_list[index]->status      = pkmn_data.status;
        file_struct->team_pokemon_list[index]->type[0]     = pkmn_data.type[0];
        file_struct->team_pokemon_list[index]->type[1]     = pkmn_data.type[1];
        file_struct->team_pokemon_list[index]->catch_item  = pkmn_data.catch_item;
        file_struct->team_pokemon_list[index]->moves[0]    = pkmn_data.moves[0];
        file_struct->team_pokemon_list[index]->moves[1]    = pkmn_data.moves[1];
        file_struct->team_pokemon_list[index]->moves[2]    = pkmn_data.moves[2];
        file_struct->team_pokemon_list[index]->moves[3]    = pkmn_data.moves[3];
        file_struct->team_pokemon_list[index]->trainer_id  = pkmn_data.trainer_id;
        file_struct->team_pokemon_list[index]->xp          = pkmn_data.xp;
        file_struct->team_pokemon_list[index]->hp_ev       = pkmn_data.hp_ev;
        file_struct->team_pokemon_list[index]->atk_ev      = pkmn_data.atk_ev;
        file_struct->team_pokemon_list[index]->def_ev      = pkmn_data.def_ev;
        file_struct->team_pokemon_list[index]->speed_ev    = pkmn_data.speed_ev;
        file_struct->team_pokemon_list[index]->special_ev  = pkmn_data.special_ev;
        file_struct->team_pokemon_list[index]->iv          = pkmn_data.iv;
        file_struct->team_pokemon_list[index]->moves_pp[0] = pkmn_data.moves_pp[0];
        file_struct->team_pokemon_list[index]->moves_pp[1] = pkmn_data.moves_pp[1];
        file_struct->team_pokemon_list[index]->moves_pp[2] = pkmn_data.moves_pp[2];
        file_struct->team_pokemon_list[index]->moves_pp[3] = pkmn_data.moves_pp[3];
        file_struct->team_pokemon_list[index]->level_opt   = pkmn_data.level_opt;
        file_struct->team_pokemon_list[index]->max_hp      = pkmn_data.max_hp;
        file_struct->team_pokemon_list[index]->atk         = pkmn_data.atk;
        file_struct->team_pokemon_list[index]->def         = pkmn_data.def;
        file_struct->team_pokemon_list[index]->speed       = pkmn_data.speed;
        file_struct->team_pokemon_list[index]->special     = pkmn_data.special;
    }
}

// others
u8 gen1_get_number_pkmn_party(struct gen1_pkmn_file_struct *file_struct)
{
    return file_struct->file_map[TEAM_POKEMON_LIST_ADDRESS];
}

struct gen1_pkmn_data_struct *gen1_get_pokemon_in_box(struct gen1_pkmn_file_struct *file_struct, u8 box_index, u8 pkmn_index)
{
    if(box_index > 0 && box_index < 12 && pkmn_index > 0 && pkmn_index < 20) {
        return file_struct->pc_box[box_index]->pokemon_list[pkmn_index];
    }

    return NULL;
}

void gen1_set_pokemon_in_box(struct gen1_pkmn_file_struct *file_struct,
                             struct gen1_pkmn_data_struct pkmn_data,
                             u8 box_index,
                             u8 pkmn_index)
{
    if(box_index > 0 && box_index < 12 && pkmn_index > 0 && pkmn_index < 20) {
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->name        = pkmn_data.name;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->ot_name     = pkmn_data.ot_name;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->index       = pkmn_data.index;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->hp          = pkmn_data.hp;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->level       = pkmn_data.level;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->status      = pkmn_data.status;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->type[0]     = pkmn_data.type[0];
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->type[1]     = pkmn_data.type[1];
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->catch_item  = pkmn_data.catch_item;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->moves[0]    = pkmn_data.moves[0];
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->moves[1]    = pkmn_data.moves[1];
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->moves[2]    = pkmn_data.moves[2];
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->moves[3]    = pkmn_data.moves[3];
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->trainer_id  = pkmn_data.trainer_id;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->xp          = pkmn_data.xp;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->hp_ev       = pkmn_data.hp_ev;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->atk_ev      = pkmn_data.atk_ev;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->def_ev      = pkmn_data.def_ev;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->speed_ev    = pkmn_data.speed_ev;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->special_ev  = pkmn_data.special_ev;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->iv          = pkmn_data.iv;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->moves_pp[0] = pkmn_data.moves_pp[0];
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->moves_pp[1] = pkmn_data.moves_pp[1];
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->moves_pp[2] = pkmn_data.moves_pp[2];
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->moves_pp[3] = pkmn_data.moves_pp[3];
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->level_opt   = pkmn_data.level_opt;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->max_hp      = pkmn_data.max_hp;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->atk         = pkmn_data.atk;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->def         = pkmn_data.def;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->speed       = pkmn_data.speed;
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->special     = pkmn_data.special;
    }
}

u8 gen1_get_pikachu_friendship(struct gen1_pkmn_file_struct *file_struct)
{
    return file_struct->pikachu_friendship[0];
}

void gen1_set_pikachu_friendship(struct gen1_pkmn_file_struct *file_struct, u8 value)
{
    file_struct->pikachu_friendship[0] = value;
}
