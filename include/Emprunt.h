#ifndef EMPRUNT_H
#define EMPRUNT_H
#include "structs.h"

void genererNumeroEmpruntManuel(Borrow *emp);
int saisirEmprunt(Borrow *emp); /* retourne 1 si l'emprunt est valide, 0 sinon */
void enregistrerEmprunt(Borrow emp);
void afficherTousLesEmprunts();
void genererRecuEmprunt(Borrow emp, const char *loginUtilisateur);

#endif
