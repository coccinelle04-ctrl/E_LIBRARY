#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/contraintesdacces.h"

int verifierFormatLogin(const char *login) {
    if (login == NULL) return 0;

    if (strlen(login) != 6) {
        return 0;
    }

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
        return 1;
    }

    User temporaire;
    while (fread(&temporaire, sizeof(User), 1, fichier) == 1) {
        if (strcmp(temporaire.login, login) == 0) {
            fclose(fichier);
            return 0;
        }
    }

    fclose(fichier);
    return 1;
}

int validerNouveauLogin(const char *login) {
    return verifierFormatLogin(login) && verifierUniciteLogin(login);
}
