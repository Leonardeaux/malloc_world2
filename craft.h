//
// Created by jeffr on 20/11/2021.
//

#ifndef MALLOC_WORLD2_CRAFT_H
#define MALLOC_WORLD2_CRAFT_H

int canCreateWOODENSWORD(int id, Player *player);

void create_weapon(int index, Player *player, int id, char* name, int damage, float max_durability, float actual_durability);

void create_armor(int index, Player *player, int id);

int canCreateARMOR(int id, Player *player);

void create_tool(int index, Player *player, int id, char* name, float max_durability, float actual_durability);

int canCreateTOOL(int id, Player *player);

int canCreateCONSUMABLE(int id, Player *player);

void create_Consumable(int index, Player *player, int id);


#endif //MALLOC_WORLD2_CRAFT_H
