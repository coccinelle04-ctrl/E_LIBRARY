#include <stdio.h>
#include <string.h>
#include "../include/authors.h"
#include "books.h"

#define FICHIER_AUTEURS "DATABASE/AUTHORS.dat"

void ajouterAuteur() {
    Author a;
    FILE *fichier;

    /* On calcule le nouvel id en comptant les auteurs deja presents */
   fichier = fopen(FICHIER_AUTEURS, "rb");
    int dernierId = 0;

    if (fichier != NULL) {
        Author temp;
        while (fread(&temp, sizeof(Author), 1, fichier) == 1) {
            if (temp.id > dernierId) {
                dernierId = temp.id;
            }
        }
        fclose(fichier);
    }

    a.id = dernierId + 1;

    printf("\n--- Ajout d'un nouvel auteur ---\n");

    printf("Nom complet : ");
    getchar();
    fgets(a.nomComplet, sizeof(a.nomComplet), stdin);
    a.nomComplet[strcspn(a.nomComplet, "\n")] = '\0';

    printf("Nationalite : ");
    fgets(a.nationalite, sizeof(a.nationalite), stdin);
    a.nationalite[strcspn(a.nationalite, "\n")] = '\0';

    printf("Date de naissance (JJ/MM/AAAA) : ");
    fgets(a.dateNaissance, sizeof(a.dateNaissance), stdin);
    a.dateNaissance[strcspn(a.dateNaissance, "\n")] = '\0';

    printf("Biographie : ");
    fgets(a.biographie, sizeof(a.biographie), stdin);
    a.biographie[strcspn(a.biographie, "\n")] = '\0';

    printf("Nombre de livres publies : ");
    scanf("%d", &a.nombreLivresPublies);

    /* On ouvre le fichier en mode "ajout" pour ecrire le nouvel auteur a la fin */
    fichier = fopen(FICHIER_AUTEURS, "ab");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    fwrite(&a, sizeof(Author), 1, fichier);
    fclose(fichier);
}

    void afficherTousAuteurs() {
    FILE *fichier;
    Author a;

    fichier = fopen(FICHIER_AUTEURS, "rb");
    if (fichier == NULL) {
        printf("\nAucun auteur enregistre pour le moment.\n");
        return;
    }

    printf("\n--- Liste des auteurs ---\n");

    int compteur = 0;
    while (fread(&a, sizeof(Author), 1, fichier) == 1) {
        printf("\nID : %d\n", a.id);
        printf("Nom complet : %s\n", a.nomComplet);
        printf("Nationalite : %s\n", a.nationalite);
        printf("Date de naissance : %s\n", a.dateNaissance);
        printf("Biographie : %s\n", a.biographie);
        printf("Nombre de livres publies : %d\n", a.nombreLivresPublies);
        compteur++;
    }

    if (compteur == 0) {
        printf("Aucun auteur enregistre pour le moment.\n");
    }

    fclose(fichier);
}

int rechercherAuteurParId(int id, Author *resultat) {
    FILE *fichier;
    Author a;

    fichier = fopen(FICHIER_AUTEURS, "rb");
    if (fichier == NULL) {
        return 0;
    }

    while (fread(&a, sizeof(Author), 1, fichier) == 1) {
        if (a.id == id) {
            *resultat = a;
            fclose(fichier);
            return 1;
        }
    }

    fclose(fichier);
    return 0;
}

void modifierAuteur() {
    int idRecherche;
    Author a;

    printf("\n--- Modifier un auteur ---\n");
    printf("Entrez l'id de l'auteur a modifier : ");
    scanf("%d", &idRecherche);

    int trouve = rechercherAuteurParId(idRecherche, &a);

    if (trouve == 0) {
        printf("Aucun auteur trouve avec cet id.\n");
        return;
    }

    printf("Auteur trouve : %s\n", a.nomComplet);

    printf("Nouveau nom complet : ");
    getchar();
    fgets(a.nomComplet, sizeof(a.nomComplet), stdin);
    a.nomComplet[strcspn(a.nomComplet, "\n")] = '\0';

    printf("Nouvelle nationalite : ");
    fgets(a.nationalite, sizeof(a.nationalite), stdin);
    a.nationalite[strcspn(a.nationalite, "\n")] = '\0';
    printf("Nouvelle date de naissance (JJ/MM/AAAA) : ");
    fgets(a.dateNaissance, sizeof(a.dateNaissance), stdin);
    a.dateNaissance[strcspn(a.dateNaissance, "\n")] = '\0';

    printf("Nouvelle biographie : ");
    fgets(a.biographie, sizeof(a.biographie), stdin);
    a.biographie[strcspn(a.biographie, "\n")] = '\0';

    printf("Nouveau nombre de livres publies : ");
    scanf("%d", &a.nombreLivresPublies);

    /* On ouvre le fichier en mode "rb+" pour pouvoir lire ET ecrire au meme endroit */
    FILE *fichier = fopen(FICHIER_AUTEURS, "rb+");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    Author temp;
    int position = 0;
    int trouvePourEcriture = 0;

    while (fread(&temp, sizeof(Author), 1, fichier) == 1) {
        if (temp.id == idRecherche) {
            fseek(fichier, position * sizeof(Author), SEEK_SET);
            fwrite(&a, sizeof(Author), 1, fichier);
            trouvePourEcriture = 1;
            break;
        }
        position++;
    }

    fclose(fichier);

    if (trouvePourEcriture == 1) {
        printf("Auteur modifie avec succes !\n");
    } else {
        printf("Erreur lors de la modification.\n");
    }
}

int auteurAdesLivres(int idAuteur) {
    FILE *fichier;
    Book b;

    fichier = fopen("DATABASE/BOOKS.dat", "rb");
    if (fichier == NULL) {
        return 0;
    }

    while (fread(&b, sizeof(Book), 1, fichier) == 1) {
        if (b.idAuteur == idAuteur) {
            fclose(fichier);
            return 1;
        }
    }

    fclose(fichier);
    return 0;
}

void supprimerAuteur() {
    int idASupprimer;
    Author a;

    printf("\n--- Supprimer un auteur ---\n");
    printf("Entrez l'id de l'auteur a supprimer : ");
    scanf("%d", &idASupprimer);

    int trouve = rechercherAuteurParId(idASupprimer, &a);
    if (trouve == 0) {
        printf("Aucun auteur trouve avec cet id.\n");
        return;
    }

    if (auteurAdesLivres(idASupprimer) == 1) {
    printf("Impossible de supprimer : des livres sont encore associes a cet auteur.\n");
    return;
    }

    FILE *ancienFichier = fopen(FICHIER_AUTEURS, "rb");
    FILE *nouveauFichier = fopen("DATABASE/AUTHORS_TEMP.dat", "wb");

    if (ancienFichier == NULL || nouveauFichier == NULL) {
        printf("Erreur : impossible d'ouvrir les fichiers.\n");
        return;
    }

    Author temp;
    while (fread(&temp, sizeof(Author), 1, ancienFichier) == 1) {
        if (temp.id != idASupprimer) {
            fwrite(&temp, sizeof(Author), 1, nouveauFichier);
        }
    }

    fclose(ancienFichier);
    fclose(nouveauFichier);

    remove(FICHIER_AUTEURS);
    rename("DATABASE/AUTHORS_TEMP.dat", FICHIER_AUTEURS);

    printf("Auteur supprime avec succes !\n");
}

int authorExists(int id) {
    Author a;
    return rechercherAuteurParId(id, &a);
}


