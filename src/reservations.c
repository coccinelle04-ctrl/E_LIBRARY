#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/structs.h"
#include "../include/reservations.h"
#include "../include/books.h"


#define FICHIER_RESERVATIONS "DATABASE/RESERVATIONS.dat"

int initReservations(){
    FILE *f;
    f = fopen(FICHIER_RESERVATIONS, "rb");
    if (f == NULL) {
        f = fopen(FICHIER_RESERVATIONS, "wb");
        if (f == NULL) {
            return 0;
        }
        fclose(f);
        return 1;
    }
    fclose(f);
    return 1;
}

int existeReservationEnAttente(int idLivre){
    FILE *f;
    Reservation temp;

    f = fopen(FICHIER_RESERVATIONS, "rb");
    if (f == NULL) {
        return 0;
    }

    while (fread(&temp, sizeof(Reservation), 1, f)) {
        if (temp.idLivre == idLivre && strcmp(temp.etat, "EN_ATTENTE") == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int creerReservation(int idUtilisateur, int idLivre){
    Book livre;
    if (rechercheLivreParId(idLivre, &livre) == 0) {
        printf("Erreur : ce livre n'existe pas.\n");
        return 0;
    }
    if (livre.nombreExemplairesDisponibles != 0) {
        printf("Erreur : ce livre est encore disponible, reservation impossible.\n");
        return 0;
    }

    FILE *f;
    Reservation temp;
    int nb = 0;
    f = fopen(FICHIER_RESERVATIONS, "rb");
    if (f != NULL) {
        while (fread(&temp, sizeof(Reservation), 1, f)) {
            nb++;
        }
        fclose(f);
    }
    Reservation nouvelle;
    nouvelle.id = nb + 1;
    nouvelle.idUtilisateur = idUtilisateur;
    nouvelle.idLivre = idLivre;

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    sprintf(nouvelle.dateReservation, "%02d/%02d/%04d",
            tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900);

    strcpy(nouvelle.etat, "EN_ATTENTE");

    f = fopen(FICHIER_RESERVATIONS, "ab");
    if (f == NULL) {
        return 0;
    }
    fwrite(&nouvelle, sizeof(Reservation), 1, f);
    fclose(f);

    printf("Reservation creee avec succes !\n");
    return 1;
}

int passerReservationDisponible(int idLivre){
    FILE *f;
    Reservation temp;
    int trouve = 0;

    f = fopen(FICHIER_RESERVATIONS, "rb+");
    if (f == NULL) {
        return 0;
    }

    while (fread(&temp, sizeof(Reservation), 1, f)) {
        if (temp.idLivre == idLivre && strcmp(temp.etat, "EN_ATTENTE") == 0) {
            strcpy(temp.etat, "DISPONIBLE");
            fseek(f, -sizeof(Reservation), SEEK_CUR);
            fwrite(&temp, sizeof(Reservation), 1, f);
            trouve = 1;
            break;
        }
    }
    fclose(f);
    return trouve;
}

int annulerReservation(int id){
    FILE *f;
    Reservation temp;
    int trouve = 0;

    f = fopen(FICHIER_RESERVATIONS, "rb+");
    if (f == NULL) {
        return 0;
    }

    while (fread(&temp, sizeof(Reservation), 1, f)) {
        if (temp.id == id) {
            strcpy(temp.etat, "ANNULEE");
            fseek(f, -sizeof(Reservation), SEEK_CUR);
            fwrite(&temp, sizeof(Reservation), 1, f);
            trouve = 1;
            break;
        }
    }
    fclose(f);
    return trouve;
}

void afficherReservations(){
    FILE *f;
    Reservation temp;

    f = fopen(FICHIER_RESERVATIONS, "rb");
    if (f == NULL) {
        printf("Aucune reservation enregistree.\n");
        return;
    }

    while (fread(&temp, sizeof(Reservation), 1, f)) {
        printf("ID: %d | Utilisateur: %d | Livre: %d | Date: %s | Etat: %s\n",
               temp.id, temp.idUtilisateur, temp.idLivre,
               temp.dateReservation, temp.etat);
    }
    fclose(f);
}
