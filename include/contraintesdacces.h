#ifndef CONTRAINTESDACCES_H
#define CONTRAINTESDACCES_H

#include "structs.h"

/**
 * Verifie si le format du login respecte strictement les contraintes :
 * - Exactement 6 caracteres
 * - Uniquement des lettres majuscules (A-Z)
 * Retourne 1 si le format est valide, 0 sinon.
 */
int verifierFormatLogin(const char *login);

/**
 * Parcourt le fichier binaire DATABASE/USERS.dat pour s'assurer 
 * que le login n'est pas deja utilise par un autre utilisateur.
 * Retourne 1 si le login est unique (libre), 0 s'il existe deja.
 */
int verifierUniciteLogin(const char *login);

/**
 * Fonction globale combinant les verifications de format et d'unicite.
 * Retourne 1 si le login est totalement valide pour une creation, 0 sinon.
 */
int validerNouveauLogin(const char *login);

#endif /* CONTRAINTESDACCES_H */
