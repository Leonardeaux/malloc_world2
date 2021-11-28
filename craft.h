#ifndef MALLOC_WORLD2_CRAFT_H
#define MALLOC_WORLD2_CRAFT_H

void create_weapon2(int index, Player *player, int id, char* name, int damage, int max_durability, int actual_durability);

void canCreateWeapon(int id, Player *player);

void create_armor2(int index, Player *player, int id, char* name, double damage_reduction);

void canCreateARMOR(int id, Player *player);

void create_tool2(int index, Player *player, int id, char* name, int max_durability, int actual_durability);

void canCreateTOOL(int id, Player *player);

void create_consumable2(int index, Player *player, int id, char* name, int hp_gain);

void canCreateCONSUMABLE(int id, Player *player);

#endif //MALLOC_WORLD2_CRAFT_H
