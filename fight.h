#ifndef MALLOC_WORLD_FIGHT_H
#define MALLOC_WORLD_FIGHT_H

int open_fight(Player* player, Monster* monster);

char* attack_process(Player* player, Monster* monster, int* weapons);

Weapon* choose_a_weapon(Player* player, int* weapons);

char* consumables_process(Player* player, int* consumables);

Consumable* choose_a_consumable(Player* player, int* consumable);

int leak_process();

char* monster_attack_process(Player* player, Monster* monster, int armor);

int process_xp(Player* player, Monster* monster);

#endif //MALLOC_WORLD_FIGHT_H
