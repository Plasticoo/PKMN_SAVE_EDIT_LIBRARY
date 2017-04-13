#include "gen1/gen1.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

static inline u8 n_digits(u32 n) {
    u8 count = 0;

    while(n != 0) {
        n /= 10;
        count++;
    }

    return count;
}

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
    if(pokedex && index < 152) {
        return pokedex[index >> 3] >> (index & 7) & 1;
    }

    return 0;
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
    if(money[1] == 0 && money[2] == 0) {
        return __bcd_to_dec(money, 1);
    } else if(money[1] != 0 && money[2] == 0) {
        return __bcd_to_dec(money, 2);
    }

    return __bcd_to_dec(money, MONEY_SIZE);
}

void gen1_set_money(u8 *money, u32 value)
{
    u8 buffer[MONEY_SIZE];

    __dec_to_bcd(value, buffer);

    memcpy(money, buffer, MONEY_SIZE);
}

u16 gen1_get_casino_coins(u8 *casino_coins)
{
    if(!casino_coins) {
        PDEBUG("Could not get casino coins.\n");
        return 0;
    }

    if(casino_coins[1] == 0) {
        return __bcd_to_dec(casino_coins, 1);
    }

    return __bcd_to_dec(casino_coins, CASINO_COINS_SIZE);
}

void gen1_set_casino_coins(u8 *casino_coins, u16 value)
{
    if(!casino_coins) {
        PDEBUG("Could not set casino coins.\n");
        return;
    }

    u8 buffer[CASINO_COINS_SIZE];

    __dec_to_bcd(value, buffer);

    if(n_digits(value) == 1 || n_digits(value) == 2) {
        casino_coins[0] = buffer[0];
        casino_coins[1] = 0;

        return;
    }

    memcpy(casino_coins, buffer, CASINO_COINS_SIZE);
}

u8 gen1_get_option(u8 *options, u8 flag)
{
    if (!options) {
        PDEBUG("Could not get option.\n");
        return 0;
    }

    u8 result = 0;

    switch(flag) {
    case OPTION_TEXT_SPEED_FAST:
        result = options[0] & OPTIONS_LOOKUP_TABLE[OPTION_TEXT_SPEED_FAST];
        break;
    case OPTION_TEXT_SPEED_NORMAL:
        result = options[0] & OPTIONS_LOOKUP_TABLE[OPTION_TEXT_SPEED_NORMAL];
        break;
    case OPTION_TEXT_SPEED_SLOW:
        result = options[0] & OPTIONS_LOOKUP_TABLE[OPTION_TEXT_SPEED_SLOW];
        break;
    case OPTION_SOUND_MONO:
        result = options[0] & OPTIONS_LOOKUP_TABLE[OPTION_SOUND_MONO];
        break;
    case OPTION_SOUND_MONO_Y:
        result = options[0] & OPTIONS_LOOKUP_TABLE[OPTION_SOUND_MONO_Y];
        break;
    case OPTION_SOUND_STEREO:
        result = options[0] & OPTIONS_LOOKUP_TABLE[OPTION_SOUND_STEREO];
        break;
    case OPTION_SOUND_EARPHONE1:
        result = options[0] & OPTIONS_LOOKUP_TABLE[OPTION_SOUND_EARPHONE1];
        break;
    case OPTION_SOUND_EARPHONE2:
        result = options[0] & OPTIONS_LOOKUP_TABLE[OPTION_SOUND_EARPHONE2];
        break;
    case OPTION_SOUND_EARPHONE3:
        result = options[0] & OPTIONS_LOOKUP_TABLE[OPTION_SOUND_EARPHONE3];
        break;
    case OPTION_BATTLE_STYLE_SWITCH:
        result = options[0] & OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_STYLE_SWITCH];
        break;
    case OPTION_BATTLE_STYLE_SET:
        result = options[0] & OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_STYLE_SET];
        break;
    case OPTION_BATTLE_EFFECTS_ON:
        result = options[0] & OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_EFFECTS_ON];
        break;
    case OPTION_BATTLE_EFFECTS_OFF:
        result = options[0] & OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_EFFECTS_OFF];
        break;
    default:
        PDEBUG("Option couldn't be retrieved.");
    }

    return result;
}

void gen1_set_option(u8 *options, u8 flag)
{
    if(!options) {
        PDEBUG("Could not set option.\n");
        return;
    }

    switch(flag) {
    case OPTION_TEXT_SPEED_FAST:
        set_clear_bits(&options[0], OPTIONS_LOOKUP_TABLE[OPTION_TEXT_SPEED_FAST]);
        break;
    case OPTION_TEXT_SPEED_NORMAL:
        set_clear_bits(&options[0], OPTIONS_LOOKUP_TABLE[OPTION_TEXT_SPEED_NORMAL]);
        break;
    case OPTION_TEXT_SPEED_SLOW:
        set_clear_bits(&options[0], OPTIONS_LOOKUP_TABLE[OPTION_TEXT_SPEED_SLOW]);
        break;
    case OPTION_SOUND_MONO:
        set_clear_bits(&options[0], OPTIONS_LOOKUP_TABLE[OPTION_SOUND_MONO]);
        break;
    case OPTION_SOUND_MONO_Y:
        set_clear_bits(&options[0], OPTIONS_LOOKUP_TABLE[OPTION_SOUND_MONO_Y]);
        break;
    case OPTION_SOUND_STEREO:
        set_clear_bits(&options[0], OPTIONS_LOOKUP_TABLE[OPTION_SOUND_STEREO]);
        break;
    case OPTION_SOUND_EARPHONE1:
        set_clear_bits(&options[0], OPTIONS_LOOKUP_TABLE[OPTION_SOUND_EARPHONE1]);
        break;
    case OPTION_SOUND_EARPHONE2:
        set_clear_bits(&options[0], OPTIONS_LOOKUP_TABLE[OPTION_SOUND_EARPHONE2]);
        break;
    case OPTION_SOUND_EARPHONE3:
        set_clear_bits(&options[0], OPTIONS_LOOKUP_TABLE[OPTION_SOUND_EARPHONE3]);
        break;
    case OPTION_BATTLE_STYLE_SWITCH:
        set_clear_bits(&options[0], OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_STYLE_SWITCH]);
        break;
    case OPTION_BATTLE_STYLE_SET:
        set_clear_bits(&options[0], OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_STYLE_SET]);
        break;
    case OPTION_BATTLE_EFFECTS_ON:
        set_clear_bits(&options[0], OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_EFFECTS_ON]);
        break;
    case OPTION_BATTLE_EFFECTS_OFF:
        set_clear_bits(&options[0], OPTIONS_LOOKUP_TABLE[OPTION_BATTLE_EFFECTS_OFF]);
        break;
    default:
        PDEBUG("Option couldnt be set!\n");
    }
}

void gen1_get_time_played(struct gen1_pkmn_time *time, struct gen1_pkmn_time *dest)
{
    if(time && dest) {
        time->seconds = dest->seconds;
        time->minutes = dest->minutes;
        time->hours   = dest->hours;
    }

    PDEBUG("Could not get time.\n");
}

void gen1_set_time_played(struct gen1_pkmn_time *time, u16 hours, u8 minutes, u8 seconds)
{
    if(hours < 1000 &&
       minutes < 100 &&
       seconds < 100 &&
        time) {
        time->seconds = seconds;
        time->minutes = minutes;
        time->hours = hours;

        return;
    }

    PDEBUG("Could not set time!\n");
}

u8 gen1_get_badge(u8 *badges, enum badges badge)
{
    return badges[0] & (1 << badge);
}

void gen1_set_badge(u8 *badges, enum badges badge)
{
    badges[0] ^= badge;
}

u8 gen1_get_current_pc_box(u8 *current_pc_box)
{
    return current_pc_box[0] + 1;
}

void gen1_set_current_pc_box(u8 *current_pc_box, u8 index)
{
    u8 idx;

    if(index <= 20) {
        if(index == 0) {
            idx = 0;
        } else {
            idx = index - 1;
        }

        current_pc_box[0] = idx;
        return;
    }

    PDEBUG("Index invalid!");
}

struct gen1_pkmn_data_struct gen1_get_pokemon_in_party(struct gen1_pkmn_data_struct *pokemon_party, u8 index)
{
    return pokemon_party[index];
}

// others
u8 gen1_get_number_pkmn_party(u8 *file_map)
{
    return file_map[TEAM_POKEMON_LIST_ADDRESS];
}

struct gen1_pkmn_data_struct *gen1_get_pokemon_in_box(struct gen1_pkmn_box *pc_box[], u8 box_index, u8 pkmn_index)
{
    if(box_index > 0 && box_index < 12 && pkmn_index > 0 && pkmn_index < 20) {
        return pc_box[box_index]->pokemon_list[pkmn_index];
    }

    PDEBUG("Indexes not valid!");
    return NULL;
}

void gen1_set_pokemon(struct gen1_pkmn_data_struct *pkmn_data,
                      struct gen1_pkmn_data_struct pkmn_new)
{
    if(pkmn_data != NULL) {
        *pkmn_data = pkmn_new;
    }
}

u8 gen1_get_pikachu_friendship(u8 *pikachu_friendship)
{
    return pikachu_friendship[0];
}

void gen1_set_pikachu_friendship(u8 *pikachu_friendship, u8 value)
{
    pikachu_friendship[0] = value;
}

u8 gen1_get_item_pocket_count(u8 *file_map)
{
    return file_map[POCKET_ITEM_LIST_ADDRESS];
}

u8 gen1_get_item_box_count(u8 *file_map)
{
    return file_map[PC_ITEM_LIST_ADDRESS];
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
