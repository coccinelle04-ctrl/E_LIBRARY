#ifndef RESERVATIONS_H_INCLUDED
#define RESERVATIONS_H_INCLUDED
#include "structs.h"

int initReservations();
int creerReservation(int idUtilisateur , int idLivre);
int existeReservationEnAttente(int idLivre);
int passerReservationDisponible(int idLivre);
int annulerReservation(int id);
void afficherReservations();


#endif // RESERVATIONS_H_INCLUDED
