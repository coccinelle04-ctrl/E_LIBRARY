#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/securitedesmotsdepasse.h"

void crypterMotDePasse(const char *motDePasseClair, char *motDePasseCrypte) {
    if (motDePasseClair == NULL || motDePasseCrypte == NULL) return;

    // Masque de chiffrement XOR basique
    char cle = 'K'; 
    int i = 0;
    
    while (motDePasseClair[i] != '\0') {
        motDePasseCrypte[i] = motDePasseClair[i] ^ cle;
        i++;
    }
    motDePasseCrypte[i] = '\0'; // Fin de chaîne
}

int verifierPremiereConnexion(const User *utilisateur) {
    if (utilisateur == NULL) return 0;
    return utilisateur->doitChangerMotDePasse;
}

int changerMotDePasse(User *utilisateur, const char *nouveauMotDePasse) {
    if (utilisateur == NULL || nouveauMotDePasse == NULL) return 0;

    // Cryptage du nouveau mot de passe
    crypterMotDePasse(nouveauMotDePasse, utilisateur->motDePasse);
    
    // Mise à jour du flag : ce n'est plus sa première connexion
    utilisateur->doitChangerMotDePasse = 0;

    return 1;
}
