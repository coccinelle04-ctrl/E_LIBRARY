#ifndef PENALITES_H_INCLUDED
#define PENALITES_H_INCLUDED

#include "structs.h"

int genererIdPenalite();

int calculerMontantPenalite(int joursRetard);

void ajouterPenalite(int idUtilisateur,
                     int idEmprunt,
                     int joursRetard);

void afficherPenalites();

int nombrePenalites();

#endif
