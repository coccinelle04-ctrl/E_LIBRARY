#ifndef STRUCTUREUTILISATEUR_H
#define STRUCTUREUTILISATEUR_H

#include "structs.h"


void initialiserUtilisateur(User *nouvelUser, const char *nom, const char *prenom,
                            const char *telephone, const char *adresse,
                            const char *email, const char *login, const char *role);
int sauvegarderUtilisateur(User *u);
int modifierUtilisateurDansFichier(const User *u);
int userExists(int id);
int rechercherUtilisateurParId(int id, User *resultat);
int rechercherUtilisateurParLogin(const char *login, User *resultat);
void afficherTousUtilisateurs();

#endif
