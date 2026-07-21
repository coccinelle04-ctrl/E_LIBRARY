#include <stdio.h>
#include <stdlib.h>

#include "../include/tracabilites.h"
#include "../include/penalites.h"
#include "../include/statistiques.h"

int main()
{
    int choix;
    int idUser, idEmp, jours; // 'montant' retiré car calculé en interne
    char login[20];
    char operation[100];

    do
    {
        printf("\n==============================");
        printf("\n   GESTION DES PENALITES");
        printf("\n==============================");

        printf("\n1. Ajouter une penalite");
        printf("\n2. Afficher les penalites");
        printf("\n3. Enregistrer une operation");
        printf("\n4. Afficher l'historique");
        printf("\n5. Afficher le nombre de penalites");
        printf("\n6. Afficher le montant total");
        printf("\n7. Generer le rapport journalier");
        printf("\n0. Quitter");

        printf("\n\nVotre choix : ");
        scanf("%d", &choix);

        switch(choix)
        {
        case 1:
            printf("ID utilisateur : ");
            scanf("%d", &idUser);

            printf("ID emprunt : ");
            scanf("%d", &idEmp);

            printf("Nombre de jours de retard : ");
            scanf("%d", &jours);

            // Appel mis à jour (le montant est géré automatiquement par la fonction)
            ajouterPenalite(idUser, idEmp, jours);
            break;

        case 2:
            afficherPenalites();
            break;

        case 3:
            printf("Login : ");
            scanf("%s", login);

            getchar(); // Vider le buffer

            printf("Operation : ");
            fgets(operation, sizeof(operation), stdin);

            enregistrerHistorique(login, operation);
            break;

        case 4:
            afficherHistorique();
            break;

        case 5:
            printf("\nNombre de penalites : %d\n", nombrePenalites());
            break;

        case 6:
            printf("\nMontant total : %d FCFA\n", montantTotalPenalites());
            break;

        case 7:
            genererRapportJournalier();
            break;

        case 0:
            printf("\nAu revoir.\n");
            break;

        default:
            printf("\nChoix invalide.\n");
        }

    }
    while(choix != 0);

    return 0;
}
