#ifndef MALLOC_WORLD_SHIFT_H
#define MALLOC_WORLD_SHIFT_H
#include "player.h"

void print_menu(int*** map, int side, Player* player);

void move_player(int*** map, int side, Player* player);

void case_forward(int*** map, int side, Player* player, char direction);

char* case_forward_for_menu(int*** map, int side, Player* player, char direction);

int case_process(int a_case, Player* player);

char* case_return(int a_case, Player* player);

#endif
