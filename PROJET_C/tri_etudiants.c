#include <stdio.h>
#include "tri_etudiants.h"

void trier_etudiants(Etudiant VETU[], int SUIVANT[], int n, int *DEB) {
    *DEB = 0;  // Initialisation du début à 0 (liste vide)
    SUIVANT[0] = 0;  // Dernier élément pointe vers 0

    for (int i = 1; i <= n; i++) {
        if (*DEB == 0 || VETU[i].note > VETU[*DEB].note) {
            // Insérer au début si la note est la plus élevée
            SUIVANT[i] = *DEB;
            *DEB = i;
        } else {
            // Trouver la bonne position en maintenant l'ordre décroissant
            int j = *DEB;
            while (SUIVANT[j] != 0 && VETU[SUIVANT[j]].note > VETU[i].note) {
                j = SUIVANT[j];
            }
            SUIVANT[i] = SUIVANT[j];
            SUIVANT[j] = i;
        }
    }
}
