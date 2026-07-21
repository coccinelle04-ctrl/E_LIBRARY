#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/structureutilisateur.h"
#include "../include/contraintesdacces.h"
#include "../include/securitedesmotsdepasse.h"

int main() {
    printf("=== SYSTEME DE GESTION DES UTILISATEURS ===\n\n");

    char loginTest[50];
    User nouvelUtilisateur;

    // 1. Saisie du login et vérification des contraintes d'accès
    printf("Entrez un login (6 lettres majuscules) : ");
    if (scanf("%49s", loginTest) != 1) {
        printf("Erreur de saisie.\n");
        return 1;
    }

    if (!verifierFormatLogin(loginTest)) {
        printf("Erreur : Le login doit contenir exactement 6 lettres majuscules (ex: ADMINI).\n");
        return 1;
    }

    if (!verifierUniciteLogin(loginTest)) {
        printf("Erreur : Le login '%s' est deja utilise dans la base.\n", loginTest);
        return 1;
    }

    printf("-> Login valide et disponible !\n\n");

    // 2. Initialisation de la structure utilisateur
    initialiserUtilisateur(&nouvelUtilisateur, "kebe", "diarra", "769456136", 
                           "12 Rue de Paris", "diarrakebe@email.com", loginTest, "ETUDIANT");

    // 3. Sauvegarde dans le fichier binaire DATABASE/USERS.dat
    if (sauvegarderUtilisateur(&nouvelUtilisateur)) {
        printf("-> Utilisateur enregistre avec succes (ID : %d) !\n", nouvelUtilisateur.id);
    } else {
        printf("Erreur lors de la sauvegarde de l'utilisateur.\n");
        return 1;
    }
    

    return 0;
}
