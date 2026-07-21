#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Retour.h"
//s
int obtenirProchainIDRetour() {
    FILE *file = fopen("../DATABASE/RETURNS.dat", "rb");
    if (file == NULL) return 1;

    Return ret;
    int maxID = 0;
    while (fread(&ret, sizeof(Return), 1, file) == 1) {
        if (ret.id > maxID) maxID = ret.id;
    }
    fclose(file);
    return maxID + 1;
}

void retournerLivre() {
    char numRecherche[30];
    printf("\n--- RETOUR D'UN LIVRE ---\n");
    printf("Entrez le numero d'emprunt : ");
    scanf("%s", numRecherche);

    FILE *fBorrows = fopen("../DATABASE/BORROWS.dat", "rb+");
    if (fBorrows == NULL) {
        printf("Erreur : Impossible d'ouvrir DATABASE/BORROWS.dat !\n");
        return;
    }

    Borrow emp;
    int trouve = 0;

    while (fread(&emp, sizeof(Borrow), 1, fBorrows) == 1) {
        if (strcmp(emp.numeroEmprunt, numRecherche) == 0) {
            trouve = 1;

            if (strcmp(emp.etat, "RETOURNE") == 0) {
                printf("Cet emprunt a déjà été marqué comme RETOURNE !\n");
                fclose(fBorrows);
                return;
            }

            Return ret;
            ret.id = obtenirProchainIDRetour();
            ret.idEmprunt = emp.id;

            printf("Entrez la date reelle de retour : ");
            scanf("%s", ret.dateRetourReelle);

            printf("Entrez le nombre de jours de retard : ");
            scanf("%d", &ret.nombreJoursRetard);

            int tarifParJour = 500;
            ret.montantPenalite = ret.nombreJoursRetard * tarifParJour;

            if (ret.nombreJoursRetard > 0) {
                strcpy(emp.etat, "EN_RETARD");
            } else {
                strcpy(emp.etat, "RETOURNE");
            }

            fseek(fBorrows, -((long)sizeof(Borrow)), SEEK_CUR);
            fwrite(&emp, sizeof(Borrow), 1, fBorrows);

            FILE *fReturns = fopen("../DATABASE/RETURNS.dat", "ab");
            if (fReturns != NULL) {
                fwrite(&ret, sizeof(Return), 1, fReturns);
                fclose(fReturns);
                printf("\n--- RECU DU RETOUR ---\n");
                printf("ID Retour : %d | ID Emprunt : %d\n", ret.id, ret.idEmprunt);
                printf("Retard : %d jours | Penalite : %d FCFA\n", ret.nombreJoursRetard, ret.montantPenalite);
                printf("Retour enregistre dans RETURNS.dat avec succes !\n");
            } else {
                printf("Erreur lors de l'enregistrement dans RETURNS.dat !\n");
            }
            break;
        }
    }

    if (!trouve) {
        printf("Erreur : Numero d'emprunt '%s' introuvable.\n", numRecherche);
    }

    fclose(fBorrows);
}
