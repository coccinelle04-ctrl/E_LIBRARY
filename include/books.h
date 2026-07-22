#ifndef BOOKS_H_INCLUDED
#define BOOKS_H_INCLUDED
#include "structs.h"

int initBooks();
int isbnExiste(char* isbn);
int livreExisteParId(int id);
int ajouterLivre(Book livre);
int rechercheLivreParIsbn(char *isbn, Book *resultat);
int rechercheLivreParId(int id, Book *resultat);
void afficherTousLesLivres();
int mettreAJourStock(int idLivre, int qnt);
Book saisirLivre();
int supprimerLivre(int id);

#endif

