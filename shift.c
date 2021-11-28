#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "map.h"
#include "shift.h"
#include "player.h"
#include "coffre.h"
#include "utils.h"
#include "monster.h"
#include "fight.h"
#include "saving.h"

void print_menu(int*** map, int side, Player* player){
    char* response = malloc(sizeof(char) * 1000);
    if(map == NULL){
        exit_and_write_error("Erreur d'allocation mémoire pour la reponse de print_menu");
    }
    char directions[4] = {'u', 'r', 'd', 'l'};
    char directions_label[4][20] = {
            "En haut",
            "A droite",
            "En bas",
            "A gauche"
    };

    for(int i = 0; i < 4; i++){
        sprintf(response, "%s : %s \n", directions_label[i], case_forward_for_menu(map, side, player, directions[i]));

        printf("%s", response);
    }

    free(response);
}

void shifting_process(int*** map, int side, Player* player){
    int stop = 0;
    char direction;

    do{
        print_one_map(map[player->actual_map], side);
        print_player(player);
        print_inventory(player);
        print_menu(map, side, player);

        printf("\nDans quelle direction voulez-vous aller ? (Tapez 0 pour quitter)\n");
        direction = getchar();

        switch (direction) {
        case 'u': case 'r': case 'd': case 'l':
                printf("%s", case_forward(map, side, player, direction));
                break;

            case '0':
                stop = 1;
                printf("Vous venez de quitter le deplacement");
                break;

            default:
                printf("\nLa direction que vous avez rentre n'est pas correct.\n");
                break;
        }
        if(player->hp <= 0){
            stop = 1;
        }

        fflush(stdin);
    } while(stop == 0);
}

char* case_forward(int*** map, int side, Player* player, char direction){
    if(check_valid_case(map[player->actual_map], side, player->coord_x, player->coord_y, direction)){
        int process_return;
        int new_x;
        int new_y;

        switch (direction) {
            case 'u':
                new_x = player->coord_x;
                new_y = player->coord_y - 1;
                break;

            case 'r':
                new_x = player->coord_x + 1;
                new_y = player->coord_y;
                break;

            case 'd':
                new_x = player->coord_x;
                new_y = player->coord_y + 1;
                break;

            case 'l':
                new_x = player->coord_x - 1;
                new_y = player->coord_y;
                break;

            default:
                return "Direction choisi invalide\n";
                break;
        }

        process_return = case_process(map, side, map[player->actual_map][new_x][new_y], player);

        if(process_return == 1){
            shift_player(map[player->actual_map], player, new_x, new_y);
            return "Deplacement effectue\n";

        } else if(process_return == -1){
            return "Inventaire pleins\n";

        } else if(process_return == -2){
            return "Vous n'avez pas l'outil ou la durabilite pour recolter cette ressource\n";

        } else if(process_return == 4){
            return "Vous n'avez pas le niveau pour vous teleporter\n";

        } else if(process_return == 5){
            return "Teleportation\n";
        } else if(process_return == 6){
            shift_player(map[player->actual_map], player, new_x, new_y);
            return "Vous avez vaincu le monstre\n";
        } else if(process_return == 7){
            return "Vous etes decede\n";
        } else if(process_return == 8){
            return "\n";
        } else if(process_return == 9){
            return "Vous avez pris la fuite\n";
        } else if(process_return == -10){
            return "Erreur ???\n";
        }

    } else {
        return "Deplacement impossible dans cette direction\n";
    }
}

char* case_forward_for_menu(int*** map, int side, Player* player, char direction){
    if(check_valid_case(map[player->actual_map], side, player->coord_x, player->coord_y, direction)){
        switch (direction) {
            case 'u':
                return case_return(map[player->actual_map][player->coord_x][player->coord_y - 1], player);
                break;

            case 'r':
                return case_return(map[player->actual_map][player->coord_x + 1][player->coord_y], player);
                break;

            case 'd':
                return case_return(map[player->actual_map][player->coord_x][player->coord_y + 1], player);
                break;

            case 'l':
                return case_return(map[player->actual_map][player->coord_x - 1][player->coord_y], player);
                break;

            default:
                break;
        }
    }

    return "Deplacement impossible dans cette direction";
}

int case_process(int*** map, int side, int a_case, Player *player) {

    if(a_case == OPEN){
        return 1;

    } else if(a_case == NPC){
        PNJmenu(player);
        return 8;

    } else if(a_case >= PLANT_1 && a_case <= WOOD_3){
        srand(time(NULL ));

        int quantity = rand() % 4 + 1;
        int tool_index = can_recolt_resource(a_case, player);

        if(tool_index != -1){
            if(recolt_resource_process(entity_bitmap[a_case], quantity, player)){
                tools_management(a_case, tool_index, player);
                return 1;
            } else {
                return -1;
            }
        } else{
            return -2;
        }

    } else if(a_case > WOOD_3 && a_case <= END_BOSS){

        Monster* current_monster = initialize_monster(a_case);
        int fight = open_fight(player, current_monster);

        if(fight == 1){
            return 6;
        } else if(fight == -1){
            return 7;
        } else if(fight == 3){
            return 9;
        }
    } else if(a_case == PORTAL_1_2 || a_case == PORTAL_2_3){
        int teleportation = can_teleport_player(map, side, player, a_case);
        if(teleportation == 0){
            return 4;
        } else{
            return 5;
        }
    }

    return -10;
}

char* case_return(int a_case, Player* player){
    if(a_case == OPEN){
        return "Vous pouvez vous deplacer librement dans cette direction";

    } else if(a_case == NPC){
        return "Vous pouvez parler au PNJ";

    } else if(a_case >= PLANT_1 && a_case <= WOOD_3){
        return "Vous pouvez recolter une ressource";

    } else if(a_case > WOOD_3 && a_case <= END_BOSS){
        return "Vous pouvez vous battre contre un monstre";

    } else if(a_case == PORTAL_1_2 || a_case == PORTAL_2_3){
        return "Vous pouvez vous deplacer dans un portail";
    }

    return "Bizarre";
}

void shift_player(int** map, Player* player, int new_x, int new_y){
    map[player->coord_x][player->coord_y] = 0;
    player->coord_x = new_x;
    player->coord_y = new_y;
    map[player->coord_x][player->coord_y] = 1;
}