//
// Created by jeffr on 28/11/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Coffre.h"
#include "player.h"
#include "craft.h"

void emptystorage(Player *player) {
    for (int i = 0; i <= 34; i++) {
        player->coffre[i].type = 0;
    }
}

int appendstorage(Player *player, int index, int quantite) {
    if (player->inventory[index].type == RESOURCE) {
        if (player->inventory[index].resource.quantity >= quantite) {
            int idname = player->inventory[index].resource.id;
            player->coffre[idname].type = RESOURCE;
            player->coffre[idname].resource.quantity += quantite;
            player->inventory[index].resource.quantity -= quantite;
            return 1;
        } else {
            printf("Vous n'avez pas assez de ressources\n");
            return 0;
        }
    } else if (player->inventory[index].type == WEAPON) {
        int idname = player->inventory[index].weapon.id;
        player->coffre[idname].weapon.id = player->inventory[index].weapon.id;
        strcpy(player->inventory[index].weapon.name, player->coffre[idname].weapon.name);
        player->coffre[idname].weapon.damage = player->inventory[index].weapon.damage;
        player->coffre[idname].weapon.max_durability = player->inventory[index].weapon.max_durability;
        player->coffre[idname].weapon.actual_durability = player->inventory[index].weapon.actual_durability;
        player->inventory[index].type = 0;
        /*strcpy(player->inventory[index].weapon.name, "");*/
    } else if (player->inventory[index].type == TOOL) {
        int idname = player->inventory[index].tool.id;
        player->coffre[idname].tool.id = player->inventory[index].tool.id;
        strcpy(player->inventory[index].tool.name, player->coffre[idname].tool.name);
        player->coffre[idname].tool.max_durability = player->inventory[index].tool.max_durability;
        player->coffre[idname].tool.actual_durability = player->inventory[index].tool.actual_durability;
        player->inventory[index].type = 0;
        /*strcpy(player->inventory[index].tool.name, "");*/
    } else if (player->inventory[index].type == ARMOR) {
        int idname = player->inventory[index].armor.id;
        player->coffre[idname].armor.id = player->inventory[index].armor.id;
        player->inventory[index].type = 0;
    } else if (player->inventory[index].type == CONSUMABLE) {
        int idname = player->inventory[index].consumable.id;
        player->coffre[idname].consumable.id = player->inventory[index].consumable.id;
        player->inventory[index].type = 0;
    }
    return 1;
}

int appendinventory(Player *player, int idname, int quantite) {
    int index = 0;
    while (player->inventory[index].type != 0) {
        index++;
    }
    if (player->coffre[idname].type == RESOURCE) {
        int indexexist;
        int quantity;
        for (int i = 0; i <= 9 ; i++) {
            if(player->inventory[i].resource.id == idname){
                printf("Ok");
                indexexist = i;
                quantity = player->inventory[i].resource.quantity + quantite;
            }else{
                indexexist = index;
                quantity = quantite;
            }
        }
        if (player->coffre[idname].resource.quantity >= quantite) {
            player->inventory[indexexist].type = RESOURCE;
            player->inventory[indexexist].resource.id = idname;
            player->inventory[indexexist].resource.quantity = quantity;
            player->coffre[idname].resource.quantity -= quantite;
            return 1;
        } else {
            return 0;
        }
    } else if (player->coffre[idname].type == WEAPON) {
        player->inventory[index].weapon.id = player->coffre[idname].weapon.id;
        strcpy(player->coffre[idname].weapon.name, player->inventory[index].weapon.name);
        player->inventory[index].weapon.damage = player->coffre[idname].weapon.damage;
        player->inventory[index].weapon.max_durability = player->coffre[idname].weapon.max_durability;
        player->inventory[index].weapon.actual_durability = player->coffre[idname].weapon.actual_durability;
        player->coffre[idname].type = 0;
        /*strcpy(player->coffre[idname].weapon.name, "");*/
    } else if (player->coffre[idname].type == TOOL) {
        player->inventory[index].tool.id = player->coffre[idname].tool.id;
        strcpy(player->coffre[idname].tool.name, player->inventory[index].tool.name);
        player->inventory[index].tool.max_durability = player->coffre[idname].tool.max_durability;
        player->inventory[index].tool.actual_durability = player->coffre[idname].tool.actual_durability;
        player->coffre[idname].type = 0;
        /*strcpy(player->inventory[index].tool.name, "");*/
    } else if (player->coffre[idname].type == ARMOR) {
        player->inventory[index].armor.id = player->coffre[idname].armor.id;
        player->coffre[index].type = 0;
    } else if (player->coffre[idname].type == CONSUMABLE) {
        player->inventory[index].consumable.id = player->coffre[idname].consumable.id;
        player->coffre[idname].type = 0;
    }
}


void repare(Player *player, int index) {
    if (player->inventory[index].type == WEAPON) {
        player->inventory[index].weapon.actual_durability = player->inventory[index].weapon.max_durability;
    } else if (player->inventory[index].type == TOOL) {
        player->inventory[index].tool.actual_durability = player->inventory[index].tool.max_durability;
    } else{
        printf("Mauvaise index");
    }
}


void PNJmenu(Player *player) {
    int menu = 1;
    while (menu == 1) {
        printf("--------------Menu PNJ-------------\n1 - Reparer votre equipement\n2 - Crafter vos ressources\n"
               "3 - Stocker des objets\n4 - Recuperer un objet du coffre\n5 - Afficher le contenu de l'inventaire\n6 - Quittez le PNJ");
        int choice;
        printf("\nVotre choix :\n");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Votre inventaire reparable:\n");
            for (int i = 0; i <= 9; i++){
                if(player->inventory[i].type == WEAPON){
                    printf("%d. %s - %d de durabilite\n", i, player->inventory[i].weapon.name, player->inventory[i].weapon.actual_durability);
                } else if(player->inventory[i].type == TOOL){
                    printf("%d. %s - %d de durabilite\n", i, player->inventory[i].tool.name, player->inventory[i].tool.actual_durability);
                }
            }
            printf("\nQuel objet voulez vous reparer : ");
            int choice2;
            scanf("%d", &choice2);
            repare(player, choice2);
        } else if (choice == 2) {
            int choice2;
            printf("Quel objet voulez vous crafter ?\n"
                   "1. Epee en bois (3 sapin)\n"
                   "8. Epee en pierre (2 sapin - 3 pierre)\n"
                   "9. Lance en pierre (3 sapin - 4 pierre)\n"
                   "10. Marteau en pierre (2 sapin - 6 pierre)\n"
                   "11. Plastron en pierre (10 pierre)\n"
                   "2. Pioche en bois (3 sapin)\n"
                   "12. Pioche en pierre (2 sapins - 3 pierres)\n"
                   "4. Hache en bois (3 sapin)\n"
                   "14. Hache en pierre (2 sapin - 3 pierres)\n"
                   "3. Serpe en bois (3 sapin)\n"
                   "13. Serpe en pierre (2 sapin - 3 pierres)\n"
                   "15. Potion de vie I (2 plante de zone I)\n"
                   "19. Epee en fer (2 hetre - 4 minerais de fer)\n"
                   "20. Lance en fer (3 hetre - 5 minerais de fer)\n"
                   "21. Marteau en fer (2 hetre - 7 minerais de fer\n"
                   "22. Plastron en fer (12 minerais de fer)\n"
                   "23. Pioche en fer (2 hetre - 4 minerais de fer)\n"
                   "25. Hache en fer (2 hetre - 4 minerais de fer)\n"
                   "24. Serpe en fer (2 hetre - 4 minerais de fer)\n"
                   "26. Potion de vie II (2 plante de zone II)\n"
                   "30. Epee en diamant (2 chene - 5 minerais de diamant)\n"
                   "31. Lance en diamant (3 chene - 6 minerais de diamant)\n"
                   "32. Marteau en diamant (2 chene - 8 minerais en diamant)\n"
                   "33. Plastron en diamant (16 minerais de diamant)"
                   "34. Potion de vie III (2 plante de zone III)\n");
            printf("\nVotre choix:");
            scanf("%d", &choice2);
            if (choice2 == 1 || (choice2 >= 8 && choice2 <= 10) || choice2 == 4 || choice2 == 14 ||
                (choice2 > 18 && choice2 < 22) || choice2 == 25 || (choice2 > 29 && choice2 < 33)) {
                canCreateWeapon(choice2, player);
            } else if (choice2 == 11 || choice2 == 22 || choice2 == 33) {
                canCreateARMOR(choice2, player);
            } else if (choice2 == 15 || choice2 == 26 || choice2 == 34) {
                canCreateCONSUMABLE(choice2, player);
            } else {
                canCreateTOOL(choice2, player);
            }
        } else if (choice == 3) {
            printf("Votre inventaire : \n\n");
            for (int i = 0; i <= 9; i++){
                if(player->inventory[i].type == WEAPON){
                    printf("%d. %s - 1 quantite\n", i, player->inventory[i].weapon.name);
                } else if(player->inventory[i].type == TOOL){
                    printf("%d. %s - 1 quantite\n", i, player->inventory[i].tool.name);
                } else if(player->inventory[i].type == RESOURCE){
                    printf("%d. Item %d - %d quantite\n", i, player->inventory[i].resource.id, player->inventory[i].resource.quantity);
                } else if(player->inventory[i].type == ARMOR){
                    printf("%d. Item %d - 1 quantite\n", i, player->inventory[i].armor.id);
                } else if(player->inventory[i].type == CONSUMABLE){
                    printf("%d. Item %d - 1 quantite\n", i, player->inventory[i].consumable.id);
                }
            }
            int object;
            printf("\nQuel case de votre inventaire voulez-vous stocker :");
            scanf("%d", &object);
            int quantity;
            printf("En quel quantite :");
            scanf("%d", &quantity);
            appendstorage(player, object, quantity);
        } else if (choice == 4) {
            for (int i = 0; i < 34; i++){
                if(player->coffre[i].type == WEAPON){
                    printf("%d. %s - 1 quantite\n", i, player->coffre[i].weapon.name);
                } else if(player->coffre[i].type == TOOL){
                    printf("%d. %s - 1 quantite\n", i, player->coffre[i].tool.name);
                } else if(player->coffre[i].type == RESOURCE){
                    printf("%d. Item %d - %d quantite\n", i, i, player->coffre[i].resource.quantity);
                } else if(player->coffre[i].type == ARMOR){
                    printf("%d. Item %d - 1 quantite\n", i, i);
                } else if(player->coffre[i].type == CONSUMABLE){
                    printf("%d. Item %d - 1 quantite\n", i, i);
                }
            }
            int object;
            printf("Quel objet de votre coffre voulez-vous recuperer :");
            scanf("%d", &object);
            int quantity;
            printf("En quel quantite :");
            scanf("%d", &quantity);
            appendinventory(player, object, quantity);
        } else if(choice == 5){
            printf("Votre inventaire:\n");
            for (int i = 0; i <= 9; i++){
                if(player->inventory[i].type == WEAPON){
                    printf("%d. %s - %d de durabilite\n", i, player->inventory[i].weapon.name, player->inventory[i].weapon.actual_durability);
                } else if(player->inventory[i].type == TOOL){
                    printf("%d. %s - %d de durabilite\n", i, player->inventory[i].tool.name, player->inventory[i].tool.actual_durability);
                } else if(player->inventory[i].type == CONSUMABLE){
                    printf("%d. %s - %d de gain d hp\n", i, player->inventory[i].consumable.name, player->inventory[i].consumable.hp_gain);
                }else if(player->inventory[i].type == RESOURCE){
                    printf("%d. %s - avec une quantite de %d\n", i, player->inventory[i].resource.name, player->inventory[i].resource.quantity);
                }else if(player->inventory[i].type == ARMOR){
                    printf("%d. %s - avec une resistance de %f\n", i, player->inventory[i].armor.name, player->inventory[i].armor.damage_reduction);
                }
            }
        }else{
            menu = 0;
        }
    }
}

