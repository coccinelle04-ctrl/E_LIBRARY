#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/statistiques.h"
#include "../include/penalites.h"
#include "../include/structs.h"

/*---------------------------------------
    Nombre d'emprunts
---------------------------------------*/
int nombreEmprunts()
{
    FILE *f;
    Borrow b;
    int compteur = 0;

    f = fopen("DATABASE/BORROWS.dat", "rb");

    if(f == NULL)
        return 0;

    while(fread(&b, sizeof(Borrow), 1, f) == 1)
    {
        compteur++;
    }

    fclose(f);

    return compteur;
}

/*---------------------------------------
    Nombre de retours
---------------------------------------*/
int nombreRetours()
{
    FILE *f;
    Return r;
    int compteur = 0;

    f = fopen("DATABASE/RETURNS.dat", "rb");

    if(f == NULL)
        return 0;

    while(fread(&r, sizeof(Return), 1, f) == 1)
    {
        compteur++;
    }

    fclose(f);

    return compteur;
}

/*---------------------------------------
    Nombre de réservations
---------------------------------------*/
int nombreReservations()
{
    FILE *f;
    Reservation r;
    int compteur = 0;

    f = fopen("DATABASE/RESERVATIONS.dat", "rb");

    if(f == NULL)
        return 0;

    while(fread(&r, sizeof(Reservation), 1, f) == 1)
    {
        compteur++;
    }

    fclose(f);

    return compteur;
}

/*---------------------------------------
    Nombre d'utilisateurs
---------------------------------------*/
int nombreUtilisateurs()
{
    FILE *f;
    User u;
    int compteur = 0;

    f = fopen("DATABASE/USERS.dat", "rb");

    if(f == NULL)
        return 0;

    while(fread(&u, sizeof(User), 1, f) == 1)
    {
        compteur++;
    }

    fclose(f);

    return compteur;
}

/*---------------------------------------
    Montant total des pénalités
---------------------------------------*/
int montantTotalPenalites()
{
    FILE *f;
    Penalty p;
    int total = 0;

    f = fopen("DATABASE/PENALTIES.dat", "rb");

    if(f == NULL)
        return 0;

    while(fread(&p, sizeof(Penalty), 1, f) == 1)
    {
        total += p.montant;
    }

    fclose(f);

    return total;
}

/*---------------------------------------
    Générer le rapport journalier
---------------------------------------*/
void genererRapportJournalier()
{
    FILE *f;
    char chemin[100];
    time_t t = time(NULL);
    struct tm *date = localtime(&t);

    // Génération du nom de fichier dynamique au format REPORT_AAAAMMJJ.txt[span_0](start_span)[span_0](end_span)
    sprintf(chemin, "REPORTS/DAILY/REPORT_%04d%02d%02d.txt",
            date->tm_year + 1900,
            date->tm_mon + 1,
            date->tm_mday);

    f = fopen(chemin, "w");

    if (f == NULL)
    {
        printf("Erreur lors de la creation du rapport.\n");
        return;
    }

    fprintf(f, "========== RAPPORT JOURNALIER ==========\n\n");
    fprintf(f, "Nombre d'emprunts : %d\n", nombreEmprunts());
    fprintf(f, "Nombre de retours : %d\n", nombreRetours());
    fprintf(f, "Nombre de reservations : %d\n", nombreReservations());
    fprintf(f, "Nombre de nouveaux utilisateurs : %d\n", nombreUtilisateurs());
    fprintf(f, "Nombre de penalites : %d\n", nombrePenalites()); // Utilise la fonction de penalites.c
    fprintf(f, "Montant total des penalites : %d FCFA\n", montantTotalPenalites());
    fprintf(f, "\nLivre le plus emprunte : Non calcule");
    fprintf(f, "\nUtilisateur le plus actif : Non calcule");
    fprintf(f, "\n\n========================================");

    fclose(f);

    printf("\nRapport journalier genere avec succes dans %s.\n", chemin);
}
