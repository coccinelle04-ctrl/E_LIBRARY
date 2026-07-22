#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "authors.h"
#include "categories.h"
#include "books.h"
#include "reservations.h"
#include "Emprunt.h"
#include "Retour.h"
#include "contraintesdacces.h"
#include "securitedesmotsdepasse.h"
#include "structureutilisateur.h"
#include "penalites.h"
#include "tracabilites.h"
#include "statistiques.h"

/* ============================================================
   Fonction pause() : attend que l'utilisateur appuie sur une
   touche avant de continuer, en vidant le buffer clavier pour
   eviter que le message s'efface trop vite.
   ============================================================ */
void pause() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* on vide le buffer clavier */
    }
    printf("\nAppuyez sur une touche pour continuer...");
    getchar();
}

/* ============================================================
   Verifie s'il existe deja au moins un utilisateur. Si non,
   propose de creer le premier compte ADMIN (sinon personne ne
   pourrait jamais se connecter au tout premier lancement).
   ============================================================ */
void creerPremierAdminSiBesoin() {
    FILE *f = fopen("DATABASE/USERS.dat", "rb");
    if (f != NULL) {
        User test;
        int existeDeja = (fread(&test, sizeof(User), 1, f) == 1);
        fclose(f);
        if (existeDeja) {
            return;
        }
    }

    printf("========================================\n");
    printf(" Aucun utilisateur trouve. Creation du\n");
    printf(" premier compte ADMINISTRATEUR.\n");
    printf("========================================\n");

    char nom[50], prenom[50], telephone[20], adresse[100], email[100], login[7];
    User nouvelAdmin;

    printf("Nom : ");
    fgets(nom, sizeof(nom), stdin);
    nom[strcspn(nom, "\n")] = '\0';

    printf("Prenom : ");
    fgets(prenom, sizeof(prenom), stdin);
    prenom[strcspn(prenom, "\n")] = '\0';

    printf("Telephone : ");
    fgets(telephone, sizeof(telephone), stdin);
    telephone[strcspn(telephone, "\n")] = '\0';

    printf("Adresse : ");
    fgets(adresse, sizeof(adresse), stdin);
    adresse[strcspn(adresse, "\n")] = '\0';

    printf("Email : ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0';

    do {
        printf("Login (6 lettres majuscules) : ");
    fgets(login, sizeof(login), stdin);
    if (strchr(login, '\n') == NULL) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    }
    login[strcspn(login, "\n")] = '\0';
    if (validerNouveauLogin(login) == 0) {
            printf("Login invalide ou deja utilise, reessayez.\n");
        }
    } while (validerNouveauLogin(login) == 0);

    initialiserUtilisateur(&nouvelAdmin, nom, prenom, telephone, adresse, email, login, "ADMIN");
    sauvegarderUtilisateur(&nouvelAdmin);

    printf("\nCompte admin cree avec succes !\n");
    printf("Login : %s | Mot de passe par defaut : Library123\n", login);
    pause();
}

/* ============================================================
   Ecran de connexion. Retourne l'utilisateur connecte via le
   pointeur "connecte" si succes, sinon renvoie 0.
   ============================================================ */
int seConnecter(User *connecte) {
    char login[7];
    char motDePasse[50];
    char motDePasseCrypte[100];

    system("cls");
    printf("========================================\n");
    printf("         CONNEXION - E-LIBRARY\n");
    printf("========================================\n");

    printf("Login : ");
    fgets(login, sizeof(login), stdin);
    if (strchr(login, '\n') == NULL) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    }
    login[strcspn(login, "\n")] = '\0';

    printf("Mot de passe : ");
    fgets(motDePasse, sizeof(motDePasse), stdin);
    motDePasse[strcspn(motDePasse, "\n")] = '\0';

    User u;
    if (rechercherUtilisateurParLogin(login, &u) == 0) {
        printf("\nLogin ou mot de passe incorrect.\n");
        pause();
        return 0;
    }

    if (strcmp(u.etat, "BLOQUE") == 0) {
        printf("\nCe compte est bloque. Contactez un administrateur.\n");
        pause();
        return 0;
    }

    crypterMotDePasse(motDePasse, motDePasseCrypte);

    if (strcmp(u.motDePasse, motDePasseCrypte) != 0) {
        printf("\nLogin ou mot de passe incorrect.\n");
        pause();
        return 0;
    }

    /* Si premiere connexion : changement de mot de passe obligatoire */
    if (verifierPremiereConnexion(&u) == 1) {
        char nouveauMdp[50];
        printf("\nPremiere connexion detectee. Vous devez changer votre mot de passe.\n");
        printf("Nouveau mot de passe : ");
        fgets(nouveauMdp, sizeof(nouveauMdp), stdin);
        nouveauMdp[strcspn(nouveauMdp, "\n")] = '\0';

        changerMotDePasse(&u, nouveauMdp);
        modifierUtilisateurDansFichier(&u);
        printf("Mot de passe change avec succes !\n");
        pause();
    }

    /* Mise a jour de la date de derniere connexion (version simplifiee) */
    strcpy(u.dateDerniereConnexion, "connecte");
    modifierUtilisateurDansFichier(&u);

    enregistrerHistorique(u.login, "Connexion au systeme");

    *connecte = u;
    return 1;
}

/* ============================================================
   Sous-menu : Gestion des auteurs
   ============================================================ */
void menuAuteurs(User connecte) {
    int choix;
    do {
        system("cls");
        printf("--- GESTION DES AUTEURS ---\n");
        printf("1. Ajouter un auteur\n");
        printf("2. Afficher tous les auteurs\n");
        printf("3. Modifier un auteur\n");
        printf("4. Supprimer un auteur\n");
        printf("0. Retour\n");
        printf("Choix : ");
        scanf("%d", &choix);
        getchar();

            if (choix == 1) {
            ajouterAuteur();
            enregistrerHistorique(connecte.login, "Ajout d'un auteur");
        }
        else if (choix == 2) afficherTousAuteurs();
        else if (choix == 3) {
            modifierAuteur();
            enregistrerHistorique(connecte.login, "Modification d'un auteur");
        }
        else if (choix == 4) {
            supprimerAuteur();
            enregistrerHistorique(connecte.login, "Suppression d'un auteur");
        }

        if (choix != 0) pause();
    } while (choix != 0);
}

/* ============================================================
   Sous-menu : Gestion des categories
   ============================================================ */
void menuCategories(User connecte) {
    int choix;
    do {
        system("cls");
        printf("--- GESTION DES CATEGORIES ---\n");
        printf("1. Ajouter une categorie\n");
        printf("2. Afficher toutes les categories\n");
        printf("3. Modifier une categorie\n");
        printf("4. Supprimer une categorie\n");
        printf("0. Retour\n");
        printf("Choix : ");
        scanf("%d", &choix);
        getchar();

        if (choix == 1) {
            ajouterCategorie();
            enregistrerHistorique(connecte.login, "Ajout d'une categorie");
        }
        else if (choix == 2) afficherToutesCategories();
        else if (choix == 3) {
            modifierCategorie();
            enregistrerHistorique(connecte.login, "Modification d'une categorie");
        }
        else if (choix == 4) {
            supprimerCategorie();
            enregistrerHistorique(connecte.login, "Suppression d'une categorie");
        }

        if (choix != 0) pause();
    } while (choix != 0);
}

/* ============================================================
   Sous-menu : Gestion des livres et reservations
   ============================================================ */
void menuLivres(User connecte) {
    int choix;
    do {
        system("cls");
        printf("--- GESTION DES LIVRES ---\n");
        printf("1. Ajouter un livre\n");
        printf("2. Afficher tous les livres\n");
        printf("3. Supprimer un livre\n");
        printf("4. Afficher les reservations\n");
        printf("5. Creer une reservation\n");
        printf("0. Retour\n");
        printf("Choix : ");
        scanf("%d", &choix);
        getchar();

        if (choix == 1) {
            Book b = saisirLivre();
            if (ajouterLivre(b) == 1) {
                printf("\nLivre ajoute avec succes !\n");
                enregistrerHistorique(connecte.login, "Ajout d'un livre");
            } else {
                printf("\nEchec de l'ajout du livre.\n");
            }
        }
        else if (choix == 2) afficherTousLesLivres();
        else if (choix == 3) {
            int id;
            printf("Id du livre a supprimer : ");
            scanf("%d", &id);
            supprimerLivre(id);
            enregistrerHistorique(connecte.login, "Suppression d'un livre");
        }
        else if (choix == 4) afficherReservations();
        else if (choix == 5) {
            int idUser, idLivre;
            printf("Id utilisateur : ");
            scanf("%d", &idUser);
            printf("Id livre : ");
            scanf("%d", &idLivre);
            creerReservation(idUser, idLivre);
            enregistrerHistorique(connecte.login, "Creation d'une reservation");
        }

        if (choix != 0) pause();
    } while (choix != 0);
}

/* ============================================================
   Sous-menu : Gestion des emprunts et retours
   ============================================================ */
void menuEmprunts(User connecte) {
    int choix;
    do {
        system("cls");
        printf("--- GESTION DES EMPRUNTS ---\n");
        printf("1. Creer un emprunt\n");
        printf("2. Afficher tous les emprunts\n");
        printf("3. Retourner un livre\n");
        printf("0. Retour\n");
        printf("Choix : ");
        scanf("%d", &choix);
        getchar();

        if (choix == 1) {
            Borrow emp;
            if (saisirEmprunt(&emp) == 1) {
            enregistrerEmprunt(emp);
            genererRecuEmprunt(emp, connecte.login);
            enregistrerHistorique(connecte.login, "Creation d'un emprunt");
        } else {
            printf("\nEmprunt annule.\n");
        }
    }
        else if (choix == 2) afficherTousLesEmprunts();
        else if (choix == 3) retournerLivre();

        if (choix != 0) pause();
    } while (choix != 0);
}

/* ============================================================
   Sous-menu : Gestion des utilisateurs (reserve a l'admin)
   ============================================================ */
void menuUtilisateurs(User connecte) {
    int choix;
    do {
        system("cls");
        printf("--- GESTION DES UTILISATEURS ---\n");
        printf("1. Creer un utilisateur\n");
        printf("2. Afficher tous les utilisateurs\n");
        printf("0. Retour\n");
        printf("Choix : ");
        scanf("%d", &choix);
        getchar();

        if (choix == 1) {
            char nom[50], prenom[50], telephone[20], adresse[100], email[100], login[7], role[10];
            User u;

            printf("Nom : ");
            fgets(nom, sizeof(nom), stdin);
            nom[strcspn(nom, "\n")] = '\0';

            printf("Prenom : ");
            fgets(prenom, sizeof(prenom), stdin);
            prenom[strcspn(prenom, "\n")] = '\0';

            printf("Telephone : ");
            fgets(telephone, sizeof(telephone), stdin);
            telephone[strcspn(telephone, "\n")] = '\0';

            printf("Adresse : ");
            fgets(adresse, sizeof(adresse), stdin);
            adresse[strcspn(adresse, "\n")] = '\0';

            printf("Email : ");
            fgets(email, sizeof(email), stdin);
            email[strcspn(email, "\n")] = '\0';

            do {
                printf("Login (6 lettres majuscules) : ");
        fgets(login, sizeof(login), stdin);
        if (strchr(login, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        }
        login[strcspn(login, "\n")] = '\0';
        if (validerNouveauLogin(login) == 0)  {
                    printf("Login invalide ou deja utilise.\n");
                }
            } while (validerNouveauLogin(login) == 0);

            printf("Role (ADMIN ou USER) : ");
            fgets(role, sizeof(role), stdin);
            role[strcspn(role, "\n")] = '\0';

            initialiserUtilisateur(&u, nom, prenom, telephone, adresse, email, login, role);
            sauvegarderUtilisateur(&u);
            enregistrerHistorique(connecte.login, "Creation d'un utilisateur");
            printf("\nUtilisateur cree ! Mot de passe par defaut : Library123\n");
        }
        else if (choix == 2) afficherTousUtilisateurs();

        if (choix != 0) pause();
    } while (choix != 0);
}

/* ============================================================
   Sous-menu : Penalites, historique et statistiques
   ============================================================ */
void menuPenalitesEtStats() {
    int choix;
    do {
        system("cls");
        printf("--- PENALITES / HISTORIQUE / STATISTIQUES ---\n");
        printf("1. Afficher les penalites\n");
        printf("2. Afficher l'historique\n");
        printf("3. Generer le rapport journalier\n");
        printf("0. Retour\n");
        printf("Choix : ");
        scanf("%d", &choix);
        getchar();

        if (choix == 1) afficherPenalites();
        else if (choix == 2) afficherHistorique();
        else if (choix == 3) genererRapportJournalier();

        if (choix != 0) pause();
    } while (choix != 0);
}

/* ============================================================
   Menu principal ADMIN
   ============================================================ */
void menuAdmin(User connecte) {
    int choix;
    do {
        system("cls");
        printf("========================================\n");
        printf(" E-LIBRARY ISI DAKAR - Bienvenue %s\n", connecte.prenom);
        printf("========================================\n");
        printf("1. Gestion des auteurs\n");
        printf("2. Gestion des categories\n");
        printf("3. Gestion des livres\n");
        printf("4. Gestion des emprunts/retours\n");
        printf("5. Gestion des utilisateurs\n");
        printf("6. Penalites / Historique / Statistiques\n");
        printf("0. Deconnexion\n");
        printf("Choix : ");
        scanf("%d", &choix);
        getchar();

        if (choix == 1) menuAuteurs(connecte);
        else if (choix == 2) menuCategories(connecte);
        else if (choix == 3) menuLivres(connecte);
        else if (choix == 4) menuEmprunts(connecte);
        else if (choix == 5) menuUtilisateurs(connecte);
        else if (choix == 6) menuPenalitesEtStats();

    } while (choix != 0);
}

/* ============================================================
   Menu principal USER (lecteur)
   ============================================================ */
void menuUser(User connecte) {
    int choix;
    do {
        system("cls");
        printf("========================================\n");
        printf(" E-LIBRARY ISI DAKAR - Bienvenue %s\n", connecte.prenom);
        printf("========================================\n");
        printf("1. Afficher les livres\n");
        printf("2. Creer une reservation\n");
        printf("0. Deconnexion\n");
        printf("Choix : ");
        scanf("%d", &choix);
        getchar();

        if (choix == 1) {
            afficherTousLesLivres();
            pause();
        }
        else if (choix == 2) {
            int idLivre;
            printf("Id du livre a reserver : ");
            scanf("%d", &idLivre);
            creerReservation(connecte.id, idLivre);
            pause();
        }

    } while (choix != 0);
}

/* ============================================================
   Point d'entree du programme
   ============================================================ */
int main() {
    initBooks();
    creerPremierAdminSiBesoin();

    int continuer = 1;
    while (continuer) {
        User connecte;
        if (seConnecter(&connecte) == 1) {
            if (strcmp(connecte.role, "ADMIN") == 0) {
                menuAdmin(connecte);
            } else {
                menuUser(connecte);
            }
            enregistrerHistorique(connecte.login, "Deconnexion du systeme");
        }

        system("cls");
        printf("Voulez-vous vous reconnecter ? (1 = Oui, 0 = Quitter) : ");
        scanf("%d", &continuer);
        getchar();
    }

    printf("\nAu revoir !\n");
    return 0;
}
