#include <stdio.h>
#include <string.h>
#include "gestion_etudiants.h"

void supprimerUnEtudiant(Etudiant VETU[], int *n, int num) {
    int i, found = 0;

    // Parcours du tableau à partir de l'indice 1
    for (i = 1; i <= *n; i++) {
        if (VETU[i].num == num) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Étudiant non trouvé.\n");
        return;
    }

    // Décalage des éléments pour supprimer l'étudiant
    for (int j = i; j < *n; j++) {
        VETU[j] = VETU[j + 1];
    }

    (*n)--;

    printf("Etudiant supprime avec succes !\n");
}

