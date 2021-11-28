#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "player.h"
#include "utils.h"
#include "craft.h"

//void create_weapon(int index, Player *player, int id, char* name, int damage, int max_durability, int actual_durability){
//    player->inventory[index].type = WEAPON;
//    Weapon* AWeapon = &player->inventory[index].weapon;
//    AWeapon->id = id;
//    AWeapon->damage = damage;
//    AWeapon->max_durability = max_durability;
//    AWeapon->actual_durability = actual_durability;
//    strcpy(AWeapon->name, name);
//}

void delete_from_inventory(int index, Player *player){
    player->inventory[index].type = 0;
}

int canCreateWOODENSWORD(int id, Player *player){
    int i, j, damage;
    int max_durability, actual_durability;
    char *name;
    for(i = 0; i < 10; i++) {
        switch (id) {
            case 1:
                if (player->inventory[i].type == 3 && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 3) {
                    player->inventory[i].resource.quantity -= 3;
                    name = "WOODEN_SWORD";
                    damage = 1, max_durability = 10, actual_durability = 8;
                }
                break;
            case 8:
                if (player->inventory[i].type == 3 && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == ROCK && player->inventory[j].resource.quantity >= 3){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 3;
                            name = "STONE_SWORD";
                            damage = 2, max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 19:
                if (player->inventory[i].type == 3 && player->inventory[i].resource.id == BEECH && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == IRON && player->inventory[j].resource.quantity >= 4){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 4;
                            name = "IRON_SWORD";
                            damage = 5, max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 30:
                if (player->inventory[i].type == 3 && player->inventory[i].resource.id == OAK && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == DIAMOND && player->inventory[j].resource.quantity >= 5){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 5;
                            name = "DIAMOND_SWORD";
                            damage = 10, max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 9:
                if (player->inventory[i].type == 3 && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 3){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == ROCK && player->inventory[j].resource.quantity >= 4){
                            player->inventory[i].resource.quantity -= 3;
                            player->inventory[j].resource.quantity -= 4;
                            name = "STONE_SPEAR";
                            damage = 3, max_durability = 8, actual_durability = 8;
                        }
                    }
                }
                break;
            case 20:
                if (player->inventory[i].type == 3 && player->inventory[i].resource.id == BEECH && player->inventory[i].resource.quantity >= 3){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == IRON && player->inventory[j].resource.quantity >= 5){
                            player->inventory[i].resource.quantity -= 3;
                            player->inventory[j].resource.quantity -= 5;
                            name = "IRON_SPEAR";
                            damage = 7, max_durability = 8, actual_durability = 8;
                        }
                    }
                }
                break;
            case 31:
                if (player->inventory[i].type == 3 && player->inventory[i].resource.id == OAK && player->inventory[i].resource.quantity >= 3){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == DIAMOND && player->inventory[j].resource.quantity >= 6){
                            player->inventory[i].resource.quantity -= 3;
                            player->inventory[j].resource.quantity -= 6;
                            name = "DIAMOND_SPEAR";
                            damage = 15, max_durability = 8, actual_durability = 8;
                        }
                    }
                }
                break;
            case 10:
                if (player->inventory[i].type == 3 && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == ROCK && player->inventory[j].resource.quantity >= 6){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 6;
                            name = "STONE_HAMMER";
                            damage = 4, max_durability = 5, actual_durability = 5;
                        }
                    }
                }
                break;
            case 21:
                if (player->inventory[i].type == 3 && player->inventory[i].resource.id == BEECH && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == IRON && player->inventory[j].resource.quantity >= 7){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 7;
                            name = "IRON_HAMMER";
                            damage = 10, max_durability = 5, actual_durability = 5;
                        }
                    }
                }
                break;
            case 32:
                if (player->inventory[i].type == 3 && player->inventory[i].resource.id == OAK && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == DIAMOND && player->inventory[j].resource.quantity >= 8){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 8;
                            name = "DIAMOND_HAMMER";
                            damage = 20, max_durability = 5, actual_durability = 5;
                        }
                    }
                }
                break;
            default:
                printf("mauvaise id");
                break;
        }
    }
    int index = 0;
    while (player->inventory[index].type != 0) {
        index++;
    }
    create_weapon(index, player, id, name, damage, max_durability, actual_durability);
    return 0;
}

//void create_armor(int index, Player *player, int id){
//    player->inventory[index].type = ARMOR;
//    Armor *armor = &player->inventory[index].armor;
//    armor->id = id;
//}

int canCreateARMOR(int id, Player *player){
    int i;
    double damage_reduction;
    for(i = 0; i < 10; i++){
        switch (id) {
            case 11:
                if (player->inventory[i].type == 5 && player->inventory[i].resource.id == ROCK && player->inventory[i].resource.quantity >= 10) {
                    player->inventory[i].resource.quantity -= 10;
                    damage_reduction = 0.10;
                }
                break;
            case 22:
                if (player->inventory[i].type == 5 && player->inventory[i].resource.id == IRON && player->inventory[i].resource.quantity >= 12) {
                    player->inventory[i].resource.quantity -= 12;
                    damage_reduction = 0.20;
                }
                break;
            case 33:
                if (player->inventory[i].type == 5 && player->inventory[i].resource.id == DIAMOND && player->inventory[i].resource.quantity >= 16) {
                    player->inventory[i].resource.quantity -= 16;
                    damage_reduction = 0.40;
                }
                break;
            default:
                printf("mauvaise id");
                break;
        }
    }
    create_armor(i, player, id, id_items_name[id], damage_reduction);
}

//void create_tool(int index, Player *player, int id, char* name, int max_durability, int actual_durability){
//    player->inventory[index].type = TOOL;
//    Tool* tool = &player->inventory[index].tool;
//    tool->id = id;
//    tool->max_durability = max_durability;
//    tool->actual_durability = actual_durability;
//    strcpy(tool->name, name);
//}

int canCreateTOOL(int id, Player *player){
    int i, j;
    int max_durability, actual_durability;
    char *name;
    for(i = 0; i < 10; i++) {
        switch (id) {
            case 2:
                if (player->inventory[i].type == 2 && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 3) {
                    player->inventory[i].resource.quantity -= 3;
                    name = "WOODEN_PICKAXE";
                    max_durability = 10, actual_durability = 10;
                }
                break;
            case 12:
                if (player->inventory[i].type == 2 && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 2 && player->inventory[j].resource.id == ROCK && player->inventory[j].resource.quantity >= 3){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 3;
                            name = "STONE_PICKAXE";
                            max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 23:
                if (player->inventory[i].type == 2 && player->inventory[i].resource.id == BEECH && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 2 && player->inventory[j].resource.id == IRON && player->inventory[j].resource.quantity >= 4){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 4;
                            name = "IRON_PICKAXE";
                            max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 4:
                if (player->inventory[i].type == 2 && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 3) {
                    player->inventory[i].resource.quantity -= 3;
                    name = "WOODEN_AXE";
                    max_durability = 10, actual_durability = 10;
                }
                break;
            case 14:
                if (player->inventory[i].type == 2 && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 2 && player->inventory[j].resource.id == ROCK && player->inventory[j].resource.quantity >= 3){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 3;
                            name = "STONE_AXE";
                            max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 25:
                if (player->inventory[i].type == 2 && player->inventory[i].resource.id == BEECH && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 2 && player->inventory[j].resource.id == IRON && player->inventory[j].resource.quantity >= 4){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 4;
                            name = "IRON_AXE";
                            max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 3:
                if (player->inventory[i].type == 2 && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 3) {
                    player->inventory[i].resource.quantity -= 3;
                    name = "WOODEN_BILLHOOK";
                    max_durability = 10, actual_durability = 10;
                }
                break;
            case 13:
                if (player->inventory[i].type == 2 && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 2 && player->inventory[j].resource.id == ROCK && player->inventory[j].resource.quantity >= 3){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 3;
                            name = "STONE_BILLHOOK";
                            max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 24:
                if (player->inventory[i].type == 2 && player->inventory[i].resource.id == BEECH && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 2 && player->inventory[j].resource.id == IRON && player->inventory[j].resource.quantity >= 4){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 4;
                            name = "IRON_BILLHOOK";
                            max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            default:
                printf("mauvaise id");
                break;
        }
    }
    create_tool(i, player, id, name, max_durability, actual_durability);
    return 0;
}

int canCreateCONSUMABLE(int id, Player *player){
    int i;
    for(i = 0; i < 10; i++){
        switch (id) {
            case 7:
                if (player->inventory[i].type == 4 && player->inventory[i].resource.id == GRASS && player->inventory[i].resource.quantity >= 2) {
                    player->inventory[i].resource.quantity -= 2;
                }
                break;
            case 18:
                if (player->inventory[i].type == 4 && player->inventory[i].resource.id == LAVENDER && player->inventory[i].resource.quantity >= 2) {
                    player->inventory[i].resource.quantity -= 2;
                }
                break;
            case 29:
                if (player->inventory[i].type == 4 && player->inventory[i].resource.id == HEMP && player->inventory[i].resource.quantity >= 2) {
                    player->inventory[i].resource.quantity -= 2;
                }
                break;
            default:
                printf("mauvaise id");
                break;
        }
    }
//    create_armor(i, player, id);
}

//void create_Consumable(int index, Player *player, int id){
//    player->inventory[index].type = CONSUMABLE;
//    Consumable *consumable = &player->inventory[index].consumable;
//    consumable->id = id;
//}