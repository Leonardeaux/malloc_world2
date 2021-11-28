#ifndef C_SAVING_H
#define C_SAVING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

char* concat(const char *s1, const char *s2);

void savingplayer(Player* player);

void savingmap (int*** map, int side, Player* player);

void savingstorage(Player* player);

void openfile(char* nom, Player* player);

void readinventory(long position, FILE* g, Player* player);

void newinv(Player*player, int index, int qtt, int dur, int id);

int* findinv (char va, char wa, char oa, FILE*g, long t);

int check_file(const char* filename);

#endif //C_SAVING_H