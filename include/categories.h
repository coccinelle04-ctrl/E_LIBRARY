#ifndef CATEGORIES_H_INCLUDED
#define CATEGORIES_H_INCLUDED

#include "structs.h"

/* Ajoute une nouvelle categorie (demande les infos et enregistre dans le fichier) */
void ajouterCategorie();

/* Affiche toutes les categories enregistrees */
void afficherToutesCategories();

/* Cherche une categorie par son id, la renvoie dans "resultat" */
/* Retourne 1 si trouvee, 0 si non trouvee */
int rechercherCategorieParId(int id, Category *resultat);

/* Modifie une categorie existante */
void modifierCategorie();

/* Supprime une categorie */
void supprimerCategorie();

/* Verifie si une categorie existe (utile pour le module Livres) */
/* Retourne 1 si elle existe, 0 sinon */
int categoryExists(int id);

#endif // CATEGORIES_H_INCLUDED
