#include <stdio.h>
#include <stdlib.h>
#include "authors.h"

int main() {
    int choix;

    do {
        system("cls");

        printf("===== MENU TEST AUTEURS =====\n");
        printf("1. Ajouter un auteur\n");
        printf("2. Afficher tous les auteurs\n");
        printf("3. Modifier un auteur\n");
        printf("4. Supprimer un auteur\n");
        printf("5. Verifier si un auteur existe\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            ajouterAuteur();
        } else if (choix == 2) {
            afficherTousAuteurs();
        } else if (choix == 3) {
            modifierAuteur();
        } else if (choix == 4) {
            supprimerAuteur();
        } else if (choix == 5) {
            int id;
            printf("Entrez l'id a verifier : ");
            scanf("%d", &id);
            if (authorExists(id)) {
                printf("Cet auteur existe.\n");
            } else {
                printf("Cet auteur n'existe pas.\n");
            }
        }

        if (choix != 0) {
            printf("\nAppuyez sur une touche pour continuer...");
            getchar();
            getchar();
        }

    } while (choix != 0);

    printf("Fin du programme.\n");
    return 0;
}
