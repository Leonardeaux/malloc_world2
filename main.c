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
