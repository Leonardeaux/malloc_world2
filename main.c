#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "utils.h"
#include "player.h"
#include "shift.h"
#include "monster.h"
#include "fight.h"
#include "saving.h"

int main(int argc, const char **argv) {
    char username[255];

    printf("Bienvenue sur Malloc World !\n Veuillez entrer un nom de joueur : ");
    scanf("%s", &username);

    int*** map = create_maps(SIDE);

    Player* APlayer = create_player(map, SIDE, username);

//    if(check_file(concat(username, ".txt"))){
//        openfile(username, APlayer);
//        fflush(stdin);
//
//    }

    shifting_process(map, SIDE, APlayer);

    if(APlayer->hp > 0){
        savingmap(map, SIDE, APlayer);
        savingplayer(APlayer);
        savingstorage(APlayer);
    }

    free_map(map, SIDE);
    free(APlayer);

//    printf("\n%d %d\n", APlayer->coord_x, APlayer->coord_y);
//    printf("\n%d\n", map[0][APlayer->coord_x][APlayer->coord_y]);
//    printf("\ntype item 1 : %s\n", APlayer->inventory[0].weapon.name);
//    printf("\nnombre de place dans l'inventaire : %d\n", nb_free_space(APlayer));
//    printf("\ntype item 2 : %s\n", APlayer->inventory[1].tool.name);
//    printf("\ntype item 3 : %s\n", APlayer->inventory[2].tool.name);
//    printf("\ntype item 4 : %s\n\n", APlayer->inventory[3].tool.name);
//    printf("\n%d %d\n", APlayer->hp, APlayer->level);

//    print_map(map, SIDE);

//    print_menu(map, SIDE, APlayer);

//    Monster* current_monster = initialize_monster(12);
//    printf("\n%s\n", current_monster->name);
//    printf("\n%s\n",id_monster_name[12 - 11]);
//
//    int fight = open_fight(APlayer, current_monster);

    return 0;
}
