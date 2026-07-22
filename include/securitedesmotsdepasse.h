#ifndef SECURITEDESMOTSDEPASSE_H
#define SECURITEDESMOTSDEPASSE_H

#include "structs.h"

void crypterMotDePasse(const char *motDePasseClair, char *motDePasseCrypte);
int verifierPremiereConnexion(const User *utilisateur);
int changerMotDePasse(User *utilisateur, const char *nouveauMotDePasse);

#endif
