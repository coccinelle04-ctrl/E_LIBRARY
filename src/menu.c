#include <stdio.h>
#include "../include/structs.h"
#include "../include/books.h"
#include "../include/reservations.h"
#include "../include/menu.h"

void lancerMenu() {

    int choix;
    do {
        printf("\n--- MENU TEST ---\n");
        printf("1. Ajouter un livre\n");
        printf("2. Afficher tous les livres\n");
        printf("3. Rechercher un livre par ID\n");
        printf("4. Rechercher un livre par ISBN\n");
        printf("5. Creer une reservation\n");
        printf("6. Afficher les reservations\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

    switch (choix) {
            case 1: {
                    Book livre = saisirLivre();
                    ajouterLivre(livre);
                    break;
            }
            case 2:
                afficherTousLesLivres();
                break;
            case 3: {
                int idRecherche;
                printf("Entrez l'ID du livre a rechercher : ");
                scanf("%d", &idRecherche);
                fflush(stdin);

                Book resultat;
                if (rechercheLivreParId(idRecherche, &resultat)) {
                    printf("Livre trouve : %s (ISBN: %s)\n", resultat.titre, resultat.isbn);
                } else {
                    printf("Aucun livre trouve avec cet ID.\n");
                }
                break;
            }
            case 4: {
                char isbnRecherche[20];
                printf("Entrez l'ISBN du livre a rechercher : ");
                fgets(isbnRecherche, sizeof(isbnRecherche), stdin);
                isbnRecherche[strcspn(isbnRecherche, "\n")] = '\0';

                Book resultat;
                if (rechercheLivreParIsbn(isbnRecherche, &resultat)) {
                    printf("Livre trouve : ID %d - %s\n", resultat.id, resultat.titre);
                } else {
                    printf("Aucun livre trouve avec cet ISBN.\n");
                }
                break;
            }
            case 5: {
                int idUtilisateur, idLivre;
                printf("Entrez l'ID de l'utilisateur : ");
                scanf("%d", &idUtilisateur);
                printf("Entrez l'ID du livre a reserver : ");
                scanf("%d", &idLivre);
                fflush(stdin);

                creerReservation(idUtilisateur, idLivre);
                break;
            }
            case 6:
                afficherReservations();
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}

