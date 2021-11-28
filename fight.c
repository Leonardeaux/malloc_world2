#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "monster.h"
#include "map.h"
#include "player.h"
#include "utils.h"
#include "fight.h"

int open_fight(Player* player, Monster* monster){

    int choice;

    int* weapons = weapons_in_inventory(player);
    int* consumables = consumables_in_inventory(player);
    int armor = armor_in_inventory(player);

    print_player(player);

    printf("\nVous tombez contre %s avec %d hp\n", monster->name, monster->hp);

    while(player->hp > 0 && monster->hp > 0){
        do {
            print_inventory(player);
            printf("Vous avez %d hp\n", player->hp);
            printf("Que voulez-vous faire ?\n");
            printf("1 : Attaquer\n");
            printf("2 : Utiliser une potion\n");
            printf("3 : Fuir\n");
            choice = getchar();

            if(choice == '1'){
                printf("%s", attack_process(player, monster, weapons));

            } else if(choice == '2'){
                printf("%s", consumables_process(player, consumables));

            } else {
                if(leak_process()){
                    return 3;
                } else {
                    printf("La fuite a echoue\n");
                }
            }
            fflush(stdin);
        } while(choice != '1' && choice != '2' && choice != '3');
        fflush(stdin);

        if(monster->hp > 0){
            printf("%s", monster_attack_process(player, monster, armor));
        }
    }

    if(player->hp <= 0){
        return -1;
    } else if(monster->hp <= 0){
        process_xp(player, monster);

        return 1;
    } else {
        return 0;
    }
}

char* attack_process(Player* player, Monster* monster, int* weapons){

    if(weapons != NULL){
        char* result = malloc(sizeof(char) * 255);

        Weapon* selected_weapon = choose_a_weapon(player, weapons);
        monster->hp -= selected_weapon->damage;
        selected_weapon->actual_durability -= 1;

        if(monster->hp <= 0){
            sprintf(result, "Le %s est mort\n", monster->name);
            return  result;
        } else {
            sprintf(result, "Attaque effectue, le %s a %d hp\n", monster->name, monster->hp);
            return result;
        }
    } else {
        return "Vous n'avez pas d'armes sur vous\n";
    }
}

Weapon* choose_a_weapon(Player* player, int* weapons){
    int weapon_choice;

    for(int i = 1; i < weapons[0]; i++){
        printf("| Arme n %d : %s |\n", i, player->inventory[weapons[i]].weapon.name);
    }
    do{
        printf("Choississez une arme pour attaquer (entrez son numero)\n");
        weapon_choice = getchar();
        fflush(stdin);
    } while(weapon_choice < '1' || weapon_choice > ('1' + (weapons[0] - 2)));

    weapon_choice = weapon_choice - '0';

    return &player->inventory[weapons[weapon_choice]].weapon;
}

char* consumables_process(Player* player, int* consumables){

    if(consumables != NULL){
        char* result = malloc(sizeof(char) * 255);

        Consumable* selected_consumable = choose_a_consumable(player, consumables);
        if(selected_consumable->hp_gain > (player->hp_max - player->hp)){
            player->hp = player->hp_max;
        } else {
            player->hp += selected_consumable->hp_gain;
        }
        sprintf(result, "Vous avez %d hp\n", player->hp);
        return  result;

    } else {
        return "Vous n'avez pas de consomables sur vous\n";
    }
}

Consumable* choose_a_consumable(Player* player, int* consumable){
    int consumable_choice;

    for(int i = 1; i < consumable[0]; i++){
        printf("| Consomable n %d : %s |\n", i, player->inventory[consumable[i]].consumable.name);
    }
    do{
        printf("Choississez un consomable (entrez son numero)\n");
        consumable_choice = getchar();
        fflush(stdin);
    } while(consumable_choice < '1' || consumable_choice > ('1' + (consumable[0] - 2)));

    consumable_choice = consumable_choice - '0';

    return &player->inventory[consumable[consumable_choice]].consumable;
}

int leak_process(){
    int leak;
    srand(time(NULL ));

    leak = rand() % 10;
    if(leak <= 3){
        return 1;
    } else {
        return 0;
    }
}

char* monster_attack_process(Player* player, Monster* monster, int armor){

    char* result = malloc(sizeof(char) * 255);

    if(armor != -1){
        player->hp -= (int)(monster->damage - (monster->damage * player->inventory[armor].armor.damage_reduction));

        sprintf(result, "Vous avez subit %d et il vous reste %d hp avec la reduction de votre armure\n", (int)(monster->damage - (monster->damage * player->inventory[armor].armor.damage_reduction)), player->hp);
    } else {
        player->hp -= monster->damage;

        sprintf(result, "Vous avez subit %d et il vous reste %d hp\n", monster->damage, player->hp);
    }

    return result;
}

int process_xp(Player* player, Monster* monster){
    if(monster->gain_xp > (player->next_xp - player->xp) && player->level < 10){
        player->level += 1;
        player->hp_max += xp_gain_hp_tab[player->level];
        player->next_xp = (int)exp((double)player->level);

    } else {
        player->xp += monster->gain_xp;
    }
}