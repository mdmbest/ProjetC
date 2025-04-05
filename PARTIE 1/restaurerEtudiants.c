#include <stdio.h>
#include "gestion_etudiants.h"

void restaurerEtudiants(Etudiant VETU[], int *n, char *fichier) {
    FILE *f = fopen(fichier, "r");
    if (!f) {
        printf("Erreur d'ouverture du fichier !\n");
        return;
    }

    int i = 1; // on commence à l'indice 1
    while (fscanf(f, "%d %s %f", &VETU[i].num, VETU[i].nom, &VETU[i].note) != EOF) {
        i++;
    }

    *n = i - 1; // nombre réel d'étudiants restaurés
    fclose(f);
    printf("Restauration reussie depuis %s !\n", fichier);
}
