#include "../../include/gen1/gen1_funcs.h"
#include "../../include/gen1/gen1_defines.h"
#include "../../include/gen1/gen1_structs.h"
#include "../../include/gen1/gen1_math.h"

#include <stdlib.h>
#include <stdbool.h>

#define FONT_SIZE 256
#define FILE_SIZE 0x8000

#define OPTION_TEXT_SPEED_MASK 7
#define OPTION_SOUND_MASK 8
#define OPTION_BATTLE_STYLE_MASK 64
#define OPTION_BATTLE_EFFECTS_MASK 128

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

int get_character_code(char c) {
    int i;

    for (i = 0; i < FONT_SIZE; i++) {
        if (c == fonts[i]) {
            return i;
        }
    }

    // return space code, as in, invalid character
    return 0x7F;
}

int gen1_save_changes(struct gen1_pkmn_file_struct *file_struct, char* file_name) {
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

void gen1_set_checksum(struct gen1_pkmn_file_struct *file_struct) {
    uint8_t checksum = gen1_checksum_map(file_struct->file_map);
    file_struct->checksum[0] = checksum;
}

char* gen1_get_name(uint8_t *name) {
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
void gen1_set_name(uint8_t* name, char* new_name, size_t size) {
    size_t i;
    size_t _s = size;

    if (size >= 7) {
        _s = 7;
    }

    for (i = 0; i < _s; i++) {
        name[i] = get_character_code(new_name[i]);
    }
}

uint8_t gen1_get_pokedex(uint8_t *pokedex, uint8_t index) {
    return pokedex[index >> 3] >> (index & 7) & 1;
}

void gen1_set_pokedex(uint8_t *pokedex, uint8_t index) {
    pokedex[index >> 3] |= 1 << (index & 7);
}

void gen1_unset_pokedex(uint8_t *pokedex, uint8_t index) {
    pokedex[index >> 3] &= ~(1 << (index & 7));
}

uint32_t gen1_get_money(struct gen1_pkmn_file_struct *file_struct) {
    return __bcd_to_dec(file_struct->money, MONEY_SIZE);
}

void gen1_set_money(struct gen1_pkmn_file_struct *file_struct, uint32_t value) {
    uint8_t buffer[MONEY_SIZE];

    __dec_to_bcd(value, buffer);

    file_struct->money[0] = buffer[0];
    file_struct->money[1] = buffer[1];
    file_struct->money[2] = buffer[2];
}

uint16_t gen1_get_casino_coins(struct gen1_pkmn_file_struct *file_struct) {
    return __bcd_to_dec(file_struct->casino_coins, CASINO_COINS_SIZE);
}

void gen1_set_casino_coins(struct gen1_pkmn_file_struct *file_struct, uint16_t value) {
    uint8_t buffer[CASINO_COINS_SIZE];

    __dec_to_bcd(value, buffer);

    file_struct->casino_coins[0] = buffer[0];
    file_struct->casino_coins[1] = buffer[1];
}

uint8_t gen1_get_option(struct gen1_pkmn_file_struct *file_struct, enum options option) {
    uint8_t result;

    switch(option) {
    case OPTION_TEXT_SPEED:
        result = file_struct->options[0] & 7;
        break;
    case OPTION_SOUND:
        result = file_struct->options[0] & 8;
        break;
    case OPTION_BATTLE_STYLE:
        result = file_struct->options[0] & 64;
        break;
    case OPTION_BATTLE_EFFECTS:
        result = file_struct->options[0] & 128;
        break;
    }

    return result;
}
