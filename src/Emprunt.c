#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/Emprunt.h"
#include "books.h"
#include "structureutilisateur.h"

int obtenirProchainIDEmprunt() {
    FILE *file = fopen("DATABASE/BORROWS.dat", "rb");
    if (file == NULL) return 1;

    Borrow emp;
    int maxID = 0;
    while (fread(&emp, sizeof(Borrow), 1, file) == 1) {
        if (emp.id > maxID) {
            maxID = emp.id;
        }
    }
    fclose(file);
    return maxID + 1;
}

void genererNumeroEmpruntManuel(Borrow *emp) {
    int annee, mois, jour, heure, minute, seconde;

    printf("\n--- SAISIE DE LA DATE ET HEURE D'EMPRUNT ---\n");
    printf("Entrer l'annee actuelle (AAAA) : ");
    scanf("%d", &annee);
    printf("Entrer le mois (MM) : ");
    scanf("%d", &mois);
    printf("Entrer le jour (JJ) : ");
    scanf("%d", &jour);
    printf("Entrer l'heure (HH) : ");
    scanf("%d", &heure);
    printf("Entrer la minute (MM) : ");
    scanf("%d", &minute);
    printf("Entrer la seconde (SS) : ");
    scanf("%d", &seconde);

    sprintf(emp->numeroEmprunt, "EMP_%04d%02d%02d%02d%02d%02d",
            annee, mois, jour, heure, minute, seconde);

    sprintf(emp->dateEmprunt, "%02d/%02d/%04d", jour, mois, annee);

        struct tm dateEmpruntStruct = {0};
        dateEmpruntStruct.tm_year = annee - 1900;
        dateEmpruntStruct.tm_mon = mois - 1;
        dateEmpruntStruct.tm_mday = jour;
        dateEmpruntStruct.tm_hour = 12;

        time_t tEmprunt = mktime(&dateEmpruntStruct);
        time_t tRetour = tEmprunt + (14 * 24 * 60 * 60);

        struct tm *dateRetourStruct = localtime(&tRetour);

        sprintf(emp->dateRetourPrevue, "%02d/%02d/%04d",
        dateRetourStruct->tm_mday,
        dateRetourStruct->tm_mon + 1,
        dateRetourStruct->tm_year + 1900);

    printf("Numero généré : %s\n", emp->numeroEmprunt);
    printf("Date retour prévue (+14j) : %s\n", emp->dateRetourPrevue);
}

int compterEmpruntsEnCours(int idUtilisateur) {
    FILE *file = fopen("DATABASE/BORROWS.dat", "rb");
    if (file == NULL) return 0;

    Borrow emp;
    int compteur = 0;
    while (fread(&emp, sizeof(Borrow), 1, file) == 1) {
        if (emp.idUtilisateur == idUtilisateur && strcmp(emp.etat, "EN_COURS") == 0) {
            compteur++;
        }
    }
    fclose(file);
    return compteur;
}

int saisirEmprunt(Borrow *emp) {
    printf("\n--- NOUVEL EMPRUNT ---\n");

    printf("Entrez l'ID de l'utilisateur : ");
    scanf("%d", &emp->idUtilisateur);

    if (userExists(emp->idUtilisateur) == 0) {
        printf("Erreur : cet utilisateur n'existe pas.\n");
        return 0;
    }

    if (compterEmpruntsEnCours(emp->idUtilisateur) >= 3) {
        printf("Erreur : cet utilisateur a deja 3 emprunts en cours (maximum autorise).\n");
        return 0;
    }

    printf("Entrez l'ID du livre : ");
    scanf("%d", &emp->idLivre);

    Book livre;
    if (rechercheLivreParId(emp->idLivre, &livre) == 0) {
        printf("Erreur : ce livre n'existe pas.\n");
        return 0;
    }

    if (livre.nombreExemplairesDisponibles <= 0) {
        printf("Erreur : ce livre n'a plus d'exemplaires disponibles.\n");
        return 0;
    }

    emp->id = obtenirProchainIDEmprunt();
    printf("ID attribue (auto) : %d\n", emp->id);
    strcpy(emp->etat, "EN_COURS");
    genererNumeroEmpruntManuel(emp);

    mettreAJourStock(emp->idLivre, -1);

    return 1;
}

void enregistrerEmprunt(Borrow emp) {
    FILE *file = fopen("DATABASE/BORROWS.dat", "ab");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir DATABASE/BORROWS.dat !\n");
        return;
    }
    fwrite(&emp, sizeof(Borrow), 1, file);
    fclose(file);
    printf("L'emprunt a ete enregistre avec succes !\n");
}
void genererRecuEmprunt(Borrow emp, const char *loginUtilisateur) {
    char chemin[150];
    sprintf(chemin, "REPORTS/BORROWS/BORROW_%s_%s.txt",
            emp.numeroEmprunt + 4, loginUtilisateur);

    FILE *f = fopen(chemin, "w");
    if (f == NULL) {
        printf("Erreur : impossible de creer le recu d'emprunt.\n");
        return;
    }

    fprintf(f, "===== RECU D'EMPRUNT =====\n");
    fprintf(f, "Numero d'emprunt : %s\n", emp.numeroEmprunt);
    fprintf(f, "Date d'emprunt : %s\n", emp.dateEmprunt);
    fprintf(f, "Date prevue de retour : %s\n", emp.dateRetourPrevue);
    fprintf(f, "ID Livre : %d\n", emp.idLivre);
    fprintf(f, "ID Utilisateur : %d\n", emp.idUtilisateur);

    fclose(f);
    printf("Recu genere : %s\n", chemin);
}

void afficherTousLesEmprunts() {
    FILE *file = fopen("DATABASE/BORROWS.dat", "rb");
    if (file == NULL) {
        printf("Aucun emprunt enregistre pour le moment.\n");
        return;
    }
    Borrow emp;
    printf("\n--- LISTE DES EMPRUNTS ---\n");
    while (fread(&emp, sizeof(Borrow), 1, file) == 1) {
        printf("ID: %d | Code: %s | User: %d | Livre: %d | Date: %s | Prevue: %s | Etat: %s\n",
               emp.id, emp.numeroEmprunt, emp.idUtilisateur, emp.idLivre,
               emp.dateEmprunt, emp.dateRetourPrevue, emp.etat);
    }
    fclose(file);
}
