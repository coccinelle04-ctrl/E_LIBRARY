#ifndef AUTHORS_H_INCLUDED
#define AUTHORS_H_INCLUDED

#include "structs.h"

void ajouterAuteur();

void afficherTousAuteurs();

int rechercherAuteurParId(int id, Author *resultat);

void modifierAuteur();

void supprimerAuteur();

int authorExists(int id);

#endif
