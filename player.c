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
    for(int i=0; i<10; i++){
        if(player->inventory[i].type==0)
            nbitem++;
    }
    return nbitem;
}

int getArme(Player * player, int weapon){// créer une arme
    for(int i = 0; i < 10; i++){
        if(player->inventory[i].type == 0){
            player->inventory[i].type = 1;
            player->inventory[i].type = weapon;
            return 1;
        }
    }
    return 0;
}

int canCreateEpeeBois(Player *player){// pour une épée en bois, 3 sapin condition
    for(int i=0; i<10; i++){
        if(player->inventory[i].type==3){
            if(player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity>=3)
                return 1;
        }
    }
    return 0;
}


void createEpeeBois(Player *player){ // créer pour une épée en bois
    for(int i=0; i<10; i++){
        if(player->inventory[i].type==3){
            if(player->inventory[i].resource.id == FIR)
                player->inventory[i].resource.quantity -= 3;
            break;
        }
    }

    getArme(player, WOODEN_SWORD);// renvoi pour créer une arme
}