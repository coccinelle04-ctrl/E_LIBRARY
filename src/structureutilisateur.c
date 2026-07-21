#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/structureutilisateur.h"
#include "../include/securitedesmotsdepasse.h"

void initialiserUtilisateur(User *nouvelUser, const char *nom, const char *prenom, 
                            const char *telephone, const char *adresse, 
                            const char *email, const char *login, const char *role) {
    if (nouvelUser == NULL) return;

    strncpy(nouvelUser->nom, nom, sizeof(nouvelUser->nom) - 1);
    strncpy(nouvelUser->prenom, prenom, sizeof(nouvelUser->prenom) - 1);
    strncpy(nouvelUser->telephone, telephone, sizeof(nouvelUser->telephone) - 1);
    strncpy(nouvelUser->adresse, adresse, sizeof(nouvelUser->adresse) - 1);
    strncpy(nouvelUser->email, email, sizeof(nouvelUser->email) - 1);
    strncpy(nouvelUser->login, login, sizeof(nouvelUser->login) - 1);

    strncpy(nouvelUser->role, role, sizeof(nouvelUser->role) - 1);
    strncpy(nouvelUser->etat, "ACTIF", sizeof(nouvelUser->etat) - 1);

    crypterMotDePasse("Library123", nouvelUser->motDePasse);

    nouvelUser->doitChangerMotDePasse = 1; 

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(nouvelUser->dateCreation, sizeof(nouvelUser->dateCreation), "%d/%m/%Y", tm_info);
    strcpy(nouvelUser->dateDerniereConnexion, "Neant");
}

int sauvegarderUtilisateur(User *u) {
    FILE *fichier = fopen("DATABASE/USERS.dat", "ab+");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir DATABASE/USERS.dat\n");
        return 0;
    }

    User temporaire;
    int dernierId = 0;
    rewind(fichier);
    
    while (fread(&temporaire, sizeof(User), 1, fichier) == 1) {
        dernierId = temporaire.id;
    }
    
    u->id = dernierId + 1;

    fwrite(u, sizeof(User), 1, fichier);
    fclose(fichier);
    return 1;
}

int modifierUtilisateurDansFichier(const User *u) {
    FILE *fichier = fopen("DATABASE/USERS.dat", "r+b");
    if (fichier == NULL) {
        return 0;
    }

    User temporaire;
    long position;

    while (fread(&temporaire, sizeof(User), 1, fichier) == 1) {
        if (temporaire.id == u->id) {
            position = ftell(fichier) - sizeof(User);
            fseek(fichier, position, SEEK_SET);
            
            fwrite(u, sizeof(User), 1, fichier);
            fclose(fichier);
            return 1;
        }
    }

    fclose(fichier);
    return 0;
}
