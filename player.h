#ifndef MALLOC_WORLD_PLAYER_H
#define MALLOC_WORLD_PLAYER_H

typedef struct Weapon{
    int id;
    char name[255];
    int damage;
    float max_durability;
    float actual_durability;
} Weapon;

typedef struct Tool{
    int id;
    char name[255];
    float max_durability;
    float actual_durability;
} Tool;

typedef struct Resource{
    int id;
    int quantity;
} Resource;

typedef struct Consumable{
    int id;
} Consumable;

typedef struct Armor{
    int id;
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
    int experience;
    int level;
    int hp;
    int hp_max;
    Item inventory[10];
} Player;

Player* create_player(int*** map, int side, char* username);

void spawn_player(Player* player, int** map, int side);

int MyGetch();

void Locate(int x,int y);

int isWeapon(int Nextcase);

int isArmor(int Nextcase);

int isTools(int Nextcase);

int isRessource(int Nextcase);

int isPotion(int Nextcase);

int getWeapon(Player* player1);

int getArmure(Player* player1);

int nbItem(int Nextcase, int* inventory);

#endif