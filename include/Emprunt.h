#ifndef EMPRUNT_H
#define EMPRUNT_H
#include "structs.h"

void genererNumeroEmpruntManuel(Borrow *emp);
int saisirEmprunt(Borrow *emp);
void enregistrerEmprunt(Borrow emp);
void afficherTousLesEmprunts();
void genererRecuEmprunt(Borrow emp, const char *loginUtilisateur);

#endif
