#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/contraintesdacces.h"

int verifierFormatLogin(const char *login) {
    if (login == NULL) return 0;

    // Doit faire exactement 6 caractères
    if (strlen(login) != 6) {
        return 0;
    }

    // Doit être uniquement composé de majuscules (A-Z)
    for (int i = 0; i < 6; i++) {
        if (!isupper((unsigned char)login[i])) {
            return 0;
        }
    }

    return 1;
}

int verifierUniciteLogin(const char *login) {
    if (login == NULL) return 0;

    FILE *fichier = fopen("DATABASE/USERS.dat", "rb");
    if (fichier == NULL) {
        return 1; // Si la base n'existe pas encore, le login est forcément libre
    }

    User temporaire;
    while (fread(&temporaire, sizeof(User), 1, fichier) == 1) {
        if (strcmp(temporaire.login, login) == 0) {
            fclose(fichier);
            return 0; // Login déjà pris
        }
    }

    fclose(fichier);
    return 1; // Login libre
}

int validerNouveauLogin(const char *login) {
    return verifierFormatLogin(login) && verifierUniciteLogin(login);
}
