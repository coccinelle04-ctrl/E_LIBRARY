#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/tracabilites.h"

void enregistrerHistorique(char login[], char operation[])
{
    FILE *f;
    time_t t;
    struct tm *date;
    t = time(NULL);
    date = localtime(&t);

    f = fopen("REPORTS/HISTORY.txt", "a");
    if(f == NULL)
    {
        printf("Impossible d'ouvrir HISTORY.txt\n");
        return;
    }

    fprintf(f,
            "[%02d/%02d/%04d %02d:%02d:%02d] %s %s\n",
            date->tm_mday,
            date->tm_mon + 1,
            date->tm_year + 1900,
            date->tm_hour,
            date->tm_min,
            date->tm_sec,
            login,
            operation);

    fclose(f);
}

void afficherHistorique()
{
    FILE *f;
    char ligne[300];
    f = fopen("REPORTS/HISTORY.txt", "r");

    if(f == NULL)
    {
        printf("Aucun historique disponible.\n");
        return;
    }
    printf("\n========== HISTORIQUE ==========\n\n");
    while(fgets(ligne, sizeof(ligne), f) != NULL)
    {
        printf("%s", ligne);
    }
    fclose(f);
}
