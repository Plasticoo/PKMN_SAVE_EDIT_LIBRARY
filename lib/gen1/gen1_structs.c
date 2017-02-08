#include "../../include/gen1/gen1_funcs.h"
#include "../../include/gen1/gen1_defines.h"
#include "../../include/gen1/gen1_structs.h"

#include <stdlib.h>

#define FONT_SIZE 256
#define FILE_SIZE 32768

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

int gen1_save_changes(char* file_name, uint8_t *file_map) {
    int i;
    FILE* _f;

    if((_f = fopen(file_name, "wb")) == NULL) {
        return -1;
    }

    for (i = 0; i < FILE_SIZE; i++) {
        fwrite(&file_map[i], 1, 1, _f);
    }

    fclose(_f);

    return 0;
}

void gen1_set_checksum(struct gen1_pkmn_file_struct *file_struct, uint8_t *file_map) {
    uint8_t checksum = gen1_checksum_map(file_map);
    file_struct->checksum[0] = checksum;
}

char* gen1_get_player_name(uint8_t *player_name) {
    int i;

    char *name = calloc(PLAYER_NAME_SIZE, sizeof(char));

    for (i = 0; i < PLAYER_NAME_SIZE; i++) {
        if(player_name[i] == 'P') break;
        name[i] = fonts[player_name[i]];
    }

    name[i] = '\0';

    return name;
}

// TODO handling of the 'P' character that is needed for string termination
void gen1_set_player_name(struct gen1_pkmn_file_struct *file_struct, char* player_name, int size) {
    int i, _s = size;

    if (size >= 7) {
        _s = 7;
    }

    for (i = 0; i < _s; i++) {
        file_struct->player_name[i] = get_character_code(player_name[i]);
    }
}
