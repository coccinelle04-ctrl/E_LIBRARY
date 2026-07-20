/*
 * ============================================================
 *  structs.h
 *  Fichier COMMUN a toute l'equipe - Projet E-LIBRARY ISI DAKAR
 * ============================================================
 *  Ce fichier contient TOUTES les structures utilisees dans le
 *  projet. Chaque membre doit inclure ce fichier dans son .c
 *  avec : #include "structs.h"
 *
 *  IMPORTANT : Ne modifiez pas une structure qui n'est pas la
 *  votre sans en parler au reste de l'equipe, sinon ca casse
 *  le travail des autres !
 * ============================================================
 */

#ifndef STRUCTS_H
#define STRUCTS_H

/* ------------------------------------------------------------
   1. AUTEURS (Massamba)
------------------------------------------------------------ */
typedef struct {
    int id;                      /* id auto-incremente */
    char nomComplet[100];
    char nationalite[50];
    char dateNaissance[12];      /* format "JJ/MM/AAAA" */
    char biographie[300];
    int nombreLivresPublies;
} Author;


/* ------------------------------------------------------------
   2. CATEGORIES (Massamba)
------------------------------------------------------------ */
typedef struct {
    int id;
    char libelle[50];
    char description[200];
    char dateCreation[12];       /* format "JJ/MM/AAAA" */
} Category;


/* ------------------------------------------------------------
   3. LIVRES (Fatou Ngom)
------------------------------------------------------------ */
typedef struct {
    int id;
    char isbn[20];                       /* unique */
    char titre[150];
    int idAuteur;                        /* doit exister dans AUTHORS.dat */
    int idCategorie;                     /* doit exister dans CATEGORIES.dat */
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


/* ------------------------------------------------------------
   4. RESERVATIONS (Fatou Ngom)
------------------------------------------------------------ */
typedef struct {
    int id;
    int idUtilisateur;
    int idLivre;
    char dateReservation[12];
    char etat[15];   /* "EN_ATTENTE", "DISPONIBLE" ou "ANNULEE" */
} Reservation;


/* ------------------------------------------------------------
   5. EMPRUNTS (Fatou Seck)
------------------------------------------------------------ */
typedef struct {
    int id;
    char numeroEmprunt[20];   /* format "EMP_AAAAMMJJHHMMSS" */
    int idUtilisateur;
    int idLivre;
    char dateEmprunt[12];
    char dateRetourPrevue[12];
    char etat[15];   /* "EN_COURS", "RETOURNE" ou "EN_RETARD" */
} Borrow;


/* ------------------------------------------------------------
   6. RETOURS (Fatou Seck)
------------------------------------------------------------ */
typedef struct {
    int id;
    int idEmprunt;
    char dateRetourReelle[12];
    int nombreJoursRetard;
    int montantPenalite;   /* en FCFA */
} Return;


/* ------------------------------------------------------------
   7. UTILISATEURS (Diarra)
------------------------------------------------------------ */
typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    char telephone[20];
    char adresse[100];
    char email[100];
    char login[7];              /* 6 lettres majuscules + '\0' */
    char motDePasse[100];       /* stocke crypte */
    char role[10];               /* "ADMIN" ou "USER" */
    char etat[10];                /* "ACTIF" ou "BLOQUE" */
    char dateCreation[12];
    char dateDerniereConnexion[12];
    int doitChangerMotDePasse;   /* 1 = oui (premiere connexion), 0 = non */
} User;


/* ------------------------------------------------------------
   8. PENALITES (Arame Gueye)
------------------------------------------------------------ */
typedef struct {
    int id;
    int idUtilisateur;
    int idEmprunt;
    int nombreJoursRetard;
    int montant;      /* en FCFA */
    char date[12];
} Penalty;


#endif
