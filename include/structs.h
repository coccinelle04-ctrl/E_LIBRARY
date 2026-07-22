
#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int id;
    char nomComplet[100];
    char nationalite[50];
    char dateNaissance[12];
    char biographie[300];
    int nombreLivresPublies;
} Author;

typedef struct {
    int id;
    char libelle[50];
    char description[200];
    char dateCreation[12];
} Category;

typedef struct {
    int id;
    char isbn[20];
    char titre[150];
    int idAuteur;
    int idCategorie;
    char editeur[100];
    int anneePublication;
    char langue[30];
    int nombrePages;
    int nombreExemplairesTotal;
    int nombreExemplairesDisponibles;
    char emplacement[50];
    char resume[300];
    char dateAjout[12];
} Book;

typedef struct {
    int id;
    int idUtilisateur;
    int idLivre;
    char dateReservation[12];
    char etat[15];
} Reservation;

typedef struct {
    int id;
    char numeroEmprunt[20];
    int idUtilisateur;
    int idLivre;
    char dateEmprunt[12];
    char dateRetourPrevue[12];
    char etat[15];
} Borrow;

typedef struct {
    int id;
    int idEmprunt;
    char dateRetourReelle[12];
    int nombreJoursRetard;
    int montantPenalite;
} Return;

typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    char telephone[20];
    char adresse[100];
    char email[100];
    char login[7];
    char motDePasse[100];
    char role[10];
    char etat[10];
    char dateCreation[12];
    char dateDerniereConnexion[12];
    int doitChangerMotDePasse;
} User;

typedef struct {
    int id;
    int idUtilisateur;
    int idEmprunt;
    int nombreJoursRetard;
    int montant;
    char date[12];
} Penalty;


#endif
