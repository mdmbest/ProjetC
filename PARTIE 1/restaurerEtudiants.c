#include <stdio.h>
#include "gestion_etudiants.h"

void restaurerEtudiants(Etudiant VETU[], int *n, char *fichier) {
    FILE *f = fopen(fichier, "r");
    if (!f) {
        printf("Erreur d'ouverture du fichier !\n");
        return;
    }

    int i = 1; // Commence à 1
    while (fscanf(f, "%d;%[^;];%f\n", &VETU[i].num, VETU[i].nom, &VETU[i].note) == 3) {
        i++;
    }

    *n = i - 1;
    fclose(f);
    printf("Restauration réussie depuis %s !\n", fichier);
}
