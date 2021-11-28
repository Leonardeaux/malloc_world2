#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "player.h"
#include "craft.h"
#include "shift.h"
#include "craft.h"
#include "coffre.h"

#define SIDE 10

int main(int argc, const char **argv) {
    int*** map = create_maps(SIDE);
    char *name, *name2, *name3, *name4, *name5, *name6, name7, name8, name9;

    printf("\n");

    Player* APlayer = create_player(map, SIDE, "Enzo");
    initialize_player(APlayer);// je met toutes les cases à 0

    APlayer->inventory[2].type = 3;
    APlayer->inventory[2].resource.id = FIR;
    APlayer->inventory[2].resource.quantity = 8;
    name = "FIR";
    strcpy(APlayer->inventory[2].resource.name, name);

    APlayer->inventory[5].type = 3;
    APlayer->inventory[5].resource.id = ROCK;
    APlayer->inventory[5].resource.quantity = 12;
    name2 = "ROCK";
    strcpy(APlayer->inventory[5].resource.name, name2);

    APlayer->inventory[4].type = 3;
    APlayer->inventory[4].resource.id = BEECH;
    APlayer->inventory[4].resource.quantity = 18;
    name3 = "BEECH";
    strcpy(APlayer->inventory[4].resource.name, name3);

    APlayer->inventory[8].type = 3;
    APlayer->inventory[8].resource.id = IRON;
    APlayer->inventory[8].resource.quantity = 15;
    name4 = "IRON";
    strcpy(APlayer->inventory[8].resource.name, name4);

    APlayer->inventory[9].type = 3;
    APlayer->inventory[9].resource.id = DIAMOND;
    APlayer->inventory[9].resource.quantity = 20;
    name5 = "DIAMOND";
    strcpy(APlayer->inventory[9].resource.name, name5);

    APlayer->inventory[7].type = 3;
    APlayer->inventory[7].resource.id = LAVENDER;
    APlayer->inventory[7].resource.quantity = 19;
    name6 = "LAVENDER";
    strcpy(APlayer->inventory[7].resource.name, name6);


    for(int i = 0; i < 10; i++){
        printf("j'ai ce type : %d ", APlayer->inventory[i].type);
        printf("et cette ressource : %d ", APlayer->inventory[i].resource.id);
        printf("et cette quantite de ressource: %d\n", APlayer->inventory[i].resource.quantity);
    }

    PNJmenu(APlayer);


    printf("\n et apres creation de l arme: contenu: \n");

    for(int i = 0; i < 10; i++){
        printf("j'ai ce type : %d ", APlayer->inventory[i].type);
        printf("et cette ressource : %d ", APlayer->inventory[i].resource.id);
        printf("et cette quantite de ressource: %d\n", APlayer->inventory[i].resource.quantity);
    }

    printf("\n%d %d\n", APlayer->coord_x, APlayer->coord_y);
    printf("\n%d\n", map[0][APlayer->coord_x][APlayer->coord_y]);
//    printf("\n%d %d\n", APlayer->hp, APlayer->level);

    print_map(map, SIDE);

    print_menu(map, SIDE, APlayer);
//    move_player(map, SIDE, APlayer);

    free_map(map, SIDE);
    free(APlayer);

    return 0;
}
