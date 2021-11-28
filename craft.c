//
// Created by jeffr on 20/11/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "player.h"
#include "utils.h"
#include "craft.h"

void create_weapon(int index, Player *player, int id, char* name, int damage, int max_durability, int actual_durability){
    int create = 0;
    for(int i = 0; i <= 9; i++){
        if(player->inventory[i].type == 0){
            player->inventory[i].type = WEAPON;
            Weapon* AWeapon = &player->inventory[i].weapon;

            AWeapon->id = id;
            AWeapon->damage = damage;
            AWeapon->max_durability = max_durability;
            AWeapon->actual_durability = actual_durability;
            strcpy(AWeapon->name, name);
            create = 1;
            break;
        }
    }
    if(create == 0){
        printf("il n'y a plus de place");
    }
}

void create_armor(int index, Player *player, int id, char* name, double damage_reduction){
    int create = 0;
    for(int i = 0; i <= 9; i++){
        if(player->inventory[i].type == 0) {
            player->inventory[i].type = ARMOR;
            Armor *AArmor = &player->inventory[i].armor;

            AArmor->damage_reduction = damage_reduction;
            AArmor->id = id;
            strcpy(AArmor->name, name);
            create = 1;
            break;
        }
    }

    if(create == 0){
        printf("il n'y a plus de place");
    }
}

void canCreateWeapon(int id, Player *player){
    int i, j, damage;
    int create = 0;
    float max_durability, actual_durability;
    char *name;
    for(i = 0; i < 10; i++) {
        switch (id) {
            case 1:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 3) {
                    player->inventory[i].resource.quantity -= 3;
                    name = "WOODEN_SWORD";
                    create = 1;
                    damage = 1, max_durability = 10, actual_durability = 10;
                }
                break;
            case 8:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == ROCK && player->inventory[j].resource.quantity >= 3){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 3;
                            name = "STONE_SWORD";
                            create = 1;
                            damage = 2, max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 19:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == BEECH && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == IRON && player->inventory[j].resource.quantity >= 4){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 4;
                            name = "IRON_SWORD";
                            create = 1;
                            damage = 5, max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 30:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == OAK && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == DIAMOND && player->inventory[j].resource.quantity >= 5){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 5;
                            name = "DIAMOND_SWORD";
                            create = 1;
                            damage = 10, max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 9:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 3){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == ROCK && player->inventory[j].resource.quantity >= 4){
                            player->inventory[i].resource.quantity -= 3;
                            player->inventory[j].resource.quantity -= 4;
                            name = "STONE_SPEAR";
                            create = 1;
                            damage = 3, max_durability = 8, actual_durability = 8;
                        }
                    }
                }
                break;
            case 20:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == BEECH && player->inventory[i].resource.quantity >= 3){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == IRON && player->inventory[j].resource.quantity >= 5){
                            player->inventory[i].resource.quantity -= 3;
                            player->inventory[j].resource.quantity -= 5;
                            name = "IRON_SPEAR";
                            create = 1;
                            damage = 7, max_durability = 8, actual_durability = 8;
                        }
                    }
                }
                break;
            case 31:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == OAK && player->inventory[i].resource.quantity >= 3){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == DIAMOND && player->inventory[j].resource.quantity >= 6){
                            player->inventory[i].resource.quantity -= 3;
                            player->inventory[j].resource.quantity -= 6;
                            name = "DIAMOND_SPEAR";
                            create = 1;
                            damage = 15, max_durability = 8, actual_durability = 8;
                        }
                    }
                }
                break;
            case 10:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == ROCK && player->inventory[j].resource.quantity >= 6){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 6;
                            name = "STONE_HAMMER";
                            create = 1;
                            damage = 4, max_durability = 5, actual_durability = 5;
                        }
                    }
                }
                break;
            case 21:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == BEECH && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == IRON && player->inventory[j].resource.quantity >= 7){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 7;
                            name = "IRON_HAMMER";
                            create = 1;
                            damage = 10, max_durability = 5, actual_durability = 5;
                        }
                    }
                }
                break;
            case 32:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == OAK && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 3 && player->inventory[j].resource.id == DIAMOND && player->inventory[j].resource.quantity >= 8){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 8;
                            name = "DIAMOND_HAMMER";
                            create = 1;
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
    if(create == 1){
        create_weapon(i, player, id, name, damage, max_durability, actual_durability);
    }
}

void canCreateARMOR(int id, Player *player){
    int i;
    int create = 0;
    double damage_reduction;
    char *name;
    for(i = 0; i < 10; i++){
        switch (id) {
            case 11:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == ROCK && player->inventory[i].resource.quantity >= 10) {
                    player->inventory[i].resource.quantity -= 10;
                    name = "STONE_BREASTPLATE";
                    damage_reduction = 0.1;
                    create = 1;
                }
                break;
            case 22:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == IRON && player->inventory[i].resource.quantity >= 12) {
                    player->inventory[i].resource.quantity -= 12;
                    name = "IRON_BREASTPLATE";
                    damage_reduction = 0.2;
                    create = 1;
                }
                break;
            case 33:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == DIAMOND && player->inventory[i].resource.quantity >= 16) {
                    player->inventory[i].resource.quantity -= 16;
                    name = "DIAMOND_BREASTPLATE";
                    damage_reduction = 0.4;
                    create = 1;
                }
                break;
            default:
                printf("erreur");
                break;
        }
    }
    if(create == 1){
        create_armor(i, player, id, name, damage_reduction);
    }
}

void create_tool(int index, Player *player, int id, char* name, int max_durability, int actual_durability){
    int create = 0;
    for(int i = 0; i <= 9; i++){
        if(player->inventory[i].type == 0){
            player->inventory[i].type = TOOL;
            Tool* ATool = &player->inventory[i].tool;

            ATool->id = id;
            ATool->max_durability = max_durability;
            ATool->actual_durability = actual_durability;
            strcpy(ATool->name, name);
            create = 1;
            break;
        }
    }

    if(create == 0){
        printf("il n'y a plus de place");
    }
}

void canCreateTOOL(int id, Player *player){
    int i, j;
    int create = 0;
    float max_durability, actual_durability;
    char *name;
    for(i = 0; i < 10; i++) {
        switch (id) {
            case 2:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 3) {
                    player->inventory[i].resource.quantity -= 3;
                    name = "WOODEN_PICKAXE";
                    create = 1;
                    max_durability = 10, actual_durability = 10;
                }
                break;
            case 12:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 2 && player->inventory[j].resource.id == ROCK && player->inventory[j].resource.quantity >= 3){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 3;
                            name = "STONE_PICKAXE";
                            create = 1;
                            max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 23:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == BEECH && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 2 && player->inventory[j].resource.id == IRON && player->inventory[j].resource.quantity >= 4){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 4;
                            name = "IRON_PICKAXE";
                            create = 1;
                            max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 4:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 3) {
                    player->inventory[i].resource.quantity -= 3;
                    name = "WOODEN_AXE";
                    create = 1;
                    max_durability = 10, actual_durability = 10;
                }
                break;
            case 14:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 2 && player->inventory[j].resource.id == ROCK && player->inventory[j].resource.quantity >= 3){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 3;
                            name = "STONE_AXE";
                            create = 1;
                            max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 25:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == BEECH && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 2 && player->inventory[j].resource.id == IRON && player->inventory[j].resource.quantity >= 4){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 4;
                            name = "IRON_AXE";
                            create = 1;
                            max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 3:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 3) {
                    player->inventory[i].resource.quantity -= 3;
                    name = "WOODEN_BILLHOOK";
                    create = 1;
                    max_durability = 10, actual_durability = 10;
                }
                break;
            case 13:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == FIR && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 2 && player->inventory[j].resource.id == ROCK && player->inventory[j].resource.quantity >= 3){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 3;
                            name = "STONE_BILLHOOK";
                            create = 1;
                            max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            case 24:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == BEECH && player->inventory[i].resource.quantity >= 2){
                    for(j = 0; j <= 9; j++){
                        if(player->inventory[j].type == 2 && player->inventory[j].resource.id == IRON && player->inventory[j].resource.quantity >= 4){
                            player->inventory[i].resource.quantity -= 2;
                            player->inventory[j].resource.quantity -= 4;
                            name = "IRON_BILLHOOK";
                            create = 1;
                            max_durability = 10, actual_durability = 10;
                        }
                    }
                }
                break;
            default:
                printf("erreur");
                break;
        }
    }
    if(create == 1){
        create_tool(i, player, id, name, max_durability, actual_durability);
    }
}

void canCreateCONSUMABLE(int id, Player *player){
    int i, hp;
    int create = 0;
    char *name;
    for(i = 0; i < 10; i++) {
        switch (id) {
            case 15:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == GRASS &&
                    player->inventory[i].resource.quantity >= 2) {
                    player->inventory[i].resource.quantity -= 2;
                    name = "POTION_OF_LIFE_I";
                    hp = 30;
                    create = 1;
                }
                break;
            case 26:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == LAVENDER &&
                    player->inventory[i].resource.quantity >= 2) {
                    player->inventory[i].resource.quantity -= 2;
                    name = "POTION_OF_LIFE_II";
                    hp = 80;
                    create = 1;
                }
                break;
            case 34:
                if (player->inventory[i].type == RESOURCE && player->inventory[i].resource.id == HEMP &&
                    player->inventory[i].resource.quantity >= 2) {
                    player->inventory[i].resource.quantity -= 2;
                    name = "POTION_OF_LIFE_III";
                    hp = 200;
                    create = 1;
                }
                break;
            default:
                printf("mauvaise id");
                break;
        }
    }
    if(create == 1){
        create_consumable(i, player, id, name, hp);
    }
}

void create_consumable(int index, Player *player, int id, char* name, int hp_gain){
    int create = 0;

    for(int i = 0; i <= 9; i++){
        if(player->inventory[i].type == 0){
            player->inventory[i].type = CONSUMABLE;
            Consumable* AConsumable = &player->inventory[i].consumable;

            AConsumable->id = id;
            AConsumable->hp_gain = hp_gain;
            strcpy(AConsumable->name, name);
            create = 1;
            break;
        }
    }

    if(create == 0){
        printf("il n'y a plus de place");
    }

}


