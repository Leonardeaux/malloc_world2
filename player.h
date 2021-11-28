#ifndef MALLOC_WORLD_PLAYER_H
#define MALLOC_WORLD_PLAYER_H

typedef struct Weapon{
    int id;
    char name[255];
    int damage;
    int max_durability;
    int actual_durability;
} Weapon;

typedef struct Tool{
    int id;
    char name[255];
    int max_durability;
    int actual_durability;
} Tool;

typedef struct Resource{
    int id;
    char name[255];
    int quantity;
} Resource;

typedef struct Consumable{
    int id;
    char name[255];
    int hp_gain;
} Consumable;

typedef struct Armor{
    int id;
    double damage_reduction;
    char name[255];
} Armor;

typedef struct Item{
    int type;
    union {
        Weapon weapon;
        Tool tool;
        Resource resource;
        Consumable consumable;
        Armor armor;
    };
} Item;

typedef enum weapon {
    WOODEN_SWORD = 1,   //Épée en bois
    STONE_SWORD = 8,    //Épée en pierre
    STONE_SPEAR = 9,    //Lance en pierre
    STONE_HAMMER = 10,  //Marteau en pierre
    IRON_SWORD = 19,    //Épée en fer
    IRON_SPEAR = 20,    //Lance en fer
    IRON_HAMMER = 21,   //Marteau en fer
    DIAMOND_SWORD = 30, //Épée en diamant
    DIAMOND_SPEAR = 31,    //Lance en diamant
    DIAMOND_HAMMER = 32,   //Marteau en diamant
} weapon;

typedef enum tool {
    WOODEN_PICKAXE = 2, //Pioche en bois
    WOODEN_BILLHOOK = 3,//Serpe en bois
    WOODEN_AXE = 4,     //Hache en bois
    STONE_PICKAXE = 12, //Pioche en pierre
    STONE_BILLHOOK = 13,//Serpe en pierre
    STONE_AXE = 14,     //Hache en pierre
    IRON_PICKAXE = 23,  //Pioche en fer
    IRON_BILLHOOK = 24, //Serpe en fer
    IRON_AXE = 25,      //Hache en fer
} tool;

typedef enum resource {
    FIR = 5,        //Sapin
    ROCK = 6,       //Pierre
    GRASS = 7,      //Herbe
    BEECH = 16,     //Hêtre
    IRON = 17,      //Fer
    LAVENDER = 18,  //Lavande
    OAK = 27,       //Chêne
    DIAMOND = 28,   //Diamant
    HEMP = 29,      //Chanvre
} resource;

typedef enum armor {
    STONE_BREASTPLATE = 11,     //Plastron en pierre
    IRON_BREASTPLATE = 22,      //Plastron en fer
    DIAMOND_BREASTPLATE = 33    //Plastron en diamant
} armor;

typedef enum consumable {
    POTION_OF_LIFE_I = 15,      //Potion de vie I
    POTION_OF_LIFE_II = 26,     //Potion de vie II
    POTION_OF_LIFE_III = 34,    //Potion de vie III

} consumable;

typedef enum type {
    WEAPON = 1,
    TOOL = 2,
    RESOURCE = 3,
    CONSUMABLE = 4,
    ARMOR = 5
} type;

typedef struct Player{
    char username[255];
    int actual_map;
    int coord_x;
    int coord_y;
    int xp;
    int next_xp;
    int level;
    int hp;
    int hp_max;
    Item inventory[10];
    Item coffre[34];
} Player;

static char* id_items_name[] = {
        "",
        "Wooden_sword",
        "Wooden_pickaxe",
        "Wooden_billhook",
        "Wooden_pickaxe",
        "Fir",
        "Rock",
        "Grass",
        "Stone_sword",
        "Stone_spear",
        "Stone_hammer",
        "Stone_breastplate",
        "Stone_pickaxe",
        "Stone_billhook",
        "Stone_axe",
        "Potion_of_life_I",
        "Beech",
        "Iron",
        "Lavender",
        "Iron_sword",
        "Iron_spear",
        "Iron_hammer",
        "Iron_breastplate",
        "Iron_pickaxe",
        "Iron_billhook",
        "Iron_axe",
        "Potion_of_life_II",
        "Oak",
        "Diamond",
        "Hemp",
        "Diamond_sword",
        "Diamond_spear",
        "Diamond_hammer",
        "Diamond_breastplate",
        "Potion_of_life_III"
};

static int xp_gain_hp_tab[] = {
        0,
        0,
        10,
        20,
        30,
        40,
        50,
        50,
        50,
        75,
        75
};

Player* create_player(int*** map, int side, char* username);

void spawn_player(Player* player, int** map, int side);

void initialize_player(Player *player);

int nb_free_space(Player* player);

int locale_resource(int id_resource, Player *player);

int locale_resource_quantity(int id_resource, Player *player, int quantity);

int locale_first_free_case(Player *player);

int can_recolt_resource(int id_entity, Player* player);

int recolt_resource_process(int id_resource, int quantity, Player* player);

int can_teleport_player(int*** map, int side, Player* player, int portal_case);

void teleport_player(int*** map, int side, Player* player, int portal_case, int new_map);

void create_weapon(int index, Player* player, int id, char* name, int damage, int max_durability, int actual_durability);

void create_tool(int index, Player* player, int id, char* name, int max_durability, int actual_durability);

void create_resource(int index, Player* player, int id, char* name, int quantity);

void create_armor(int index, Player* player, int id, char* name, double damage_reduction);

void create_consumable(int index, Player *player, int id, char* name, int hp_gain);

void print_player(Player* player);

void print_inventory(Player* player);

int weapon_in_inventory(Player* player, int id_weapon);

int tool_in_inventory(Player* player, int id_tool);

int verif_tool_entity(int id_entity);

double entity_coeff(int id_entity);

int entity_rank(int id_entity);

int* valable_tools(int id_entity);

int* weapons_in_inventory(Player* player);

int* consumables_in_inventory(Player* player);

int armor_in_inventory(Player* player);

#endif