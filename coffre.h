#ifndef C_COFFRE_H
#define C_COFFRE_H

#include "player.h"

void emptystorage(Player* player);

void repare(Player* player, int index);

int appendstorage(Player* player, int index, int quantite);

int appendinventory(Player *player, int idname, int quantite);

void PNJmenu(Player *player);

#endif //C_COFFRE_H

/*
 * 1 -- Epee en bois
 * 2 -- Pioche en bois
 * 3 -- Serpe en bois
 * 4 -- Hache en bois
 * 5 -- Sapin
 * 6 -- Pierre
 * 7 -- Herbe
 * 8 -- Epee en pierre
 * 9 -- Lance en pierre
 * 10 -- Marteau en pierre
 * 11 -- Plastron en pierre
 * 12 -- Pioche en pierre
 * 13 -- Serpe en pierre
 * 14 -- Hache en pierre
 * 15 -- Potion de vie I
 * 16 -- Hetre
 * 17 -- Fer
 * 18 -- Lavande
 * 19 -- Epee en fer
 * 20 -- Lance en fer
 * 21 -- Marteau en fer
 * 22 -- Plastron en fer
 * 23 -- Pioche en fer
 * 24 -- Serpe en fer
 * 25 -- Hache en fer
 * 26 -- Potion de vie II
 * 27 -- Chene
 * 28 -- Diamant
 * 29 -- Chanvre
 * 30 -- Epee en diamant
 * 31 -- Lance en diamant
 * 32 -- Marteau en diamant
 * 33 -- Plastron en diamant
 * 34 -- Potion de vie III
 */