#include <stdio.h>
#include "gestion_etudiants.h"

void sauvegarderEtudiants(Etudiant VETU[], int n, char *fichier) {
    FILE *f = fopen(fichier, "w");
    if (!f) {
        printf("Erreur d'ouverture du fichier !\n");
        return;
    }

    for (int i = 1; i <= n; i++) {
        fprintf(f, "%d %s %.2f\n", VETU[i].num, VETU[i].nom, VETU[i].note);
    }

    fclose(f);
    printf("Sauvegarde reussie dans %s !\n", fichier);
}
