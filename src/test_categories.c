#include <stdio.h>
#include "categories.h"
#include <stdlib.h>

int main() {
    int choix;

    do {
        system("cls");

        printf("===== MENU TEST CATEGORIES =====\n");
        printf("1. Ajouter une categorie\n");
        printf("2. Afficher toutes les categories\n");
        printf("3. Modifier une categorie\n");
        printf("4. Supprimer une categorie\n");
        printf("5. Verifier si une categorie existe\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            ajouterCategorie();
        } else if (choix == 2) {
            afficherToutesCategories();
        } else if (choix == 3) {
            modifierCategorie();
        } else if (choix == 4) {
            supprimerCategorie();
        } else if (choix == 5) {
            int id;
            printf("Entrez l'id a verifier : ");
            scanf("%d", &id);
            if (categoryExists(id)) {
                printf("Cette categorie existe.\n");
            } else {
                printf("Cette categorie n'existe pas.\n");
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
