#include <stdio.h>
#include <stdlib.h>

// Inclusion des fichiers d'en-tête (headers)
#include "../include/structs.h"
#include "../include/Emprunt.h"
#include "../include/Retour.h"

int main() {
    int choix;
    Borrow monEmprunt;

    do {
        printf("\n===================================\n");
        printf("    GESTION DES EMPRUNTS ET RETOURS\n");
        printf("===================================\n");
        printf("1. Enregistrer un nouvel emprunt\n");
        printf("2. Marquer un livre comme rendu\n");
        printf("3. Afficher la liste des emprunts\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            saisirEmprunt(&monEmprunt);
            enregistrerEmprunt(monEmprunt);
        }
        else if (choix == 2) {
            retournerLivre();
        }
        else if (choix == 3) {
            afficherTousLesEmprunts();
        }
        else if (choix == 0) {
            printf("Fermeture du programme...\n");
        }
        else {
            printf("Choix invalide, veuillez reessayer.\n");
        }

    } while (choix != 0);

    return 0;
}
