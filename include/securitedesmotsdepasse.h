#ifndef SECURITEDESMOTSDEPASSE_H
#define SECURITEDESMOTSDEPASSE_H

#include "structs.h"

/**
 * Prend un mot de passe en clair et genere sa version cryptee
 * avant l'ecriture binaire sur le disque.
 */
void crypterMotDePasse(const char *motDePasseClair, char *motDePasseCrypte);

/**
 * Verifie si l'utilisateur doit changer son mot de passe (premiere connexion).
 * Retourne 1 si c'est sa premiere connexion, 0 sinon.
 */
int verifierPremiereConnexion(const User *utilisateur);

/**
 * Permet a un utilisateur de modifier son mot de passe.
 * Met a jour le champ dans la structure et passe doitChangerMotDePasse a 0.
 */
int changerMotDePasse(User *utilisateur, const char *nouveauMotDePasse);

#endif /* SECURITEDESMOTSDEPASSE_H */
