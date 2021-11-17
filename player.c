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

int isWeapon(Item item){// je recupère l'index après chaque tap dans les déplacements, et je regarde il est contenu dans ma liste pour déterminer s'il
    // s'agit d'une arme
    /*int listWeapon[] = {WOODEN_SWORD, STONE_SWORD, STONE_SPEAR, STONE_HAMMER, IRON_SWORD,
                        IRON_SPEAR, IRON_HAMMER, DIAMOND_SWORD, DIAMOND_SPEAR, DIAMOND_HAMMER};
    */
    for(int i=0; i<10; i++){
        if(item.type == 1){
            return 1;
        }
    }
    return 0;
}

int getWeapon(Player* player1){
    int nbWeapon =0;
    int itemWeapon = 0;
    for(int i=0;i < 10; i++){
        itemWeapon = isWeapon(player1->inventory[i]);
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

int isArmor(Item item){//je recupère l'index après chaque tap dans les déplacements, et je regarde il est contenu dans ma liste pour déterminer s'il
    // s'agit d'une armure
    /*int listeArmor[] = {STONE_BREASTPLATE, IRON_BREASTPLATE, DIAMOND_BREASTPLATE};*/
    for(int i=0; i<3; i++){
        if(item.type == 5){
            return 1;
        }
    }
    return 0;
}

int isTools(Item item){//je recupère l'index après chaque tap dans les déplacements, et je regarde il est contenu dans ma liste pour déterminer s'il
    // s'agit d'un outil
    for(int i=0; i<10; i++){
        if(item.type == 2){
            return 1;
        }
    }
    return 0;
}

int isRessource(Item item){//je recupère l'index après chaque tap dans les déplacements, et je regarde il est contenu dans ma liste pour déterminer s'il
    // s'agit d'une ressource
    for(int i=0; i<10; i++){
        if(item.type == 3){
            return 1;
        }
    }
    return 0;
}

int isPotion(Item item){//je recupère l'index après chaque tap dans les déplacements, et je regarde il est contenu dans ma liste pour déterminer s'il
    // s'agit d'une potion
    int listePotion[] = {POTION_OF_LIFE_I, POTION_OF_LIFE_II, POTION_OF_LIFE_III};
    for(int i=0; i<3; i++){
        if(item.type == 4){
            return 1;
        }
    }
    return 0;
}
// j'effectue la recherche uniquement pour les armes et les armures car elles sont limités
// je recupère mon inventaire via le pointeur liste et je regarde si j'en est bien moins de 3 à chaque tape, dans le main, une condition
// à effectuer dans le cas où on aurait 4 armes ( un printf pour lui dire qu'on a déjà trop d'armes ? )
/*int getArmure(Player* player1){
    int item = 0;
    for(int i=0;i < LENGTH;i++){
        item = isArmor(player1->inventory[i]);
        //printf(" j ai ca : %d\n", item);
        if(item == 1){
            return 1;
        }
    }
    return 0;
}*/

// même chose pour un armure ( max 1)

/*int nbItem(Item item, int* inventory){// l'inventaire
    int counter = 0;
    for(int i=0; i < LENGTH;i++){
        if(item == Nextcase){
            counter++;
        }
    }
    return counter;
}*/