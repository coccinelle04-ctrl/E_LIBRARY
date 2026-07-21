#ifndef AUTHORS_H_INCLUDED
#define AUTHORS_H_INCLUDED

#include "structs.h"

/* Ajoute un nouvel auteur (demande les infos et enregistre dans le fichier) */
void ajouterAuteur();

/* Affiche tous les auteurs enregistres */
void afficherTousAuteurs();

/* Cherche un auteur par son id, le renvoie dans "resultat" */
/* Retourne 1 si trouve, 0 si non trouve */
int rechercherAuteurParId(int id, Author *resultat);

/* Modifie un auteur existant */
void modifierAuteur();

/* Supprime un auteur (uniquement si aucun livre ne lui est associe) */
void supprimerAuteur();

/* Verifie si un auteur existe (utile pour le module Livres) */
/* Retourne 1 si il existe, 0 sinon */
int authorExists(int id);

#endif // AUTHORS_H_INCLUDED
