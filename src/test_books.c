#include <stdio.h>
#include "books.h"

int main() {
    Book b = saisirLivre();
    ajouterLivre(b);
    printf("\nLivre ajoute avec succes !\n");
    return 0;
}
