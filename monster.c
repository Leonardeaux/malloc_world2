#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "monster.h"
#include "map.h"
#include "player.h"
#include "utils.h"

Monster* initialize_monster(int id_monster){

    Monster* AMonster = malloc(sizeof(Monster));
    if(AMonster == NULL){
        exit_and_write_error("Erreur d'allocation mémoire dans la fonction d'initialisation du monstre");
    }
    int zone_monster = monster_zone(id_monster);

    AMonster->id = id_monster;
    AMonster->id_zone = zone_monster;

    if(zone_monster == 1){
        create_monster_zone_one(AMonster);

    } else if(zone_monster == 2){
        create_monster_zone_two(AMonster);

    } else {
        create_monster_zone_three(AMonster);

    }

    return AMonster;
}

int monster_zone(int id_monster){

    for(int i = 0; i < 3; i++){
        if(id_monster == zone_one_monsters[i]){
            return 1;
        }
    }

    for(int i = 0; i < 3; i++){
        if(id_monster == zone_two_monsters[i]){
            return 2;
        }
    }

    for(int i = 0; i < 4; i++){
        if(id_monster == zone_three_monsters[i]){
            return 3;
        }
    }

    return 0;
}

void create_monster_zone_one(Monster* monster){
    srand(time(NULL ));

    strcpy(monster->name, id_monster_name[monster->id - 12]);

    if(monster->id == PIOU){
        monster->hp_max = rand() % 12 + 3;
        monster->damage = 8;
    } else if(monster->id == TOFU){
        monster->hp_max = rand() % 8 + 2;
        monster->damage = 14;
    } else {
        monster->hp_max = rand() % 18 + 14;
        monster->damage = 5;
    }

    monster->hp = monster->hp_max;
    monster->gain_xp = 4;
}

void create_monster_zone_two(Monster* monster){
    srand(time(NULL ));

    strcpy(monster->name, id_monster_name[monster->id - 11]);

    if(monster->id == CRAQUELEUR){
        monster->hp_max = rand() % 25 + 20;
        monster->damage = 14;
    } else if(monster->id == ABRAKNYDE){
        monster->hp_max = rand() % 20 + 12;
        monster->damage = 17;
    } else {
        monster->hp_max = rand() % 18 + 12;
        monster->damage = 20;
    }

    monster->hp = monster->hp_max;
    monster->gain_xp = 80;
}

void create_monster_zone_three(Monster* monster){
    srand(time(NULL ));

    strcpy(monster->name, id_monster_name[monster->id - 11]);

    if(monster->id == BOUFMOUTH){
        monster->hp_max = rand() %  35 + 31;
        monster->damage = 18;
        monster->gain_xp = 500;
    } else if(monster->id == GIVREFOUX){
        monster->hp_max = rand() % 23 + 25;
        monster->damage = 21;
        monster->gain_xp = 500;
    } else if(monster->id == APERIGLOURS){
        monster->hp_max = rand() % 31 + 27;
        monster->damage = 24;
        monster->gain_xp = 500;
    } else {
        monster->hp_max = rand() % 112 + 100;
        monster->damage = 35;
        monster->gain_xp = 3000;
    }

    monster->hp = monster->hp_max;
}

int return_random_monster_id(int id_zone){
    srand(time(NULL ));

    if(id_zone == 0){
        return zone_one_monsters[rand() %  2 + 0];
    } else if(id_zone == 1){
        return zone_two_monsters[rand() %  2 + 0];
    } else {
        return zone_three_monsters[rand() %  2 + 0];
    }
}