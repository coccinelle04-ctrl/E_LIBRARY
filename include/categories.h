#ifndef CATEGORIES_H_INCLUDED
#define CATEGORIES_H_INCLUDED

#include "structs.h"

void ajouterCategorie();

void afficherToutesCategories();

int rechercherCategorieParId(int id, Category *resultat);

void modifierCategorie();

void supprimerCategorie();

int categoryExists(int id);

#endif
