#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "player.h"
#include "craft.h"
#include "shift.h"

#define SIDE 10

int main(int argc, const char **argv) {
    int*** map = create_maps(SIDE);

    printf("\n");

    Player* APlayer = create_player(map, SIDE, "Enzo");
    initialize(APlayer);// je met toutes les cases à 0
    APlayer->inventory[2].type = 3;
    APlayer->inventory[2].resource.id = FIR;
    APlayer->inventory[2].resource.quantity = 8;

    APlayer->inventory[5].type = 3;
    APlayer->inventory[5].resource.id = ROCK;
    APlayer->inventory[5].resource.quantity = 12;

    APlayer->inventory[4].type = 3;
    APlayer->inventory[4].resource.id = BEECH;
    APlayer->inventory[4].resource.quantity = 18;

    APlayer->inventory[8].type = 3;
    APlayer->inventory[8].resource.id = IRON;
    APlayer->inventory[8].resource.quantity = 15;

    for(int i = 0; i < 10; i++){
        printf("j'ai ce type : %d ", APlayer->inventory[i].type);
        printf("et cette ressource : %d ", APlayer->inventory[i].resource.id);
        printf("et cette quantite de ressource: %d\n", APlayer->inventory[i].resource.quantity);
    }

    canCreateWOODENSWORD(1, APlayer);

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
