#ifndef MALLOC_WORLD_MONSTER_H
#define MALLOC_WORLD_MONSTER_H

typedef struct Monster {
    int id;
    int id_zone;
    char name[255];
    int hp;
    int hp_max;
    int damage;
    int gain_xp;
} Monster;

typedef enum monster {
    PIOU = 12,
    TOFU = 13,
    BOUFTOU = 14,
    CRAQUELEUR = 15,
    ABRAKNYDE = 16,
    POOLAY = 17,
    BOUFMOUTH = 18,
    GIVREFOUX = 19,
    APERIGLOURS = 20,
    COMTE_HAREBOURG = 99
} monsters;

static char* id_monster_name[] = {
        "Piou",
        "Tofu",
        "Bouftou",
        "Craqueleur",
        "Abraknyde",
        "Poolay",
        "Boufmouth",
        "Givrefoux",
        "Aperiglours",
        "Comte_harebourg"
};

static int zone_one_monsters[3] = {
    PIOU,
    TOFU,
    BOUFTOU
};

static int zone_two_monsters[3] = {
    CRAQUELEUR,
    ABRAKNYDE,
    POOLAY
};

static int zone_three_monsters[4] = {
    BOUFMOUTH,
    GIVREFOUX,
    APERIGLOURS,
    COMTE_HAREBOURG
};

Monster* initialize_monster(int id_monster);

int monster_zone(int id_monster);

void create_monster_zone_one(Monster* monster);

void create_monster_zone_two(Monster* monster);

void create_monster_zone_three(Monster* monster);

int return_random_monster_id(int id_zone);

#endif //MALLOC_WORLD_MONSTER_H
