#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/statistiques.h"
#include "../include/penalites.h"
#include "../include/structs.h"
#include "../include/books.h"
#include "../include/structureutilisateur.h"


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
    int idLivreTop = livreLePlusEmprunte();
    if (idLivreTop != -1) {
    Book livreTop;
    if (rechercheLivreParId(idLivreTop, &livreTop) == 1) {
        fprintf(f, "\nLivre le plus emprunte : %s (id %d)", livreTop.titre, idLivreTop);
    } else {
        fprintf(f, "\nLivre le plus emprunte : id %d", idLivreTop);
    }
    } else {
    fprintf(f, "\nLivre le plus emprunte : Aucun emprunt enregistre");
    }

    int idUserTop = utilisateurLePlusActif();
    if (idUserTop != -1) {
    User userTop;
    if (rechercherUtilisateurParId(idUserTop, &userTop) == 1) {
        fprintf(f, "\nUtilisateur le plus actif : %s %s (id %d)", userTop.prenom, userTop.nom, idUserTop);
    } else {
        fprintf(f, "\nUtilisateur le plus actif : id %d", idUserTop);
    }
    } else {
    fprintf(f, "\nUtilisateur le plus actif : Aucun emprunt enregistre");
    }
    fprintf(f, "\n\n========================================");

    fclose(f);

    printf("\nRapport journalier genere avec succes dans %s.\n", chemin);
}
int livreLePlusEmprunte() {
    FILE *f = fopen("DATABASE/BORROWS.dat", "rb");
    if (f == NULL) return -1;

    Borrow emp;
    int idsLivres[1000];
    int compteurs[1000];
    int nbLivresDifferents = 0;

    while (fread(&emp, sizeof(Borrow), 1, f) == 1) {
        int trouve = 0;
        for (int i = 0; i < nbLivresDifferents; i++) {
            if (idsLivres[i] == emp.idLivre) {
                compteurs[i]++;
                trouve = 1;
                break;
            }
        }
        if (trouve == 0 && nbLivresDifferents < 1000) {
            idsLivres[nbLivresDifferents] = emp.idLivre;
            compteurs[nbLivresDifferents] = 1;
            nbLivresDifferents++;
        }
    }
    fclose(f);

    if (nbLivresDifferents == 0) return -1;

    int indexMax = 0;
    for (int i = 1; i < nbLivresDifferents; i++) {
        if (compteurs[i] > compteurs[indexMax]) {
            indexMax = i;
        }
    }

    return idsLivres[indexMax];
}

int utilisateurLePlusActif() {
    FILE *f = fopen("DATABASE/BORROWS.dat", "rb");
    if (f == NULL) return -1;

    Borrow emp;
    int idsUsers[1000];
    int compteurs[1000];
    int nbUsersDifferents = 0;

    while (fread(&emp, sizeof(Borrow), 1, f) == 1) {
        int trouve = 0;
        for (int i = 0; i < nbUsersDifferents; i++) {
            if (idsUsers[i] == emp.idUtilisateur) {
                compteurs[i]++;
                trouve = 1;
                break;
            }
        }
        if (trouve == 0 && nbUsersDifferents < 1000) {
            idsUsers[nbUsersDifferents] = emp.idUtilisateur;
            compteurs[nbUsersDifferents] = 1;
            nbUsersDifferents++;
        }
    }
    fclose(f);

    if (nbUsersDifferents == 0) return -1;

    int indexMax = 0;
    for (int i = 1; i < nbUsersDifferents; i++) {
        if (compteurs[i] > compteurs[indexMax]) {
            indexMax = i;
        }
    }

    return idsUsers[indexMax];
}
