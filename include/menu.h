#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "structs.h"

void pause();
void creerPremierAdminSiBesoin();
int seConnecter(User *connecte);
void menuAuteurs(User connecte);
void menuCategories(User connecte);
void menuLivres(User connecte);
void menuEmprunts(User connecte);
void menuUtilisateurs(User connecte);
void menuPenalitesEtStats();
void menuAdmin(User connecte);
void menuUser(User connecte);
void lancerApplication();

#endif
