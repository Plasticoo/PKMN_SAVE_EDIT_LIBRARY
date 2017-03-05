
#ifndef __GEN1_STRUCTS_H_
#define __GEN1_STRUCTS_H_

#include <inttypes.h>
#include <sys/types.h>

#define FONT_SIZE 0x100
#define FILE_SIZE 0x8000

#define BOX_SIZE 20

#define OPTION_TEXT_SPEED_MASK 0x7
#define OPTION_SOUND_MASK 0x10
#define OPTION_BATTLE_STYLE_MASK 0x40
#define OPTION_BATTLE_EFFECTS_MASK 0x80

enum options {
    OPTION_TEXT_SPEED,
    OPTION_SOUND,
    OPTION_BATTLE_STYLE,
    OPTION_BATTLE_EFFECTS
};

enum badges {
    BOULDER_BADGE,
    CASCADE_BADGE,
    THUNDER_BADGE,
    RAINBOW_BADGE,
    SOUL_BADGE,
    MARSH_BADGE,
    VOLCANO_BADGE,
    EARTH_BADGE
};

enum {
    STATUS_ASLEEP = 0x04,
    STATUS_POISONED = 0x08,
    STATUS_BURNED = 0x10,
    STATUS_FROZEN = 0x20,
    STATUS_PARALYZED = 0x40,
};

enum {
    TYPE_NORMAL = 0x00,
    TYPE_FIGHTING = 0x01,
    TYPE_FLYING = 0x02,
    TYPE_POISON = 0x03,
    TYPE_GROUND = 0x04,
    TYPE_ROCK = 0x05,
    TYPE_BUG = 0x07,
    TYPE_GHOST = 0x08,
    TYPE_FIRE = 0x14,
    TYPE_WATER = 0x15,
    TYPE_GRASS = 0x16,
    TYPE_ELECTRIC = 0x17,
    TYPE_PSYCHIC = 0x18,
    TYPE_ICE = 0x19,
    TYPE_DRAGON = 0x1A,
};

enum {
    ITEM_NOTHING = 0x00,
    ITEM_MASTER_BALL = 0x01,
    ITEM_ULTRA_BALL = 0x02,
    ITEM_GREAT_BALL = 0x03,
    ITEM_POKE_BALL = 0x04,
    ITEM_TOWN_MAP = 0x05,
    ITEM_BICYCLE = 0x06,
    ITEM_UNNAMED = 0x07,
    ITEM_SAFARI_BALL = 0x08,
    ITEM_POKÉDEX = 0x09,
    ITEM_MOON_STONE = 0x0A,
    ITEM_ANTIDOTE = 0x0B,
    ITEM_BURN_HEAL = 0x0C,
    ITEM_ICE_HEAL = 0x0D,
    ITEM_AWAKENING = 0x0E,
    ITEM_PARLYZ_HEAL = 0x0F,
    ITEM_FULL_RESTORE = 0x10,
    ITEM_MAX_POTION = 0x11,
    ITEM_HYPER_POTION = 0x12,
    ITEM_SUPER_POTION = 0x13,
    ITEM_POTION = 0x14,
    ITEM_BOULDERBADGE = 0x15,
    ITEM_CASCADEBADGE = 0x16,
    ITEM_THUNDERBADGE = 0x17,
    ITEM_RAINBOWBADGE = 0x18,
    ITEM_SOULBADGE = 0x19,
    ITEM_MARSHBADGE = 0x1A,
    ITEM_VOLCANOBADGE = 0x1B,
    ITEM_EARTHBADGE = 0x1C,
    ITEM_ESCAPE_ROPE = 0x1D,
    ITEM_REPEL = 0x1E,
    ITEM_OLD_AMBER = 0x1F,
    ITEM_FIRE_STONE = 0x20,
    ITEM_THUNDER_STONE = 0x21,
    ITEM_WATER_STONE = 0x22,
    ITEM_HP_UP = 0x23,
    ITEM_PROTEIN = 0x24,
    ITEM_IRON = 0x25,
    ITEM_CARBOS = 0x26,
    ITEM_CALCIUM = 0x27,
    ITEM_RARE_CANDY = 0x28,
    ITEM_DOME_FOSSIL = 0x29,
    ITEM_HELIX_FOSSIL = 0x2A,
    ITEM_SECRET_KEY = 0x2B,
    ITEM_UNNAMED2 = 0x2C,
    ITEM_BIKE_VOUCHER = 0x2D,
    ITEM_X_ACCURACY = 0x2E,
    ITEM_LEAF_STONE = 0x2F,
    ITEM_CARD_KEY = 0x30,
    ITEM_NUGGET = 0x31,
    ITEM_PP_UP_GLITCHED = 0x32,
    ITEM_POKÉ_DOLL = 0x33,
    ITEM_FULL_HEAL = 0x34,
    ITEM_REVIVE = 0x35,
    ITEM_MAX_REVIVE = 0x36,
    ITEM_GUARD_SPEC = 0x37,
    ITEM_SUPER_REPEL = 0x38,
    ITEM_MAX_REPEL = 0x39,
    ITEM_DIRE_HIT = 0x3A,
    ITEM_COIN = 0x3B,
    ITEM_FRESH_WATER = 0x3C,
    ITEM_SODA_POP = 0x3D,
    ITEM_LEMONADE = 0x3E,
    ITEM_SS_TICKET = 0x3F,
    ITEM_GOLD_TEETH = 0x40,
    ITEM_X_ATTACK = 0x41,
    ITEM_X_DEFEND = 0x42,
    ITEM_X_SPEED = 0x43,
    ITEM_X_SPECIAL = 0x44,
    ITEM_COIN_CASE = 0x45,
    ITEM_OAKS_PARCEL = 0x46,
    ITEM_ITEMFINDER = 0x47,
    ITEM_SILPH_SCOPE = 0x48,
    ITEM_POKÉ_FLUTE = 0x49,
    ITEM_LIFT_KEY = 0x4A,
    ITEM_EXP_ALL = 0x4B,
    ITEM_OLD_ROD = 0x4C,
    ITEM_GOOD_ROD = 0x4D,
    ITEM_SUPER_ROD = 0x4E,
    ITEM_PP_UP = 0x4F,
    ITEM_ETHER = 0x50,
    ITEM_MAX_ETHER = 0x51,
    ITEM_ELIXER = 0x52,
    ITEM_MAX_ELIXER = 0x53,
    ITEM_HM01 = 0xC4,
    ITEM_HM02 = 0xC5,
    ITEM_HM03 = 0xC6,
    ITEM_HM04 = 0xC7,
    ITEM_HM05 = 0xC8,
    ITEM_TM01 = 0xC9,
    ITEM_TM02 = 0xCA,
    ITEM_TM03 = 0xCB,
    ITEM_TM04 = 0xCC,
    ITEM_TM05 = 0xCD,
    ITEM_TM06 = 0xCE,
    ITEM_TM07 = 0xCF,
    ITEM_TM08 = 0xD0,
    ITEM_TM09 = 0xD1,
    ITEM_TM10 = 0xD2,
    ITEM_TM11 = 0xD3,
    ITEM_TM12 = 0xD4,
    ITEM_TM13 = 0xD5,
    ITEM_TM14 = 0xD6,
    ITEM_TM15 = 0xD7,
    ITEM_TM16 = 0xD8,
    ITEM_TM17 = 0xD9,
    ITEM_TM18 = 0xDA,
    ITEM_TM19 = 0xDB,
    ITEM_TM20 = 0xDC,
    ITEM_TM21 = 0xDD,
    ITEM_TM22 = 0xDE,
    ITEM_TM23 = 0xDF,
    ITEM_TM24 = 0xE0,
    ITEM_TM25 = 0xE1,
    ITEM_TM26 = 0xE2,
    ITEM_TM27 = 0xE3,
    ITEM_TM28 = 0xE4,
    ITEM_TM29 = 0xE5,
    ITEM_TM30 = 0xE6,
    ITEM_TM31 = 0xE7,
    ITEM_TM32 = 0xE8,
    ITEM_TM33 = 0xE9,
    ITEM_TM34 = 0xEA,
    ITEM_TM35 = 0xEB,
    ITEM_TM36 = 0xEC,
    ITEM_TM37 = 0xED,
    ITEM_TM38 = 0xEE,
    ITEM_TM39 = 0xEF,
    ITEM_TM40 = 0xF0,
    ITEM_TM41 = 0xF1,
    ITEM_TM42 = 0xF2,
    ITEM_TM43 = 0xF3,
    ITEM_TM44 = 0xF4,
    ITEM_TM45 = 0xF5,
    ITEM_TM46 = 0xF6,
    ITEM_TM47 = 0xF7,
    ITEM_TM48 = 0xF8,
    ITEM_TM49 = 0xF9,
    ITEM_TM50 = 0xFA,
    ITEM_TM51 = 0xFB,
    ITEM_TM52 = 0xFC,
    ITEM_TM53 = 0xFD,
    ITEM_TM54 = 0xFE,
    ITEM_TM55 = 0xFF,
};

// Todo change number of bytes
struct gen1_pkmn_time {
    uint32_t hours;
    uint32_t minutes;
    uint32_t seconds;
};

struct gen1_pkmn_data_struct {
    uint8_t *name;
    uint8_t *ot_name;
    uint8_t *index;
    uint8_t *hp;
    uint8_t *level;
    uint8_t *status;
    uint8_t *type[2];
    uint8_t *catch_item;
    uint8_t *moves[4];
    uint8_t *trainer_id;
    uint8_t *xp;
    uint8_t *hp_ev;
    uint8_t *atk_ev;
    uint8_t *def_ev;
    uint8_t *speed_ev;
    uint8_t *special_ev;
    uint8_t *iv;
    uint8_t *moves_pp[4];
    uint8_t *level_opt;
    uint8_t *max_hp;
    uint8_t *atk;
    uint8_t *def;
    uint8_t *speed;
    uint8_t *special;
};

struct gen1_pkmn_box {
    struct gen1_pkmn_data_struct *pokemon_list[BOX_SIZE];
};

struct gen1_item {
    uint8_t index;
    uint8_t count;
};

// TODO Change uint8_t for the
// respective structure
struct gen1_pkmn_file_struct {
    uint8_t *player_name;
    uint8_t *pokedex_owned;
    uint8_t *pokedex_seen;
    struct gen1_item *pocket_item_list[20];
    uint8_t *money;
    uint8_t *rival_name;
    uint8_t *options;
    uint8_t *badges;
    uint8_t *player_trainer_id;
    uint8_t *pikachu_friendship;
    uint8_t *pc_item_list;
    uint8_t *current_pc_box;
    uint8_t *casino_coins;
    uint8_t *time_played;
    struct gen1_pkmn_data_struct *team_pokemon_list[6];
    uint8_t *current_box_list;
    uint8_t *checksum;
    struct gen1_pkmn_box *pc_box[12];
    uint8_t *file_map;
};

int gen1_save_changes(struct gen1_pkmn_file_struct *file_struct, char* file_name);
void gen1_set_checksum(struct gen1_pkmn_file_struct *file_struct);

// functions to get properties of the struct
char* gen1_get_name(uint8_t *name);
uint8_t gen1_get_pokedex(uint8_t *pokedex, uint8_t index);
uint32_t gen1_get_money(struct gen1_pkmn_file_struct *file_struct);
uint16_t gen1_get_casino_coins(struct gen1_pkmn_file_struct *file_struct);
uint8_t gen1_get_option(struct gen1_pkmn_file_struct *file_struct, enum options option);
void gen1_get_time_played(struct gen1_pkmn_file_struct *file_struct, struct gen1_pkmn_time *time);
uint8_t gen1_get_badge(struct gen1_pkmn_file_struct *file_struct, enum badges badge);
uint8_t gen1_get_current_pc_box(struct gen1_pkmn_file_struct *file_struct);
struct gen1_pkmn_data_struct *gen1_get_pokemon_in_party(struct gen1_pkmn_file_struct *file_struct, uint8_t index);
struct gen1_pkmn_data_struct *gen1_get_pokemon_in_box(struct gen1_pkmn_file_struct *file_struct, uint8_t box_index, uint8_t pkmn_index);

// functions to set properties of the struct
void gen1_set_name(uint8_t* name, char* new_name, size_t size);
void gen1_set_pokedex(uint8_t *pokedex, uint8_t index);
void gen1_unset_pokedex(uint8_t *pokedex, uint8_t index);
void gen1_set_money(struct gen1_pkmn_file_struct *file_struct, uint32_t value);
void gen1_set_casino_coins(struct gen1_pkmn_file_struct *file_struct, uint16_t value);
void gen1_set_option(struct gen1_pkmn_file_struct *file_struct, enum options option);
void gen1_set_time_played(struct gen1_pkmn_file_struct *file_struct, struct gen1_pkmn_time *time);
void gen1_set_badge(struct gen1_pkmn_file_struct *file_struct, enum badges badge);
void gen1_set_current_pc_box(struct gen1_pkmn_file_struct *file_struct, uint8_t index);
void gen1_set_pokemon_in_party(struct gen1_pkmn_file_struct *file_struct,
                               struct gen1_pkmn_data_struct pkmn_data,
                               uint8_t index);
void gen1_set_pokemon_in_box(struct gen1_pkmn_file_struct *file_struct,
                               struct gen1_pkmn_data_struct pkmn_data,
                               uint8_t box_index,
                               uint8_t pkmn_index);
// others
uint8_t gen1_get_number_pkmn_party(struct gen1_pkmn_file_struct *file_struct);

#endif
