#ifndef MAC_WINDOWS_TEST_MAP_H
#define MAC_WINDOWS_TEST_MAP_H

#define MIN_PLANT 3
#define MIN_ROCK 3
#define MIN_WOOD 3

typedef enum entity {
    PORTAL_1_2 = -3,
    PORTAL_2_3 = -2,
    IMPOSSIBLE = -1,
    OPEN = 0,
    PLAYER = 1,
    NPC = 2,
    PLANT_1 = 3,
    ROCK_1 = 4,
    WOOD_1 = 5,
    PLANT_2 = 6,
    ROCK_2 = 7,
    WOOD_2 = 8,
    PLANT_3 = 9,
    ROCK_3 = 10,
    WOOD_3 = 11,
    END_BOSS = 99,
} entity;

typedef enum entity_type {
    OPEN_TYPE = 0,
    NPC_TYPE = 1,
    RESOURCE_TYPE = 2,
    MONSTER_TYPE = 3,
    PORTAL_TYPE = 4
} entity_type;

int*** create_maps(int side);

int*** malloc_map(int side);

void generate_portals(int*** map, int side);

int verif_map(int*** map, int side);

void square_access(int** map, int side, int x, int y);

void print_map(int*** map, int side);

void free_map(int*** map, int side);

int check_valid_case(int** map, int side, int x, int y, char direction);

int collect_resource();

#endif