#include "saving.h"

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void savingplayer(Player* player){
    char* nom = concat(player->username, ".txt");
    FILE* g = fopen(nom, "a");
    fseek(g, 0, SEEK_END);
    if(g != NULL){
        printf("\nLe fichier de sauvegarde du player a ete cree");
    } else{
        printf("Le fichier de sauvegarde du player n'a pas ete creee");
    }
    fprintf(g, "\n=== PLAYER ===\n{%02d}\n{%05d}/{%05d}\n",player->level,player->xp,player->next_xp);
    fprintf(g,"{%03d}/{%03d}\n", player->hp, player->hp_max);
    fprintf(g, "-- INVENTORY --\n");
    for (int i = 0; i <= 9; ++i) {
        if (player->inventory[i].type == RESOURCE){
            fprintf(g,"{%02d}@{%02d}@{00}\n", player->inventory[i].resource.quantity, player->inventory[i].resource.id);
        } else if (player->inventory[i].type == WEAPON){
            fprintf(g,"{01}@{%02d}@{%02d}\n", player->inventory[i].weapon.id, player->inventory[i].weapon.actual_durability);
        } else if (player->inventory[i].type == ARMOR){
            fprintf(g,"{01}@{%02d}@{00}\n", player->inventory[i].armor.id);
        } else if (player->inventory[i].type == CONSUMABLE){
            fprintf(g,"{01}@{%02d}@{00}\n", player->inventory[i].consumable.id);
        } else if (player->inventory[i].type == TOOL){
            fprintf(g,"{01}@{%02d}@{%02d}\n", player->inventory[i].tool.id, player->inventory[i].tool.actual_durability);
        } else {
            fprintf(g,"{00}@{00}@{00}\n");
        }
    }
    fclose(g);
}

void savingstorage(Player* player){
    char* nom = concat(player->username, ".txt");
    FILE* g = fopen(nom, "a");
    fseek(g, 0, SEEK_END);
    if(g != NULL){
        printf("\nLe fichier de sauvegarde du player a ete ouvert");
    } else{
        printf("Le fichier de sauvegarde du player n'a pas ete ouvert");
    }
    fprintf(g, "\n-- STORAGE --\n");
    for (int i = 0; i <= 33; ++i) {
        if (player->coffre[i].type == RESOURCE){
            fprintf(g,"{%02d}@{%d}\n", player->coffre[i].resource.quantity, i+1);
        } else if (player->coffre[i].type == WEAPON){
            fprintf(g,"{01}@{%d}\n", i+1);
        } else if (player->coffre[i].type == ARMOR){
            fprintf(g,"{01}@{%d}\n", i+1);
        } else if (player->coffre[i].type == CONSUMABLE){
            fprintf(g,"{01}@{%d}\n", i+1);
        } else if (player->coffre[i].type == TOOL){
            fprintf(g,"{01}@{%d}\n", i+1);
        } else {
            fprintf(g,"{00}@{0}\n");
        }
    }

}

void savingmap (int*** map, int side, Player* player){
    char* nom = concat(player->username, ".txt");
    FILE* g = fopen(nom, "w");
    fseek(g, 0, SEEK_END);
    if(g != NULL){
        printf("\nLe fichier de sauvegarde du player a ete ouvert");
    } else{
        printf("Le fichier de sauvegarde du player n'a pas ete ouvert");
    }
    fprintf(g,"\n===================MAP===================\n");
    for(int x = 0; x < 3; x++){
        fprintf(g,"\n------------------ZONE %d-----------------\n", x+1);
        for(int j = 0; j < side; j++){
            fprintf(g,"|");
            for(int i = 0; i < side; i++){
                if(map[x][i][j] < 0 || map[x][i][j] > 9){
                    fprintf(g,"%d |", map[x][i][j]);
                } else {
                    fprintf(g," %d |", map[x][i][j]);
                }
            }
            fprintf(g,"\n");
        }
    }
    fclose(g);
}

void openfile(char* nom, Player* player){
    FILE* g = fopen(nom, "r");
    fseek(g, 0, SEEK_SET);
    if(g != NULL){
    } else{
        printf("Le fichier de sauvegarde du player n'a pas ete ouvert");
    }
    printf("\nLe fichier de sauvegarde du nouveau player a ete ouvert");
    char c, e, f, h, i;
    while (c != '{'){
        c = fgetc(g);
    }
    int lvl1 = (int)fgetc(g) - 48;
    int lvl10 = (int)fgetc(g) - 48;
    player->level = lvl1*10 + lvl10;
    while (e != '{'){
        e = fgetc(g);
    }
    char str[6];
    fgets(str, 6, g);
    int cur_xp10000 = (int) str[0]-48;
    int cur_xp1000 = (int) str[1]-48;
    int cur_xp100 = (int) str[2]-48;
    int cur_xp10 = (int) str[3]-48;
    int cur_xp1 = (int) str[4]-48;
    player->xp = cur_xp10000*10000 + cur_xp1000*1000 + cur_xp100*100 + cur_xp10*10 + cur_xp1;
    while (f != '{'){
        f = fgetc(g);
    }
    int next_xp10000 = (int) fgetc(g)-48;
    int next_xp1000 = (int) fgetc(g)-48;
    int next_xp100 = (int) fgetc(g)-48;
    int next_xp10 = (int) fgetc(g)-48;
    int next_xp1 = (int) fgetc(g)-48;
    player->next_xp = next_xp10000*10000 + next_xp1000*1000 + next_xp100*100 + next_xp10*10 + next_xp1;
    while (h != '{'){
        h = fgetc(g);
    }
    int hp100 = (int) fgetc(g)-48;
    int hp10 = (int) fgetc(g)-48;
    int hp1 = (int) fgetc(g)-48;
    player->hp = hp100*100 + hp10*10 + hp1;
    while (i != '{'){
        i = fgetc(g);
    }
    int max_hp100 = (int) fgetc(g)-48;
    int max_hp10 = (int) fgetc(g)-48;
    int max_hp1 = (int) fgetc(g)-48;
    player->hp_max = max_hp100*100 + max_hp10*10 + max_hp1;
    char u, z, y;
    int* tab = findinv(u, z, y, g, ftell(g));
    newinv(player, 0, tab[0], tab[1], tab[2]);
    char v, w, o;
    int* tab2 = findinv(v, w, o, g, ftell(g));
    newinv(player, 1, tab2[0], tab2[1], tab2[2]);
    char va, wa, oa;
    int* tab3 = findinv(va, wa, oa, g, ftell(g));
    newinv(player, 2, tab3[0], tab3[1], tab3[2]);
    char vb, wb, ob;
    int* tab4 = findinv(vb, wb, ob, g, ftell(g));
    newinv(player, 3, tab4[0], tab4[1], tab4[2]);
    char vc, wc, oc;
    int* tab5 = findinv(vc, wc, oc, g, ftell(g));
    newinv(player, 4, tab5[0], tab5[1], tab5[2]);
    char vd, wd, od;
    int* tab6 = findinv(vd, wd, od, g, ftell(g));
    char ve, we, oe;
    int* tab7 = findinv(ve, we, oe, g, ftell(g));
    char vf, wf, of;
    int* tab8 = findinv(vf, wf, of, g, ftell(g));
    char vg, wg, og;
    int* tab9 = findinv(vg, wg, og, g, ftell(g));
    char vh, wh, oh;
    int* tab10 = findinv(vh, wh, oh, g, ftell(g));
    newinv(player, 9, tab10[0], tab10[1], tab10[2]);
    fclose(g);

}

int* findinv (char va, char wa, char oa, FILE*g, long t){
    fseek(g, t, SEEK_SET);
    while (va != '{'){
        va = fgetc(g);
    }
    int qtt310 = (int) fgetc(g)-48;
    int qtt31 = (int) fgetc(g)-48;
    int qtt3 = qtt310*10 + qtt31;
    while (wa != '{'){
        wa = fgetc(g);
    }
    int id310 = (int) fgetc(g)-48;
    int id31 = (int) fgetc(g)-48;
    int id3 = id310*10 + id31;
    while (oa != '{'){
        oa = fgetc(g);
    }
    int dur310 = (int) fgetc(g)-48;
    int dur31 = (int) fgetc(g)-48;
    int dur3 = dur310*10 + dur31;
    int* tab = malloc(sizeof(int) * 3);
    tab[0] = qtt3;
    tab[2] = id3;
    tab[1] = dur3;
    return tab;
}

int* findstorage (char va, char wa, FILE*g, long t){
    fseek(g, t, SEEK_SET);
    while (va != '{'){
        va = fgetc(g);
    }
    int qtt310 = (int) fgetc(g)-48;
    int qtt31 = (int) fgetc(g)-48;
    int qtt3 = qtt310*10 + qtt31;
    while (wa != '{'){
        wa = fgetc(g);
    }
    int id310 = (int) fgetc(g)-48;
    int id31 = (int) fgetc(g)-48;
    int id3 = id310*10 + id31;
    while (va != '{'){
        va = fgetc(g);
    }
    int* tab = malloc(sizeof(int) * 2);
    tab[0] = qtt3;
    tab[1] = id3;
    return tab;
}

void newstorage(Player*player, int index, int qtt, int id){
    if(id == 1 || (id>=8 && id<=10) || (id>=19 && id<=21) || (id >= 30 && id>= 32)){
        player->coffre[index].type = WEAPON;
        player->coffre[index].weapon.id = id;
    } else if((id >= 5 && id <= 7)||(id >= 16 && id <= 18)|| (id >= 27 && id <= 29)){
        player->coffre[index].type = RESOURCE;
        player->coffre[index].resource.id = id;
        player->coffre[index].resource.quantity = qtt;
    } else if((id>=2 && id<=4)||(id>=12 && id<=14)||(id>=23 && id<=25)){
        player->coffre[index].type = TOOL;
        player->coffre[index].tool.id = id;
    } else if(id == 11 || id == 22 || id == 33){
        player->coffre[index].type = ARMOR;
        player->coffre[index].armor.id = id;
    } else if(id == 15 || id == 26 || id == 34){
        player->coffre[index].type = CONSUMABLE;
        player->coffre[index].consumable.id = id;
    } else{
        printf("Coucou x 1000\n");
    }
}

void newinv(Player*player, int index, int qtt, int dur, int id){
    if(id == 1 || (id>=8 && id<=10) || (id>=19 && id<=21) || (id >= 30 && id>= 32)){
        player->inventory[index].type = WEAPON;
        player->inventory[index].weapon.id = id;
        player->inventory[index].weapon.actual_durability = dur;
    } else if((id >= 5 && id <= 7)||(id >= 16 && id <= 18)|| (id >= 27 && id <= 29)){
        player->inventory[index].type = RESOURCE;
        player->inventory[index].resource.id = id;
        player->inventory[index].resource.quantity = qtt;
    } else if((id>=2 && id<=4)||(id>=12 && id<=14)||(id>=23 && id<=25)){
        player->inventory[index].type = TOOL;
        player->inventory[index].tool.id = id;
        player->inventory[index].tool.actual_durability = dur;
    } else if(id == 11 || id == 22 || id == 33){
        player->inventory[index].type = ARMOR;
        player->inventory[index].armor.id = id;
    } else if(id == 15 || id == 26 || id == 34){
        player->inventory[index].type = CONSUMABLE;
        player->inventory[index].consumable.id = id;
    }
}

int check_file(const char* filename){
    FILE* file = fopen(filename, "r+");

    if(file == NULL){
        return 0;
    } else {
        fclose(file);
        return 1;
    }
}