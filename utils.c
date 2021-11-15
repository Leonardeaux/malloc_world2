#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

/*
 * Fonction qui renvoie la date et l'heure courante
 */
char* date_now(){
    char* date_now = malloc(sizeof(char) * 255);
    if(date_now == NULL){

        FILE* log = fopen("log.txt", "a+");

        fprintf(log, "La date, c'est non\n");

        fclose(log);

        exit(EXIT_FAILURE);
    }

    int h, min, s, day, mois, an;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    h = local->tm_hour;
    min = local->tm_min;
    s = local->tm_sec;
    day = local->tm_mday;
    mois = local->tm_mon + 1;
    an = local->tm_year + 1900;
    sprintf(date_now, "%02d/%02d/%d %02d:%02d:%02d", day, mois, an, h, min, s);

    return date_now;
}

/*
 * Fonction qui permet le fermeture du programme et d'écrire un message d'erreur dans un fichier de log
 */
void exit_and_write_error(char* message){

    FILE* log = fopen("log.txt", "a+");

    fprintf(log, "%s: %s\n",date_now(), message);

    fclose(log);

    exit(EXIT_FAILURE);
}