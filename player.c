#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "player.h"
#include "utils.h"

Player* create_player(int*** map, int side, char* username){

    Player* APlayer = malloc(sizeof(Player));

    APlayer->experience = 1;
    APlayer->level = 1;
    APlayer->hp_max = 100;
    APlayer->hp = 100;
    APlayer->actual_map = 0;
    strcpy(APlayer->username, username);
    APlayer->inventory[0] = *create_weapon(WOODEN_SWORD, "Wooden_sword", 10, 100, 100);
    APlayer->inventory[1] = *create_tool(WOODEN_AXE, "Wooden_axe", 100, 100);
    APlayer->inventory[2] = *create_tool(WOODEN_BILLHOOK, "Wooden_billhook", 100, 100);
    APlayer->inventory[3] = *create_tool(WOODEN_PICKAXE, "Wooden_pickaxe", 100, 100);

    spawn_player(APlayer, map[0], side);

    return APlayer;
}

void spawn_player(Player* player, int** map, int side){

    int i;
    int j;
    int x;
    int y;

    for(i = 0; i < side; i++){
        for(j = 0; j < side; j++){
            if(map[i][j] == 2){
                x = i;
                y = j;
            }
        }
    }

    if(x < side - 1){
        player->coord_x = x + 1;
        player->coord_y = y;
    } else if(x > 0){
        player->coord_x = x - 1;
        player->coord_y = y;
    } else if(y < side - 1){
        player->coord_x = x;
        player->coord_y = y + 1;
    } else {
        player->coord_x = x;
        player->coord_y = y - 1;
    }

    map[player->coord_x][player->coord_y] = 1;
}

int teleport_player(int*** map, int side, Player* player, int portal_x, int portal_y){
    if(player->level < 3 ){
        return 0;
    } else {

    }
}

Item* create_weapon(int id, char* name, int damage, float max_durability, float actual_durability){
    Item* AItem = malloc(sizeof(Item));
    Weapon* AWeapon = malloc(sizeof(Weapon));
    AWeapon->id = id;
    AWeapon->damage = damage;
    AWeapon->max_durability = max_durability;
    AWeapon->actual_durability = actual_durability;
    strcpy(AWeapon->name, name);

    AItem->type = WEAPON;
    AItem->weapon = *AWeapon;

    return AItem;
}

Item* create_tool(int id, char* name, float max_durability, float actual_durability){
    Item* AItem = malloc(sizeof(Item));
    Tool* ATool = malloc(sizeof(Tool));
    ATool->id = id;
    ATool->max_durability = max_durability;
    ATool->actual_durability = actual_durability;
    strcpy(ATool->name, name);

    AItem->type = TOOL;
    AItem->tool = *ATool;

    return AItem;
}

Item* create_resource(int id, char* name, int quantity){
    Item* AItem = malloc(sizeof(Item));
    Resource* AResource = malloc(sizeof(Resource));
    AResource->id = id;
    AResource->quantity = quantity;
    strcpy(AResource->name, name);

    AItem->type = RESOURCE;
    AItem->resource = *AResource;

    return AItem;
}
