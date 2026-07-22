#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/penalites.h"

int genererIdPenalite()
{
    FILE *f;
    Penalty p;
    int dernierId = 0;
    f = fopen("DATABASE/PENALTIES.dat", "rb");
    if (f == NULL)
        return 1;
    while (fread(&p, sizeof(Penalty), 1, f) == 1) {
        if (p.id > dernierId) {
            dernierId = p.id;
        }
    }
    fclose(f);
    return dernierId + 1;
}

int calculerMontantPenalite(int joursRetard)
{
    return joursRetard * 500;
}

void ajouterPenalite(int idUtilisateur,
                     int idEmprunt,
                     int joursRetard)
{
    FILE *f;
    Penalty p;
    f = fopen("DATABASE/PENALTIES.dat", "ab");

    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    p.id = genererIdPenalite();
    p.idUtilisateur = idUtilisateur;
    p.idEmprunt = idEmprunt;
    p.nombreJoursRetard = joursRetard;
    p.montant = calculerMontantPenalite(joursRetard);

    time_t t = time(NULL);
    struct tm *date = localtime(&t);
    sprintf(p.date, "%02d/%02d/%04d",
            date->tm_mday,
            date->tm_mon + 1,
            date->tm_year + 1900);

    fwrite(&p, sizeof(Penalty), 1, f);
    fclose(f);

    FILE *fHistory = fopen("REPORTS/HISTORY.txt", "a");
    if (fHistory != NULL) {
        fprintf(fHistory, "[%02d/%02d/%04d %02d:%02d:%02d] SYSTEM Ajout d'une pénalité de %d FCFA\n",
                date->tm_mday, date->tm_mon + 1, date->tm_year + 1900,
                date->tm_hour, date->tm_min, date->tm_sec, p.montant);
        fclose(fHistory);
    }

    printf("\nPenalité enregistree avec succes.\n");
}

void afficherPenalites()
{
    FILE *f;
    Penalty p;
    f = fopen("DATABASE/PENALTIES.dat", "rb");
    if (f == NULL)
    {
        printf("\nAucune penalite enregistree.\n");
        return;
    }
    printf("\n========== LISTE DES PENALITES ==========\n");
    while (fread(&p, sizeof(Penalty), 1, f) == 1)
    {
        printf("\nID : %d", p.id);
        printf("\nUtilisateur : %d", p.idUtilisateur);
        printf("\nEmprunt : %d", p.idEmprunt);
        printf("\nRetard : %d jour(s)", p.nombreJoursRetard);
        printf("\nMontant : %d FCFA", p.montant);
        printf("\nDate : %s", p.date);
        printf("\n--------------------------------------");
    }
    fclose(f);
}

int nombrePenalites()
{
    FILE *f;
    Penalty p;
    int compteur = 0;
    f = fopen("DATABASE/PENALTIES.dat", "rb");

    if (f == NULL)
        return 0;
    while (fread(&p, sizeof(Penalty), 1, f) == 1)
    {
        compteur++;
    }
    fclose(f);
    return compteur;
}
