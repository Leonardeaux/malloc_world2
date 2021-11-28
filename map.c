#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "utils.h"
#include "monster.h"
#include "perlin_noise.h"

/*
 * -2 = portail zone 2 -> 3
 * -3 = portail zone 1 -> 2
 * -1 = mur
 *  0 = libre
 *  1 = joueur
 *  2 = pnj
 *  3 = plante zone 1 (>3)
 *  4 = rocher zone 1 (>3)
 *  5 = bois zone 1 (>3)
 *  6 = plante zone 2 (>3)
 *  7 = rocher zone 2 (>3)
 *  8 = bois zone 2 (>3)
 *  9 = plante zone 3 (>3)
 * 10 = rocher zone 3 (>3)
 * 11 = bois zone 3 (>3)
 */

/***
 * Fonction permettant la création d'un tableau à deux dimensions qui fait office de map
 * @param side côté de la map
 * @return Un tableau à triple dimension qui représente les maps du jeu
 */
int*** create_maps(int side){

    int*** map = malloc_map(side);

    do{

        float freq = 0.2f;
        short depth = 15;
        int seed = -1;
        float noise;
        short plant;
        short rock;
        short wood;

        seed++;

        printf("Creation de la map...\n");

        /* Génération des cases avec l'algorithme du bruit de Perlin */
        for(int i = 0; i < 3; i++){
            if(i == 0){
                plant = PLANT_1;
                rock = ROCK_1;
                wood = WOOD_1;
            } else if(i == 1){
                plant = PLANT_2;
                rock = ROCK_2;
                wood = WOOD_2;
            } else{
                plant = PLANT_3;
                rock = ROCK_3;
                wood = WOOD_3;
            }
            for(int x = 0; x < side; x++){
                for(int y = 0; y < side; y++){
                    noise = perlin2d(x, y, freq, depth, seed);
                    if(noise < 0.2){
                        map[i][x][y] = -1;
                    } else if(noise > 0.3 && noise < 0.4){
                        map[i][x][y] = plant;
                    } else if(noise > 0.55 && noise < 0.6){
                        map[i][x][y] = rock;
                    } else if(noise > 0.65 && noise < 0.7){
                        map[i][x][y] = wood;
                    } else{
                        map[i][x][y] = 0;
                    }
                }
            }
        }

        generate_portals(map, side);
        generate_monsters(map, side);
        generate_boss(map, side);


    } while(!verif_map(map, side));

    return map;
}

/***
 * Fonction qui permet l'allocation mémoire d'un tableau à deux dimension qui fait office de map
 * @param side côté de la map
 * @return Un tableau à double dimension dynamique
 */
int*** malloc_map(int side){

    /* Allocation de la mémoire pour la map */
    int*** map = malloc(sizeof(int**) * 3);
    if(map == NULL){
        exit_and_write_error("Erreur d'allocation mémoire pour la map");
    }

    for(int x = 0; x < 3; x++){
        map[x] = malloc(sizeof(int*) * side);
        for(int i = 0; i < side; i++){
            map[x][i] = malloc(sizeof(int) * side);
        }
    }

    return map;
}

/***
 * Fonction permettant la génération du pnj sur la map et des portails pour naviguer de zone en zone
 * @param map map passé en paramêtre
 * @param side côté de la map
 * @param id_zone numéro de la zone
 */
void generate_portals(int*** map, int side){

    srand(time(NULL ));

    int x_pnj = rand() % (side);
    int y_pnj = rand() % (side);
    int x_portal = rand() % (side);
    int y_portal = rand() % (side);

    for(int i = 0; i < 3; i++){
        map[i][x_pnj][y_pnj] = 2;
        square_access(map[i], side, x_pnj, y_pnj);

        if(i == 0){
            map[i][x_portal][y_portal] = PORTAL_1_2;
        } else if(i == 1){
            map[i][x_portal][y_portal] = PORTAL_2_3;

            int x_portal2;
            int y_portal2;

            do{
                x_portal2 = rand() % (side);
                y_portal2 = rand() % (side);
            } while(x_portal2 == x_portal && y_portal2 == y_portal);

            square_access(map[i], side, x_portal2, y_portal2);
            map[i][x_portal2][y_portal2] = PORTAL_1_2;
        } else {
            map[i][x_portal][y_portal] = PORTAL_2_3;
        }

        square_access(map[i], side, x_portal, y_portal);
    }

}

void generate_monsters(int*** map , int side){
    srand(time(NULL ));

    int x_monster;
    int y_monster;
    int monster;

    for(int i = 0; i < 3; i++){
        if(i == 0){
            for(monster = PIOU; monster <= BOUFTOU; monster++){
                do{
                    x_monster = rand() % (side);
                    y_monster = rand() % (side);

                } while(map[i][x_monster][y_monster] != 0);

                map[i][x_monster][y_monster] = monster;
            }
        } else if(i == 1){
            for(monster = CRAQUELEUR; monster <= POOLAY; monster++){
                do{
                    x_monster = rand() % (side);
                    y_monster = rand() % (side);

                } while(map[i][x_monster][y_monster] != 0);

                map[i][x_monster][y_monster] = monster;
            }
        } else {
            for(monster = BOUFMOUTH; monster <= APERIGLOURS; monster++){
                do{
                    x_monster = rand() % (side);
                    y_monster = rand() % (side);

                } while(map[i][x_monster][y_monster] != 0);

                map[i][x_monster][y_monster] = monster;
            }
        }
    }
}

void generate_boss(int*** map , int side){
    srand(time(NULL ));

    int x_boos;
    int y_boos;

    do{
        x_boos = rand() % (side);
        y_boos = rand() % (side);

    } while(map[2][x_boos][y_boos] != 0);

    map[2][x_boos][y_boos] = COMTE_HAREBOURG;
}

/***
 * Fonction permettant la vérification de la map, si elle répond bien aux règles demandées
 * @param map map passé en paramêtre
 * @param side côté de la map
 * @return 0 si la map ne respecte pas les règles, 1 si elle respecte
 */
int verif_map(int*** map, int side){
    int plant_cpt = 0;
    int rock_cpt = 0;
    int wood_cpt = 0;

    for(int x = 0; x < 3; x++) {
        for (int i = 0; i < side; i++) {
            for (int j = 0; j < side; j++) {
                if (map[x][i][j] == 3 || map[x][i][j] == 6 || map[x][i][j] == 9) {
                    plant_cpt++;
                } else if (map[x][i][j] == 4 || map[x][i][j] == 7 || map[x][i][j] == 10) {
                    rock_cpt++;
                } else if (map[x][i][j] == 5 || map[x][i][j] == 8 || map[x][i][j] == 11) {
                    wood_cpt++;
                }
            }
        }
    }

    if(plant_cpt >= MIN_PLANT && rock_cpt >= MIN_ROCK && wood_cpt >= MIN_WOOD){
        return 1;
    } else {
        return 0;
    }
}

/***
 * Rend accessible les cases autour d'une coordonnée
 * @param map map passé en paramêtre
 * @param side côté de la map
 * @param x coordonnée x
 * @param y coordonnée y
 */
void square_access(int** map, int side, int x, int y){
    if(x < side - 1){
        map[x + 1][y] = 0;
    }
    if(x > 0){
        map[x - 1][y] = 0;
    }
    if(y < side - 1){
        map[x][y + 1] = 0;
    }
    if(y > 0){
        map[x][y - 1] = 0;
    }
}

/***
 * Affiche la map
 * @param map map passé en paramêtre
 * @param side côté de la map
 */
void print_map(int*** map, int side){

    for(int x = 0; x < 3; x++){
        for(int j = 0; j < side; j++){
            printf("|");
            for(int i = 0; i < side; i++){
                if(map[x][i][j] < 0 || map[x][i][j] > 9){
                    printf("%d |", map[x][i][j]);
                } else {
                    printf(" %d |", map[x][i][j]);
                }
            }
            printf("\n");
        }
        printf("\n---------------------------------\n");
    }
}

void print_one_map(int** map, int side){

    for(int j = 0; j < side; j++){
        printf("|");
        for(int i = 0; i < side; i++){
            if(map[i][j] < 0 || map[i][j] > 9){
                printf("%d |", map[i][j]);
            } else {
                printf(" %d |", map[i][j]);
            }
        }
        printf("\n");
    }
}

/***
 * Libère la mémoire de la map
 * @param map map passé en paramêtre
 * @param side côté de la map
 */
void free_map(int*** map, int side){
    for(int x = 0; x < 3; x++){
        for(int i = 0; i < side; i++){
            free(map[x][i]);
        }
        free(map[x]);
    }

    free(map);
}

/***
 * Vérifie que la case suivant une direction est accessible
 * @param map map passé en paramêtre
 * @param side côté de la map
 * @param x coordonnée x
 * @param y coordonnée y
 * @param direction direction dans laquelle le joueur veut se déplacer
 * @return
 */
int check_valid_case(int** map, int side, int x, int y, char direction){
    switch (direction) {
        case 'u':
            if(y > 0){
                if(map[x][y - 1] != IMPOSSIBLE){
                    return 1;
                }
            }
            break;

        case 'r':
            if(x < side - 1){
                if(map[x + 1][y] != IMPOSSIBLE){
                    return 1;
                }
            }
            break;

        case 'd':
            if(y < side - 1){
                if(map[x][y + 1] != IMPOSSIBLE){
                    return 1;
                }
            }
            break;

        case 'l':
            if(x > 0){
                if(map[x - 1][y] != IMPOSSIBLE){
                    return 1;
                }
            }
            break;

        default:
            break;
    }

    return 0;
}

int* return_first_free_case(int** map, int side, int a_case){
    int* coords = malloc(sizeof(int) * 2);
    if(coords == NULL){
        exit_and_write_error("Erreur d'allocation mémoire lors du tableau de resultat de la fonction return_first_free_case");
    }

    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            if(map[i][j] == a_case){
                if(j > 0 && map[i][j - 1] == 0){
                    coords[0] = i;
                    coords[1] = j - 1;
                    return coords;
                } else if(i < side - 1 && map[i + 1][j] == 0){
                    coords[0] = i + 1;
                    coords[1] = j;
                    return coords;
                } else if(j < side - 1 && map[i][j + 1] == 0){
                    coords[0] = i;
                    coords[1] = j + 1;
                    return coords;
                } else {
                    coords[0] = i - 1;
                    coords[1] = j;
                    return coords;
                }
            }
        }
    }
    coords[0] = -1;
    coords[1] = -1;

    return coords;
}