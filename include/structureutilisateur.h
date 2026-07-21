#ifndef STRUCTUREUTILISATEUR_H
#define STRUCTUREUTILISATEUR_H

#include "structs.h"

/**
 * Initialise un nouvel utilisateur avec les informations de base.
 * Applique le mot de passe par defaut "Library123" et configure
 * doitChangerMotDePasse a 1.
 */
void initialiserUtilisateur(User *nouvelUser, const char *nom, const char *prenom, 
                            const char *telephone, const char *adresse, 
                            const char *email, const char *login, const char *role);

/**
 * Enregistre un utilisateur a la fin du fichier binaire DATABASE/USERS.dat.
 * Genere l'ID auto-incremente avant l'ecriture.
 * Retourne 1 si succes, 0 en cas d'erreur.
 */
int sauvegarderUtilisateur(User *u);

/**
 * Met a jour un utilisateur existant dans le fichier DATABASE/USERS.dat
 * en utilisant son ID pour le retrouver via fseek.
 * Retourne 1 si succes, 0 en cas d'erreur.
 */
int modifierUtilisateurDansFichier(const User *u);

#endif /* STRUCTUREUTILISATEUR_H */
