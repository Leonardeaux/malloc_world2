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

int isWeapon(int Nextcase){// je recupère l'index après chaque tap dans les déplacements, et je regarde il est contenu dans ma liste pour déterminer s'il
    // s'agit d'une arme
    int listWeapon[] = {WOODEN_SWORD, STONE_SWORD, STONE_SPEAR, STONE_HAMMER, IRON_SWORD,
                        IRON_SPEAR, IRON_HAMMER, DIAMOND_SWORD, DIAMOND_SPEAR, DIAMOND_HAMMER};
    for(int i=0; i<10; i++){
        if(listWeapon[i] == Nextcase){
            return 1;
        }
    }
    return 0;
}

int isArmor(int Nextcase){//je recupère l'index après chaque tap dans les déplacements, et je regarde il est contenu dans ma liste pour déterminer s'il
    // s'agit d'une armure
    int listeArmor[] = {STONE_BREASTPLATE, IRON_BREASTPLATE, DIAMOND_BREASTPLATE};
    for(int i=0; i<3; i++){
        if(listeArmor[i]==Nextcase){
            return 1;
        }
    }
    return 0;
}

int isTools(int Nextcase){//je recupère l'index après chaque tap dans les déplacements, et je regarde il est contenu dans ma liste pour déterminer s'il
    // s'agit d'un outil
    int listeTools[] = {WOODEN_PICKAXE, WOODEN_BILLHOOK, WOODEN_AXE, STONE_PICKAXE, STONE_BILLHOOK, STONE_AXE, IRON_PICKAXE, IRON_BILLHOOK, IRON_AXE};
    for(int i=0; i<9; i++){
        if(listeTools[i]==Nextcase){
            return 1;
        }
    }
    return 0;
}

int isRessource(int Nextcase){//je recupère l'index après chaque tap dans les déplacements, et je regarde il est contenu dans ma liste pour déterminer s'il
    // s'agit d'une ressource
    int listeRessource[] = {FIR, ROCK, GRASS, BEECH, IRON, LAVENDER, OAK, DIAMOND, HEMP};
    for(int i=0; i<9; i++){
        if(listeRessource[i]==Nextcase){
            return 1;
        }
    }
    return 0;
}

int isPotion(int Nextcase){//je recupère l'index après chaque tap dans les déplacements, et je regarde il est contenu dans ma liste pour déterminer s'il
    // s'agit d'une potion
    int listePotion[] = {POTION_OF_LIFE_I, POTION_OF_LIFE_II, POTION_OF_LIFE_III};
    for(int i=0; i<3; i++){
        if(listePotion[i]== Nextcase){
            return 1;
        }
    }
    return 0;
}
// j'effectue la recherche uniquement pour les armes et les armures car elles sont limités
int getWeapon(Player* player1){
    int nbWeapon =0;
    int itemWeapon = 0;
    for(int i=0;i < 10; i++){
        itemWeapon = isWeapon(player1->inventory[i][1]);
        printf(" j ai ca : %d\n", itemWeapon);
        if(itemWeapon==1)
            nbWeapon++;
    }
    if(nbWeapon == 3){
        return 1;
    }else if(nbWeapon < 3){
        return 2;
    }else{
        return 0;
    }
}
// je recupère mon inventaire via le pointeur liste et je regarde si j'en est bien moins de 3 à chaque tape, dans le main, une condition
// à effectuer dans le cas où on aurait 4 armes ( un printf pour lui dire qu'on a déjà trop d'armes ? )
int getArmure(Player* player1){
    int item = 0;
    for(int i=0;i < LENGTH;i++){
        item = isArmor(player1->inventory[i][1]);
        //printf(" j ai ca : %d\n", item);
        if(item == 1){
            return 1;
        }
    }
    return 0;
}

// même chose pour un armure ( max 1)

int nbItem(int Nextcase, int* inventory){// l'inventaire
    int counter = 0;
    for(int i=0; i < LENGTH;i++){
        if(inventory[i]== Nextcase){
            counter++;
        }
    }
    return counter;
}
