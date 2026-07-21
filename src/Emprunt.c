#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/Emprunt.h"

// Calcule le prochain ID auto-incrémenté pour BORROWS.dat
int obtenirProchainIDEmprunt() {
    FILE *file = fopen("../DATABASE/BORROWS.dat", "rb");
    if (file == NULL) return 1; // Premier ID si le fichier n'existe pas

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

    // Format EMP_AAAAMMJJHHMMSS
    sprintf(emp->numeroEmprunt, "EMP_%04d%02d%02d%02d%02d%02d",
            annee, mois, jour, heure, minute, seconde);

    // Format date simple "JJ/MM/AAAA" pour dateEmprunt
    sprintf(emp->dateEmprunt, "%02d/%02d/%04d", jour, mois, annee);

    // Calcul de la date de retour prévue (+14 jours simplification)
    int jourRetour = jour + 14;
    int moisRetour = mois;
    int anneeRetour = annee;

    if (jourRetour > 30) { // Simplification gestion mois de 30 jours
        jourRetour -= 30;
        moisRetour++;
        if (moisRetour > 12) {
            moisRetour = 1;
            anneeRetour++;
        }
    }
    sprintf(emp->dateRetourPrevue, "%02d/%02d/%04d", jourRetour, moisRetour, anneeRetour);

    printf("Numero généré : %s\n", emp->numeroEmprunt);
    printf("Date retour prévue (+14j) : %s\n", emp->dateRetourPrevue);
}

void saisirEmprunt(Borrow *emp) {
    printf("\n--- NOUVEL EMPRUNT ---\n");
    emp->id = obtenirProchainIDEmprunt();
    printf("ID attribué (auto) : %d\n", emp->id);

    printf("Entrez l'ID de l'utilisateur : ");
    scanf("%d", &emp->idUtilisateur);

    printf("Entrez l'ID du livre : ");
    scanf("%d", &emp->idLivre);

    strcpy(emp->etat, "EN_COURS");
    genererNumeroEmpruntManuel(emp);
}

void enregistrerEmprunt(Borrow emp) {
    FILE *file = fopen("../DATABASE/BORROWS.dat", "ab");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir DATABASE/BORROWS.dat !\n");
        return;
    }
    fwrite(&emp, sizeof(Borrow), 1, file);
    fclose(file);
    printf("L'emprunt a ete enregistre avec succes !\n");
}

void afficherTousLesEmprunts() {
    FILE *file = fopen("../DATABASE/BORROWS.dat", "rb");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir DATABASE/BORROWS.dat !\n");
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
