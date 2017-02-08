#include "../../include/gen1/gen1_funcs.h"
#include "../../include/gen1/gen1_defines.h"
#include "../../include/gen1/gen1_structs.h"

#include <stdlib.h>

#define FONT_SIZE 256

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

int gen1_get_character_code(char c) {
    int i;

    for (i = 0; i < FONT_SIZE; i++) {
        if (c == fonts[i]) {
            return i;
        }
    }

    return -1;
}

char* gen1_get_player_name(uint8_t *player_name) {
    int i;

    char *name = malloc(sizeof(char) * PLAYER_NAME_SIZE);

    for (i = 0; i < PLAYER_NAME_SIZE; i++) {
        if(player_name[i] == 'P') break;
        name[i] = fonts[player_name[i]];
    }

    name[i] = '\0';

    return name;
}

void gen1_set_player_name(struct gen1_pkmn_file_struct *file_struct, char* player_name, int size) {
    int i, _s = size;

    if (size >= 11) {
        _s = 11;
    }

    for (i = 0; i < _s; i++) {
        file_struct->player_name[i] = player_name[i];
    }
}
