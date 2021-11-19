#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "player.h"
#include "shift.h"

#define SIDE 10

int main(int argc, const char **argv) {
    int*** map = create_maps(SIDE);

    printf("\n");

    Player* APlayer = create_player(map, SIDE, "Enzo");

    printf("\n%d %d\n", APlayer->coord_x, APlayer->coord_y);
    printf("\n%d\n", map[0][APlayer->coord_x][APlayer->coord_y]);
    printf("\ntype item 1 : %s\n", APlayer->inventory[0].weapon.name);
//    printf("\ntype item 2 : %s\n", APlayer->inventory[1].tool.name);
//    printf("\ntype item 3 : %s\n", APlayer->inventory[2].tool.name);
//    printf("\ntype item 4 : %s\n\n", APlayer->inventory[3].tool.name);
//    printf("\n%d %d\n", APlayer->hp, APlayer->level);

    print_map(map, SIDE);

    print_menu(map, SIDE, APlayer);
//    move_player(map, SIDE, APlayer);

    free_map(map, SIDE);
    free(APlayer);

    return 0;
}
