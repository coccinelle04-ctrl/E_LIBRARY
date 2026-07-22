#include <stdio.h>
#include <string.h>
#include "../include/categories.h"

#define FICHIER_CATEGORIES "DATABASE/CATEGORIES.dat"
void ajouterCategorie() {
    Category c;
    FILE *fichier;

   fichier = fopen(FICHIER_CATEGORIES, "rb");
    int dernierId = 0;

    if (fichier != NULL) {
        Category temp;
        while (fread(&temp, sizeof(Category), 1, fichier) == 1) {
            if (temp.id > dernierId) {
                dernierId = temp.id;
            }
        }
        fclose(fichier);
    }

    c.id = dernierId + 1;

    printf("\n--- Ajout d'une nouvelle categorie ---\n");

    printf("Libelle : ");
    fgets(c.libelle, sizeof(c.libelle), stdin);
    c.libelle[strcspn(c.libelle, "\n")] = '\0';

    printf("Description : ");
    fgets(c.description, sizeof(c.description), stdin);
    c.description[strcspn(c.description, "\n")] = '\0';

    printf("Date de creation (JJ/MM/AAAA) : ");
    fgets(c.dateCreation, sizeof(c.dateCreation), stdin);
    c.dateCreation[strcspn(c.dateCreation, "\n")] = '\0';

    fichier = fopen(FICHIER_CATEGORIES, "ab");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    fwrite(&c, sizeof(Category), 1, fichier);
    fclose(fichier);

    printf("Categorie ajoutee avec succes ! (id = %d)\n", c.id);
}

void afficherToutesCategories() {
    FILE *fichier;
    Category c;

    fichier = fopen(FICHIER_CATEGORIES, "rb");
    if (fichier == NULL) {
        printf("\nAucune categorie enregistree pour le moment.\n");
        return;
    }

    printf("\n--- Liste des categories ---\n");

    int compteur = 0;
    while (fread(&c, sizeof(Category), 1, fichier) == 1) {
        printf("\nID : %d\n", c.id);
        printf("Libelle : %s\n", c.libelle);
        printf("Description : %s\n", c.description);
        printf("Date de creation : %s\n", c.dateCreation);
        compteur++;
    }

    if (compteur == 0) {
        printf("Aucune categorie enregistree pour le moment.\n");
    }

    fclose(fichier);
}

int rechercherCategorieParId(int id, Category *resultat) {
    FILE *fichier;
    Category c;

    fichier = fopen(FICHIER_CATEGORIES, "rb");
    if (fichier == NULL) {
        return 0;
    }

    while (fread(&c, sizeof(Category), 1, fichier) == 1) {
        if (c.id == id) {
            *resultat = c;
            fclose(fichier);
            return 1;
        }
    }

    fclose(fichier);
    return 0;
}

void modifierCategorie() {
    int idRecherche;
    Category c;

    printf("\n--- Modifier une categorie ---\n");
    printf("Entrez l'id de la categorie a modifier : ");
    scanf("%d", &idRecherche);
    getchar();

    int trouve = rechercherCategorieParId(idRecherche, &c);

    if (trouve == 0) {
        printf("Aucune categorie trouvee avec cet id.\n");
        return;
    }

    printf("Categorie trouvee : %s\n", c.libelle);

    printf("Nouveau libelle : ");
    fgets(c.libelle, sizeof(c.libelle), stdin);
    c.libelle[strcspn(c.libelle, "\n")] = '\0';

    printf("Nouvelle description : ");
    fgets(c.description, sizeof(c.description), stdin);
    c.description[strcspn(c.description, "\n")] = '\0';
    printf("Nouvelle date de creation (JJ/MM/AAAA) : ");
    fgets(c.dateCreation, sizeof(c.dateCreation), stdin);
    c.dateCreation[strcspn(c.dateCreation, "\n")] = '\0';

    FILE *fichier = fopen(FICHIER_CATEGORIES, "rb+");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    Category temp;
    int position = 0;
    int trouvePourEcriture = 0;

    while (fread(&temp, sizeof(Category), 1, fichier) == 1) {
        if (temp.id == idRecherche) {
            fseek(fichier, position * sizeof(Category), SEEK_SET);
            fwrite(&c, sizeof(Category), 1, fichier);
            trouvePourEcriture = 1;
            break;
        }
        position++;
    }

    fclose(fichier);

    if (trouvePourEcriture == 1) {
        printf("Categorie modifiee avec succes !\n");
    } else {
        printf("Erreur lors de la modification.\n");
    }
}

void supprimerCategorie() {
    int idASupprimer;
    Category c;

    printf("\n--- Supprimer une categorie ---\n");
    printf("Entrez l'id de la categorie a supprimer : ");
    scanf("%d", &idASupprimer);

    int trouve = rechercherCategorieParId(idASupprimer, &c);
    if (trouve == 0) {
        printf("Aucune categorie trouvee avec cet id.\n");
        return;
    }

    FILE *ancienFichier = fopen(FICHIER_CATEGORIES, "rb");
    FILE *nouveauFichier = fopen("DATABASE/CATEGORIES_TEMP.dat", "wb");

    if (ancienFichier == NULL || nouveauFichier == NULL) {
        printf("Erreur : impossible d'ouvrir les fichiers.\n");
        return;
    }

    Category temp;
    while (fread(&temp, sizeof(Category), 1, ancienFichier) == 1) {
        if (temp.id != idASupprimer) {
            fwrite(&temp, sizeof(Category), 1, nouveauFichier);
        }
    }

    fclose(ancienFichier);
    fclose(nouveauFichier);

    remove(FICHIER_CATEGORIES);
    rename("DATABASE/CATEGORIES_TEMP.dat", FICHIER_CATEGORIES);

    printf("Categorie supprimee avec succes !\n");
}

int categoryExists(int id) {
    Category c;
    return rechercherCategorieParId(id, &c);
}
