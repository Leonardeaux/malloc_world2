//
// Created by jeffr on 20/11/2021.
//

#ifndef MALLOC_WORLD2_CRAFT_H
#define MALLOC_WORLD2_CRAFT_H

void canCreateWeapon(int id, Player *player);

void create_weapon(int index, Player *player, int id, char* name, int damage, int max_durability, int actual_durability);

void create_armor(int index, Player *player, int id, char* name, double damage_reduction);

void canCreateARMOR(int id, Player *player);

void create_tool(int index, Player *player, int id, char* name, int max_durability, int actual_durability);

void canCreateTOOL(int id, Player *player);

void canCreateCONSUMABLE(int id, Player *player);

void create_consumable(int index, Player *player, int id, char* name, int hp_gain);


#endif //MALLOC_WORLD2_CRAFT_H
