#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "shift.h"
#include "player.h"
#include "utils.h"

void print_menu(int*** map, int side, Player* player){
    char* response = malloc(sizeof(char) * 1000);
    if(map == NULL){
        exit_and_write_error("Erreur d'allocation mémoire pour la reponse du menu");
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

}

void move_player(int*** map, int side, Player* player){
    int stop = 0;
    char direction;

    do{
        printf("\nDans quelle direction voulez-vous aller ?\n");
        direction = getchar();
        printf("\nla direction est : %c\n", direction);

        switch (direction) {
            case 'u':
                printf("\nLa direction est correct.\n");

                break;

            case 'r':
                printf("\nLa direction est correct.\n");
                break;

            case 'd':
                printf("\nLa direction est correct.\n");
                break;

            case 'l':
                printf("\nLa direction est correct.\n");
                break;

            default:
                printf("\nLa direction que vous avez rentre n'est pas correct.\n");
                break;
        }

        fflush(stdin);
    } while(stop == 0);
}

void case_forward(int*** map, int side, Player* player, char direction){
    if(check_valid_case(map[player->actual_map], side, player->coord_x, player->coord_y, direction)){
        switch (direction) {
            case 'u':
                if(case_process(map[player->actual_map][player->coord_x][player->coord_y - 1], player)){
                    player->coord_y -= 1;
                }
                break;

            case 'r':
                if(case_process(map[player->actual_map][player->coord_x + 1][player->coord_y], player)){
                    player->coord_y += 1;
                }
                break;

            case 'd':
                if(case_process(map[player->actual_map][player->coord_x][player->coord_y + 1], player)){
                    player->coord_y += 1;
                }
                break;

            case 'l':
                if(case_process(map[player->actual_map][player->coord_x - 1][player->coord_y], player)){
                    player->coord_y -= 1;
                }
                break;

            default:
                break;
        }   
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
    } else {
        return "Deplacement impossible dans cette direction";
    }
}

int case_process(int a_case, Player* player){
    if(a_case == OPEN){
        return 1;
    } else if(a_case == NPC){
        //open npc

    } else if(a_case >= PLANT_1 && a_case <= WOOD_3){
        //collect resource

    } else if(a_case > WOOD_3 && a_case <= END_BOSS){
        //open fight

    } else if(a_case == PORTAL_1_2 || a_case == PORTAL_2_3){
        //enter portal

    }
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