#include <stdio.h>
#include <stdlib.h>
#include "authors.h"
#include "categories.h"
#include "books.h"
#include "reservations.h"
#include "Emprunt.h"
#include "Retour.h"
#include "contraintesdacces.h"
#include "securitedesmotsdepasse.h"
#include "structureutilisateur.h"
#include "penalites.h"
#include "tracabilites.h"
#include "statistiques.h"
void pause() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* on vide le buffer clavier */
    }
    printf("\nAppuyez sur une touche pour continuer...");
    getchar();
}
int main() {
    int choix;

    do {
        system("cls");

        printf("========================================\n");
        printf("       MENU TEST GLOBAL - E-LIBRARY\n");
        printf("========================================\n");
        printf("1. Gestion des auteurs\n");
        printf("2. Gestion des categories\n");
        printf("3. Ajouter un livre\n");
        printf("4. Afficher tous les livres\n");
        printf("5. Afficher les reservations\n");
        printf("6. Afficher tous les emprunts\n");
        printf("7. Retourner un livre\n");
        printf("8. Afficher les penalites\n");
        printf("9. Afficher l'historique\n");
        printf("10. Supprimer un livre\n");
        printf("11. Creer un emprunt\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar();

        if (choix == 1) {
            int sousChoix;
            do {
                system("cls");
                printf("--- AUTEURS ---\n");
                printf("1. Ajouter\n2. Afficher tous\n3. Modifier\n4. Supprimer\n5. Verifier existence\n0. Retour\n");
                printf("Choix : ");
                scanf("%d", &sousChoix);

                if (sousChoix == 1) ajouterAuteur();
                else if (sousChoix == 2) afficherTousAuteurs();
                else if (sousChoix == 3) modifierAuteur();
                else if (sousChoix == 4) supprimerAuteur();
                else if (sousChoix == 5) {
                    int id;
                    printf("Id a verifier : ");
                    scanf("%d", &id);
                    printf(authorExists(id) ? "Existe.\n" : "N'existe pas.\n");
                }

                if (sousChoix != 0) {
                    pause();
                }
            } while (sousChoix != 0);
        }
        else if (choix == 2) {
            int sousChoix;
            do {
                system("cls");
                printf("--- CATEGORIES ---\n");
                printf("1. Ajouter\n2. Afficher toutes\n3. Modifier\n4. Supprimer\n5. Verifier existence\n0. Retour\n");
                printf("Choix : ");
                scanf("%d", &sousChoix);

                if (sousChoix == 1) ajouterCategorie();
                else if (sousChoix == 2) afficherToutesCategories();
                else if (sousChoix == 3) modifierCategorie();
                else if (sousChoix == 4) supprimerCategorie();
                else if (sousChoix == 5) {
                    int id;
                    printf("Id a verifier : ");
                    scanf("%d", &id);
                    printf(categoryExists(id) ? "Existe.\n" : "N'existe pas.\n");
                }

                if (sousChoix != 0) {
                    pause();
                }
            } while (sousChoix != 0);
        }
        else if (choix == 3) {
            Book b = saisirLivre();
            int succes = ajouterLivre(b);
            if (succes == 1) {
            printf("\nLivre ajoute avec succes !\n");
            } else {
            printf("\nEchec de l'ajout du livre.\n");
            }
            }
        else if (choix == 10) {
            int id;
            printf("Id du livre a supprimer : ");
            scanf("%d", &id);
            supprimerLivre(id);
        }
        else if (choix == 4) {
            afficherTousLesLivres();
        }
        else if (choix == 5) {
            afficherReservations();
        }
        else if (choix == 6) {
            afficherTousLesEmprunts();
        }
        else if (choix == 7) {
            retournerLivre();
        }
        else if (choix == 8) {
            afficherPenalites();
        }
        else if (choix == 9) {
            afficherHistorique();
        }
        else if (choix == 11) {
            Borrow emp;
            saisirEmprunt(&emp);
            enregistrerEmprunt(emp);
        }

        if (choix != 0) {
            pause();
        }

    } while (choix != 0);

    return 0;
}
