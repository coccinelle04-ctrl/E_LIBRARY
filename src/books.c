#include <stdio.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/books.h"
#include "../include/authors.h"
#include "../include/categories.h"


#define FICHIER_LIVRES "DATABASE/BOOKS.dat"

int initBooks(){
    FILE* f;
    f=fopen(FICHIER_LIVRES, "rb");
    if(f==NULL){
        f=fopen(FICHIER_LIVRES, "wb");
        if(f==NULL){
            printf("La creation du fichier a echouer");
            return 0;
        }
        else {
            fclose(f);
            printf("Le fichier est creer avec succes!");
            return 1;
        }
    }
    else {
        fclose(f);
        printf("Le fichier existe deja!");
        return 1;
    }
   }



int isbnExiste(char* isbn){
    FILE *f;
    Book parcourir;
    f=fopen(FICHIER_LIVRES, "rb");
    if (f==NULL){
        return 0;
    }
    while(fread(&parcourir, sizeof(Book), 1,f)){
        if(strcmp(isbn ,parcourir.isbn)==0){
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}


int livreExisteParId(int id){
    FILE *f;
    Book parcourir;
    f=fopen(FICHIER_LIVRES, "rb");
    if (f==NULL){
        return 0;
    }
    while(fread(&parcourir, sizeof(Book), 1,f)){
        if(parcourir.id == id){
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int ajouterLivre(Book livre){
    if(authorExists(livre.idAuteur) == 0){
        printf("Erreur : l'auteur n'existe pas.\n");
        return 0;
    }
    if(categoryExists(livre.idCategorie) == 0){
        printf("Erreur : la categorie n'existe pas.\n");
        return 0;
    }
    if(isbnExiste(livre.isbn) == 1){
        printf("Erreur : cet ISBN existe deja.\n");
        return 0;
    }

    FILE *f;
    Book temp;
    int nb = 0;

    f = fopen(FICHIER_LIVRES, "rb");
    int dernierId = 0;
    if (f != NULL) {
        while (fread(&temp, sizeof(Book), 1, f)) {
            if (temp.id > dernierId) {
                dernierId = temp.id;
            }
        }
        fclose(f);
    }
    livre.id = dernierId + 1;

    f = fopen(FICHIER_LIVRES, "ab");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier pour ecrire.\n");
        return 0;
    }
    fwrite(&livre, sizeof(Book), 1, f);
    fclose(f);

    printf("Livre ajoute avec succes !\n");
    return 1;
}

int rechercheLivreParIsbn(char *isbn, Book *resultat){
    FILE *f;
    Book temp;

    f = fopen(FICHIER_LIVRES, "rb");
    if (f == NULL) {
        return 0;
    }

    while (fread(&temp, sizeof(Book), 1, f)) {
        if (strcmp(temp.isbn, isbn) == 0) {
            *resultat = temp;
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int rechercheLivreParId(int id, Book *resultat){
    FILE *f;
    Book temp;

    f = fopen(FICHIER_LIVRES, "rb");
    if (f == NULL) {
        return 0;
    }

    while (fread(&temp, sizeof(Book), 1, f)) {
        if (temp.id == id) {
            *resultat = temp;
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void afficherTousLesLivres(){
    FILE *f;
    Book temp;

    f = fopen(FICHIER_LIVRES, "rb");
    if (f == NULL) {
        printf("Aucun livre enregistre.\n");
        return;
    }

    while (fread(&temp, sizeof(Book), 1, f)) {
        printf("ID: %d | ISBN: %s | Titre: %s | Disponibles: %d/%d\n",
               temp.id, temp.isbn, temp.titre,
               temp.nombreExemplairesDisponibles, temp.nombreExemplairesTotal);
    }
    fclose(f);
}

int mettreAJourStock(int idLivre, int quantite){
    FILE *f;
    Book temp;
    int trouve = 0;

    f = fopen(FICHIER_LIVRES, "rb+");
    if (f == NULL) {
        return 0;
    }

    while (fread(&temp, sizeof(Book), 1, f)) {
        if (temp.id == idLivre) {
            temp.nombreExemplairesDisponibles += quantite;
            fseek(f, -sizeof(Book), SEEK_CUR);
            fwrite(&temp, sizeof(Book), 1, f);
            trouve = 1;
            break;
        }
    }
    fclose(f);
    return trouve;
}

Book saisirLivre() {
    Book livre;


    fflush(stdin);
    printf("ISBN : ");
    fgets(livre.isbn, sizeof(livre.isbn), stdin);
    livre.isbn[strcspn(livre.isbn, "\n")] = '\0';

    printf("Titre : ");
    fgets(livre.titre, sizeof(livre.titre), stdin);
    livre.titre[strcspn(livre.titre, "\n")] = '\0';

    printf("ID Auteur : ");
    scanf("%d", &livre.idAuteur);
    fflush(stdin);

    printf("ID Categorie : ");
    scanf("%d", &livre.idCategorie);
    fflush(stdin);

    printf("Editeur : ");
    fgets(livre.editeur, sizeof(livre.editeur), stdin);
    livre.editeur[strcspn(livre.editeur, "\n")] = '\0';

    printf("Annee de publication : ");
    scanf("%d", &livre.anneePublication);
    fflush(stdin);

    printf("Langue : ");
    fgets(livre.langue, sizeof(livre.langue), stdin);
    livre.langue[strcspn(livre.langue, "\n")] = '\0';

    printf("Nombre de pages : ");
    scanf("%d", &livre.nombrePages);
    fflush(stdin);

    printf("Nombre d'exemplaires total : ");
    scanf("%d", &livre.nombreExemplairesTotal);
    fflush(stdin);

    livre.nombreExemplairesDisponibles = livre.nombreExemplairesTotal;

    printf("Emplacement : ");
    fgets(livre.emplacement, sizeof(livre.emplacement), stdin);
    livre.emplacement[strcspn(livre.emplacement, "\n")] = '\0';

    printf("Resume : ");
    fgets(livre.resume, sizeof(livre.resume), stdin);
    livre.resume[strcspn(livre.resume, "\n")] = '\0';

    strcpy(livre.dateAjout, "21/07/2026");

    return livre;
}
int supprimerLivre(int id) {
    if (livreExisteParId(id) == 0) {
        printf("Aucun livre trouve avec cet id.\n");
        return 0;
    }

    FILE *ancienFichier = fopen(FICHIER_LIVRES, "rb");
    FILE *nouveauFichier = fopen("DATABASE/BOOKS_TEMP.dat", "wb");

    if (ancienFichier == NULL || nouveauFichier == NULL) {
        printf("Erreur : impossible d'ouvrir les fichiers.\n");
        return 0;
    }

    Book temp;
    while (fread(&temp, sizeof(Book), 1, ancienFichier) == 1) {
        if (temp.id != id) {
            fwrite(&temp, sizeof(Book), 1, nouveauFichier);
        }
    }

    fclose(ancienFichier);
    fclose(nouveauFichier);

    remove(FICHIER_LIVRES);
    rename("DATABASE/BOOKS_TEMP.dat", FICHIER_LIVRES);

    printf("Livre supprime avec succes !\n");
    return 1;
}
