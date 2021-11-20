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
    initialize_player(APlayer);
    create_weapon(0, APlayer, WOODEN_SWORD, "Wooden_sword", 10, 100, 100);
    create_tool(1, APlayer, WOODEN_AXE, "Wooden_axe", 100, 100);
    create_tool(2, APlayer, WOODEN_BILLHOOK, "Wooden_billhook", 100, 100);
    create_tool(3, APlayer, WOODEN_PICKAXE, "Wooden_pickaxe", 100, 100);

    spawn_player(APlayer, map[0], side);

    return APlayer;
}

void spawn_player(Player* player, int** map, int side){

    int i, j, x, y;

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

void initialize_player(Player *player){
    for(int i = 0; i < 10; i++){
        player->inventory[i].type = 0;
    }
}

int nb_free_space(Player *player){
    int nb_space = 0;

    for(int i = 0; i < 10; i++){
        if(player->inventory[i].type == 0)
            nb_space++;
    }
    return nb_space;
}

int locale_resource(int id_resource, Player *player){
    for(int i = 0; i < 10; i++){
        if(player->inventory[i].resource.id == id_resource){
            return i;
        }
    }

    return -1;
}

int can_recolt_resource(int id_entity, int quantity, Player *player){
    int index_resource = locale_resource(entity_bitmap[id_entity], player);
    if(nb_free_space(player) <= 0 || index_resource){
        return 0;
    }

    if(locale_resource()){

    }

}

int teleport_player(int*** map, int side, Player* player, int portal_x, int portal_y){
    if(player->level < 3 ){
        return 0;
    } else {

    }
}

void create_weapon(int index, Player *player, int id, char* name, int damage, float max_durability, float actual_durability){
    player->inventory[index].type = WEAPON;
    Weapon* AWeapon = &player->inventory[index].weapon;

    AWeapon->id = id;
    AWeapon->damage = damage;
    AWeapon->max_durability = max_durability;
    AWeapon->actual_durability = actual_durability;
    strcpy(AWeapon->name, name);
}

void create_tool(int index, Player *player, int id, char* name, float max_durability, float actual_durability){
    player->inventory[index].type = TOOL;
    Tool* ATool = &player->inventory[index].tool;

    ATool->id = id;
    ATool->max_durability = max_durability;
    ATool->actual_durability = actual_durability;
    strcpy(ATool->name, name);
}

void create_resource(int index, Player *player, int id, char* name, int quantity){
    player->inventory[index].type = RESOURCE;
    Resource * AResource = &player->inventory[index].resource;

    AResource->id = id;
    AResource->quantity = quantity;
    strcpy(AResource->name, name);
}

void create_armor(int index, Player *player, int id, char* name, float damage_reduction, float max_durability, float actual_durability){
    player->inventory[index].type = ARMOR;
    Armor * AArmor = &player->inventory[index].armor;

    AArmor->id = id;
    AArmor->damage_reduction = damage_reduction;
    AArmor->max_durability = max_durability;
    AArmor->actual_durability = actual_durability;
    strcpy(AArmor->name, name);
}