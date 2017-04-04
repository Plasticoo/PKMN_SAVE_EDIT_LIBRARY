#include "gen1/gen1.h"
#include "utils.h"

#include <stdlib.h>

int get_character_code(u8 c)
{
    int i;

    for (i = 0; i < FONT_SIZE; i++) {
        if (c == FONT[i]) {
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
        _name[i] = FONT[name[i]];
    }

    _name[i - 1] = '\0';
    return _name;
}

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

    name[++i] = 'P';

    while(i < 11) {
        name[++i] = 0x0;
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

u32 gen1_get_money(u8 *money)
{
    return __bcd_to_dec(money, MONEY_SIZE);
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

u8 gen1_get_option(struct gen1_pkmn_file_struct *file_struct, u8 option)
{
    u8 result = 0;

    switch(option) {
    case OPTION_TEXT_SPEED_FAST:
        result = file_struct->options[0] & OPTIONS_LOOKUP_TABLE[OPTION_TEXT_SPEED_FAST];
        break;
    case OPTION_TEXT_SPEED_NORMAL:
        result = file_struct->options[0] & OPTIONS_LOOKUP_TABLE[OPTION_TEXT_SPEED_NORMAL];
        break;
    case OPTION_TEXT_SPEED_SLOW:
        result = file_struct->options[0] & OPTIONS_LOOKUP_TABLE[OPTION_TEXT_SPEED_SLOW];
        break;
    case OPTION_SOUND_MONO:
        result = file_struct->options[0] & OPTIONS_LOOKUP_TABLE[OPTION_SOUND_MONO];
        break;
    case OPTION_SOUND_MONO_Y:
        result = file_struct->options[0] & OPTIONS_LOOKUP_TABLE[OPTION_SOUND_MONO_Y];
        break;
    case OPTION_SOUND_STEREO:
        result = file_struct->options[0] & OPTIONS_LOOKUP_TABLE[OPTION_SOUND_STEREO];
        break;
    case OPTION_SOUND_EARPHONE1:
        result = file_struct->options[0] & OPTIONS_LOOKUP_TABLE[OPTION_SOUND_EARPHONE1];
        break;
    case OPTION_SOUND_EARPHONE2:
        result = file_struct->options[0] & OPTIONS_LOOKUP_TABLE[OPTION_SOUND_EARPHONE2];
        break;
    case OPTION_SOUND_EARPHONE3:
        result = file_struct->options[0] & OPTIONS_LOOKUP_TABLE[OPTION_SOUND_EARPHONE3];
        break;
    case OPTION_BATTLE_STYLE_SWITCH:
        result = file_struct->options[0] & OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_STYLE_SWITCH];
        break;
    case OPTION_BATTLE_STYLE_SET:
        result = file_struct->options[0] & OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_STYLE_SET];
        break;
    case OPTION_BATTLE_EFFECTS_ON:
        result = file_struct->options[0] & OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_EFFECTS_ON];
        break;
    case OPTION_BATTLE_EFFECTS_OFF:
        result = file_struct->options[0] & OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_EFFECTS_OFF];
        break;
    default:
        PDEBUG("Option couldn't be retrieved.");
    }

    return result;
}

void gen1_set_option(struct gen1_pkmn_file_struct *file_struct, u8 option)
{
    switch(option) {
    case OPTION_TEXT_SPEED_FAST:
        set_clear_bits(&file_struct->options[0], OPTIONS_LOOKUP_TABLE[OPTION_TEXT_SPEED_FAST]);
        break;
    case OPTION_TEXT_SPEED_NORMAL:
        set_clear_bits(&file_struct->options[0], OPTIONS_LOOKUP_TABLE[OPTION_TEXT_SPEED_NORMAL]);
        break;
    case OPTION_TEXT_SPEED_SLOW:
        set_clear_bits(&file_struct->options[0], OPTIONS_LOOKUP_TABLE[OPTION_TEXT_SPEED_SLOW]);
        break;
    case OPTION_SOUND_MONO:
        set_clear_bits(&file_struct->options[0], OPTIONS_LOOKUP_TABLE[OPTION_SOUND_MONO]);
        break;
    case OPTION_SOUND_MONO_Y:
        set_clear_bits(&file_struct->options[0], OPTIONS_LOOKUP_TABLE[OPTION_SOUND_MONO_Y]);
        break;
    case OPTION_SOUND_STEREO:
        set_clear_bits(&file_struct->options[0], OPTIONS_LOOKUP_TABLE[OPTION_SOUND_STEREO]);
        break;
    case OPTION_SOUND_EARPHONE1:
        set_clear_bits(&file_struct->options[0], OPTIONS_LOOKUP_TABLE[OPTION_SOUND_EARPHONE1]);
        break;
    case OPTION_SOUND_EARPHONE2:
        set_clear_bits(&file_struct->options[0], OPTIONS_LOOKUP_TABLE[OPTION_SOUND_EARPHONE2]);
        break;
    case OPTION_SOUND_EARPHONE3:
        set_clear_bits(&file_struct->options[0], OPTIONS_LOOKUP_TABLE[OPTION_SOUND_EARPHONE3]);
        break;
    case OPTION_BATTLE_STYLE_SWITCH:
        set_clear_bits(&file_struct->options[0], OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_STYLE_SWITCH]);
        break;
    case OPTION_BATTLE_STYLE_SET:
        set_clear_bits(&file_struct->options[0], OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_STYLE_SET]);
        break;
    case OPTION_BATTLE_EFFECTS_ON:
        set_clear_bits(&file_struct->options[0], OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_EFFECTS_ON]);
        break;
    case OPTION_BATTLE_EFFECTS_OFF:
        set_clear_bits(&file_struct->options[0], OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_EFFECTS_OFF]);
        break;
    default:
        PDEBUG("Option couldnt be set!");
    }
}

void gen1_set_time_played(struct gen1_pkmn_time *time, u16 hours, u8 minutes, u8 seconds)
{
    if(hours < 1000 &&
       minutes < 100 &&
       seconds < 100) {
        time->seconds = seconds;
        time->minutes = minutes;
        time->hours = hours;

        return;
    }

    PDEBUG("Could not set time!");
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

    if(index <= 20) {
        if(index == 0) {
            idx = 0;
        } else {
            idx = index - 1;
        }

        file_struct->current_pc_box[0] = idx;
        return;
    }

    PDEBUG("Index invalid!");
}

struct gen1_pkmn_data_struct gen1_get_pokemon_in_party(struct gen1_pkmn_file_struct *file_struct, u8 index)
{
    return file_struct->team_pokemon_list[index];
}

void gen1_set_pokemon_in_party(struct gen1_pkmn_file_struct *file_struct,
                               struct gen1_pkmn_data_struct pkmn_data,
                               u8 index)
{
    // index 0 - 5
    if (index < 6) {
        file_struct->team_pokemon_list[index] = pkmn_data;
        return;
    }

    PDEBUG("Index not valid!");
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

    PDEBUG("Indexes not valid!");
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
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->xp[0]       = pkmn_data.xp[0];
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->xp[1]       = pkmn_data.xp[1];
        file_struct->pc_box[box_index]->pokemon_list[pkmn_index]->xp[2]       = pkmn_data.xp[2];
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

        return;
    }

    PDEBUG("Indexes not valid!");
}

u8 gen1_get_pikachu_friendship(struct gen1_pkmn_file_struct *file_struct)
{
    return file_struct->pikachu_friendship[0];
}

void gen1_set_pikachu_friendship(struct gen1_pkmn_file_struct *file_struct, u8 value)
{
    file_struct->pikachu_friendship[0] = value;
}

u8 gen1_get_item_pocket_count(struct gen1_pkmn_file_struct *file_struct)
{
    return file_struct->file_map[POCKET_ITEM_LIST_ADDRESS];
}

u8 gen1_get_item_box_count(struct gen1_pkmn_file_struct *file_struct)
{
    return file_struct->file_map[PC_ITEM_LIST_ADDRESS];
}

u8 gen1_get_pokedex_numbers(u8 *pokedex)
{
    u8 i;
    u8 count = 0;

    for(i = 0; i < POKEDEX_SIZE; i++) {
        if(gen1_get_pokedex(pokedex, i)) {
            count++;
        }
    }

    return count;
}
