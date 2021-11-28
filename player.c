#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "player.h"
#include "utils.h"

Player* create_player(int*** map, int side, char* username){

    Player* APlayer = malloc(sizeof(Player));
    if(APlayer == NULL){
        exit_and_write_error("Erreur d'allocation mémoire dans la fonction de la création du joueur");
    }

    APlayer->xp = 1;
    APlayer->next_xp = 100;
    APlayer->level = 8;
    APlayer->hp_max = 100;
    APlayer->hp = 40;
    APlayer->actual_map = 0;
    strcpy(APlayer->username, username);
    initialize_player(APlayer);
    create_weapon(0, APlayer, WOODEN_SWORD, id_items_name[WOODEN_SWORD], 10, 100, 100);
    create_tool(1, APlayer, WOODEN_AXE, id_items_name[WOODEN_AXE], 100, 10);
    create_tool(2, APlayer, STONE_BILLHOOK, id_items_name[STONE_BILLHOOK], 100, 100);
    create_tool(3, APlayer, WOODEN_PICKAXE, id_items_name[WOODEN_PICKAXE], 100, 100);
//    create_weapon(4, APlayer, STONE_HAMMER, id_items_name[STONE_HAMMER], 10, 100, 100);
//    create_weapon(5, APlayer, DIAMOND_SPEAR, id_items_name[DIAMOND_SPEAR], 10, 100, 100);
    create_consumable(6, APlayer, POTION_OF_LIFE_I, id_items_name[POTION_OF_LIFE_I], 50);
    create_consumable(7, APlayer, POTION_OF_LIFE_II, id_items_name[POTION_OF_LIFE_II], 100);
//    create_resource(4, APlayer, FIR, id_items_name[FIR], 20);
//    create_resource(5, APlayer, FIR, id_items_name[FIR], 20);
//    create_resource(6, APlayer, FIR, id_items_name[FIR], 20);
//    create_resource(7, APlayer, FIR, id_items_name[FIR], 20);
//    create_resource(8, APlayer, FIR, id_items_name[FIR], 20);
//    create_resource(9, APlayer, FIR, id_items_name[FIR], 17);

    spawn_player(APlayer, map[0], side);

    return APlayer;
}

void spawn_player(Player* player, int** map, int side){

    int i, j, x, y;

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

void initialize_player(Player *player){
    for(int i = 0; i < 10; i++){
        player->inventory[i].type = 0;
    }
}

int nb_free_space(Player *player){
    int nb_space = 0;

    for(int i = 0; i < 10; i++){
        if(player->inventory[i].type == 0)
            nb_space++;
    }
    return nb_space;
}

int locale_resource(int id_resource, Player *player){
    int index = -1;

    for(int i = 0; i < 10; i++){
        if(player->inventory[i].resource.id == id_resource){
            index = i;
        }
    }

    return index;
}

int locale_resource_with_quantity(int id_resource, Player *player, int quantity){
    for(int i = 0; i < 10; i++){
        if(player->inventory[i].resource.id == id_resource && player->inventory[i].resource.quantity <= (20 - quantity)){
            return i;
        }
    }

    return -1;
}

int locale_first_free_case(Player *player){
    for(int i = 0; i < 10; i++){
        if(player->inventory[i].type == 0){
            return i;
        }
    }

    return -1;
}

int can_recolt_resource(int id_entity, Player *player){
    int* valable_tools_tab = valable_tools(id_entity);
    int tool_index;


    for(int i = 0; i < 3; i++){
        if(valable_tools_tab[i] != 0){
            tool_index = tool_in_inventory(player, valable_tools_tab[i]);

            if(tool_index != -1){
                if(player->inventory[tool_index].tool.actual_durability >= (player->inventory[tool_index].tool.max_durability *
                                                                            entity_coeff(id_entity))){
                    free(valable_tools_tab);
//                    player->inventory[tool_index].tool.actual_durability -= (int)(player->inventory[tool_index].tool.max_durability * entity_coeff(id_entity));
                    return tool_index;
                }
            }
        }
    }
    free(valable_tools_tab);
    return -1;
}

void tools_management(int id_entity, int tool_index, Player *player){

    player->inventory[tool_index].tool.actual_durability -= (int)(player->inventory[tool_index].tool.max_durability * entity_coeff(id_entity));
}

int recolt_resource_process(int id_resource, int quantity, Player *player){
    int index_resource = locale_resource(id_resource, player);

//    printf("%d\n\n\n\n", index_resource);
//    printf("%d\n\n\n\n", quantity);
//    printf("---%d/%d---\n\n\n\n", (20 - player->inventory[index_resource].resource.quantity) >= quantity, (20 - player->inventory[index_resource].resource.quantity));

    if(index_resource != -1){ //Item trouvé

        if(player->inventory[index_resource].resource.quantity >= 20 && nb_free_space(player) <= 0) {
//            printf("01\n\n\n\n");
            return 0;   //Pas de place dans l'inventaire

        } else if((20 - player->inventory[index_resource].resource.quantity) >= quantity){
            player->inventory[index_resource].resource.quantity += quantity;
//            printf("1\n\n\n\n");
            return 1;   //La ressource est présente dans l'inventaire

        } else if(((20 - player->inventory[index_resource].resource.quantity) < quantity) && nb_free_space(player) >= 1){
            quantity -= 20 - player->inventory[index_resource].resource.quantity;
            player->inventory[index_resource].resource.quantity = 20;
            create_resource(locale_first_free_case(player), player, id_resource, player->inventory[index_resource].resource.name, quantity);
//            printf("2\n\n\n\n");
            return 2;   //La ressource est présente mais à l'index la quantité est supérieur au reste et il reste une place en plus dans l'inventaire

        } else if(((20 - player->inventory[index_resource].resource.quantity) < quantity) && nb_free_space(player) < 1) {
            player->inventory[index_resource].resource.quantity = 20;
//            printf("02\n\n\n\n");
            return 3;   //La ressource est présente mais à l'index la quantité est supérieur au reste et il ne reste pas de place suplémentaire
        }

    } else if(nb_free_space(player) >= 1){   //Item non trouvé mais place dans l'inventaire
        create_resource(locale_first_free_case(player), player, id_resource, id_items_name[id_resource], quantity);
//        printf("4\n\n\n\n");
        return 4;

    }
    //Item non trouvé mais pas de place dans l'inventaire
//    printf("03\n\n\n\n");
    return 0;
}

int can_teleport_player(int*** map, int side, Player* player, int portal_case){
    if(player->level < 3 && portal_case == PORTAL_1_2){
        return 0;

    } else if(player->level < 7 && portal_case == PORTAL_2_3){
        return 0;

    } else {

        if (portal_case == PORTAL_1_2 && player->actual_map == 0) {
            teleport_player(map, side, player, portal_case, 1);

        } else if(portal_case == PORTAL_2_3 && player->actual_map == 1){
            teleport_player(map, side, player, portal_case, 2);

        } else if(portal_case == PORTAL_1_2 && player->actual_map == 1){
            teleport_player(map, side, player, portal_case, 0);

        } else if(portal_case == PORTAL_2_3 && player->actual_map == 2){
            teleport_player(map, side, player, portal_case, 1);
        }

        return 1;
    }
}

void teleport_player(int*** map, int side, Player* player, int portal_case, int new_map){
    int *coords;

    map[player->actual_map][player->coord_x][player->coord_y] = 0;
    player->actual_map = new_map;
    coords = return_first_free_case(map[player->actual_map], side, portal_case);
    map[player->actual_map][coords[0]][coords[1]] = PLAYER;
    player->coord_x = coords[0];
    player->coord_y = coords[1];

    free(coords);
}

void create_weapon(int index, Player *player, int id, char* name, int damage, int max_durability, int actual_durability){
    player->inventory[index].type = WEAPON;
    Weapon* AWeapon = &player->inventory[index].weapon;

    AWeapon->id = id;
    AWeapon->damage = damage;
    AWeapon->max_durability = max_durability;
    AWeapon->actual_durability = actual_durability;
    strcpy(AWeapon->name, name);
}

void create_tool(int index, Player *player, int id, char* name, int max_durability, int actual_durability){
    player->inventory[index].type = TOOL;
    Tool* ATool = &player->inventory[index].tool;

    ATool->id = id;
    ATool->max_durability = max_durability;
    ATool->actual_durability = actual_durability;
    strcpy(ATool->name, name);
}

void create_resource(int index, Player *player, int id, char* name, int quantity){
    player->inventory[index].type = RESOURCE;
    Resource * AResource = &player->inventory[index].resource;

    AResource->id = id;
    AResource->quantity = quantity;
    strcpy(AResource->name, name);
}

void create_armor(int index, Player *player, int id, char* name, double damage_reduction){
    player->inventory[index].type = ARMOR;
    Armor * AArmor = &player->inventory[index].armor;

    AArmor->id = id;
    AArmor->damage_reduction = damage_reduction;
    strcpy(AArmor->name, name);
}

void create_consumable(int index, Player *player, int id, char* name, int hp_gain){
    player->inventory[index].type = CONSUMABLE;
    Consumable* AConsumable = &player->inventory[index].consumable;

    AConsumable->id = id;
    AConsumable->hp_gain = hp_gain;
    strcpy(AConsumable->name, name);
}

void print_player(Player* player){
    printf("\nJoueur %s :\n", player->username);
    printf("\thp : %d/%d\n", player->hp, player->hp_max);
    printf("\tlevel : %d\n", player->level);
    printf("\txp : %d/%d\n", player->xp, player->next_xp);
}

void print_inventory(Player* player){
    printf("\nInventaire de %s : \n", player->username);
    for(int i = 0; i < 10; i++){
        if(player->inventory[i].type == 0){
            printf("| Vide |\n");

        } else if(player->inventory[i].type == 1){
            printf("| %s x1 - %d/%d - %d |\n", player->inventory[i].weapon.name, player->inventory[i].weapon.actual_durability, player->inventory[i].weapon.max_durability, player->inventory[i].weapon.damage);
        } else if(player->inventory[i].type == 2){
            printf("| %s x1 - %d/%d |\n", player->inventory[i].tool.name, player->inventory[i].tool.actual_durability, player->inventory[i].tool.max_durability);
        } else if(player->inventory[i].type == 3){
            printf("| %s x%d |\n", player->inventory[i].resource.name, player->inventory[i].resource.quantity);
        } else if(player->inventory[i].type == 4){
            printf("| %s x1 |\n", player->inventory[i].consumable.name);
        } else {
            printf("| %s x1 |\n", player->inventory[i].armor.name);
        }
    }

    printf("\n");
}

int weapon_in_inventory(Player* player, int id_weapon){
    for(int i = 0; i < 10; i++){
        if(player->inventory[i].weapon.id == id_weapon){
            return i;
        }
    }

    return -1;
}

int tool_in_inventory(Player* player, int id_tool){
    for(int i = 0; i < 10; i++){
        if(player->inventory[i].tool.id == id_tool){
            return i;
        }
    }

    return -1;
}

int verif_tool_entity(int id_entity){

    if(id_entity == PLANT_1){
        return WOODEN_BILLHOOK;
    } else if(id_entity == PLANT_2){
        return STONE_BILLHOOK;
    } else if(id_entity == PLANT_3){
        return IRON_BILLHOOK;
    } else if(id_entity == ROCK_1){
        return WOODEN_PICKAXE;
    } else if(id_entity == ROCK_2){
        return STONE_PICKAXE;
    } else if(id_entity == ROCK_3){
        return IRON_PICKAXE;
    } else if(id_entity == WOOD_1){
        return WOODEN_AXE;
    } else if(id_entity == WOOD_2){
        return STONE_AXE;
    } else{
        return IRON_AXE;
    }
}

int entity_rank(int id_entity){
    if(id_entity == PLANT_1){
        return 1;
    } else if(id_entity == PLANT_2){
        return 2;
    } else if(id_entity == PLANT_3){
        return 3;
    } else if(id_entity == ROCK_1){
        return 1;
    } else if(id_entity == ROCK_2){
        return 2;
    } else if(id_entity == ROCK_3){
        return 3;
    } else if(id_entity == WOOD_1){
        return 1;
    } else if(id_entity == WOOD_2){
        return 2;
    } else{
        return 3;
    }
}

double entity_coeff(int id_entity){
    if(id_entity == PLANT_1){
        return 0.1;
    } else if(id_entity == PLANT_2){
        return 0.2;
    } else if(id_entity == PLANT_3){
        return 0.4;
    } else if(id_entity == ROCK_1){
        return 0.1;
    } else if(id_entity == ROCK_2){
        return 0.2;
    } else if(id_entity == ROCK_3){
        return 0.4;
    } else if(id_entity == WOOD_1){
        return 0.1;
    } else if(id_entity == WOOD_2){
        return 0.2;
    } else{
        return 0.4;
    }
}

int* valable_tools(int id_entity){
    int* result_tab = calloc(3, sizeof(int));
    if(result_tab == NULL){
        exit_and_write_error("Erreur d'allocation mémoire pour le tableau de resultat de la fonction valable_tools");
    }

    if(id_entity == PLANT_1){
        result_tab[0] = WOODEN_BILLHOOK;
        result_tab[1] = STONE_BILLHOOK;
        result_tab[2] = IRON_BILLHOOK;
    } else if(id_entity == PLANT_2){
        result_tab[0] = STONE_BILLHOOK;
        result_tab[1] = IRON_BILLHOOK;
    } else if(id_entity == PLANT_3){
        result_tab[0] = IRON_BILLHOOK;
    } else if(id_entity == ROCK_1){
        result_tab[0] = WOODEN_PICKAXE;
        result_tab[1] = STONE_PICKAXE;
        result_tab[2] = IRON_PICKAXE;
    } else if(id_entity == ROCK_2){
        result_tab[0] = STONE_PICKAXE;
        result_tab[1] = IRON_PICKAXE;
    } else if(id_entity == ROCK_3){
        result_tab[0] = IRON_PICKAXE;
    } else if(id_entity == WOOD_1){
        result_tab[0] = WOODEN_AXE;
        result_tab[1] = STONE_AXE;
        result_tab[2] = IRON_AXE;
    } else if(id_entity == WOOD_2){
        result_tab[0] = STONE_AXE;
        result_tab[1] = IRON_AXE;
    } else{
        result_tab[0] = IRON_AXE;
    }

    return result_tab;
}

int* weapons_in_inventory(Player* player){
    int* weapons = malloc(sizeof(int) * 255);
    if(weapons == NULL){
        exit_and_write_error("Erreur d'allocation mémoire dans la fonction de recupération des armes");
    }
    int cpt = 1;

    for(int i = 0; i < 10; i++){
        if(player->inventory[i].type == WEAPON && player->inventory[i].weapon.actual_durability > 0){
            weapons[cpt] = i;
            cpt++;
        }
    }

    if(cpt > 0){
        weapons[0] = cpt;
        return weapons;
    } else {
        return NULL;
    }
}

int* consumables_in_inventory(Player* player){
    int* consumable = malloc(sizeof(int) * 5);
    if(consumable == NULL){
        exit_and_write_error("Erreur d'allocation mémoire dans la fonction de recupération des consomables");
    }

    int cpt = 1;

    for(int i = 0; i < 10; i++){
        if(player->inventory[i].type == CONSUMABLE){
            consumable[cpt] = i;
            cpt++;
        }
    }

    if(cpt > 0){
        consumable[0] = cpt;
        return consumable;
    } else {
        return NULL;
    }
}

int armor_in_inventory(Player* player){
    for(int i = 0; i < 10; i++){
        if(player->inventory[i].type == ARMOR){
            return i;
        }
    }

    return -1;
}