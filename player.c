#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "player.h"
#include "utils.h"

#define MAX 3
#define LENGTH 10

Player* create_player(int*** map, int side, char* username){

    Player* APlayer = malloc(sizeof(Player));
    Item* Sword_item = malloc(sizeof(Item));
    Weapon* Sword = malloc(sizeof(Weapon));
    Sword_item->type = WEAPON;
    Sword_item->weapon = *Sword;


    APlayer->experience = 1;
    APlayer->level = 1;
    APlayer->hp_max = 100;
    APlayer->hp = 100;
    APlayer->actual_map = 0;
    strcpy(APlayer->username, username);
    APlayer->inventory[0] = *Sword_item;
    //TODO initialiser l'inventaire
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

void initialize(Player *player){// le mettre une fois le joueur crée
    for(int i=0; i<10; i++){
        player->inventory[i].type=0;
    }
}

int canGetWeapon(Player *player){// est ce que je peux prendre une arme ou pas, savoir combien j'ai d'arme
    int nbweapon=0;
    for(int i=0; i< 10; i++){
        if(player->inventory[i].type == 1)
            nbweapon++;
    }
    if(nbweapon <= 3) {
        return 1;
    }
    return 0;
}

int canGetArmor(Player *player){// est ce que je peux prendre une armure ou pas
    int nbArmor=0;
    for(int i=0; i< 10; i++){
        if(player->inventory[i].type == 5)
            nbArmor++;
    }
    if(nbArmor <= 1) {
        return 1;
    }else {
        return 0;
    }
}

int nbItemLibre(Player *player){// pour savoir toutes les places disponibles
    int nbitem =0;
    for(int i = 1; i<=10; i++){
        if(player->inventory[i].type==0)
            nbitem++;
    }
    return nbitem;
}

void makeWeapon(Player * player, int weapon){
    for(int i = 1; i <= 10; i++){
        if(player->inventory[i].type == 0){
            player->inventory[i].type = 1;
            player->inventory[i].weapon.id = weapon;
            player->inventory[i].weapon.damage = 1;
            player->inventory[i].weapon.max_durability = 10;
            player->inventory[i].weapon.actual_durability = 10;
            break;
        }
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

int canCreateWOODENSWORD(int id, Player *player){
    int i, j, damage;
    float max_durability, actual_durability;
    char *name;
    for(i = 1; i<=10; i++) {
        switch (id) {
            case 1:
                if (player->inventory[i].type == 3 && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 3) {
                    player->inventory[i].resource.quantity -= 3;
                    name = "WOODEN_SWORD";
                    damage = 1, max_durability = 10, actual_durability = 10;
                }
                break;
            case 8:
                if (player->inventory[i].type == 3 && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 2){
                    for(j = 1; j < 10; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == ROCK && player->inventory[j].resource.quantity >= 3){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 3;
                            name = "STONE_SWORD";
                            damage = 2, max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 19:
                if (player->inventory[i].type == 3 && player->inventory[i].resource.id == BEECH && player->inventory[i].resource.quantity >= 2){
                    for(j = 1; j <= 10; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == IRON && player->inventory[j].resource.quantity >= 7){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 7;
                            name = "IRON_SWORD";
                            damage = 5, max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            default:
                printf("mauvaise id");
                break;
        }
    }
    create_weapon(i, player, id, name, damage, max_durability, actual_durability);
    return 0;
}