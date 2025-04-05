#include <stdio.h>
#include "gestion_etudiants.h"

void trierEtudiantsMerite(Etudiant VETU[], int SUIVANT[], int n, int *DEB) {
    *DEB = 0;  // Initialisation du debut à 0 (liste vide)
    SUIVANT[0] = 0;  // Dernier element pointe vers 0

    for (int i = 1; i <= n; i++) {
        if (*DEB == 0 || VETU[i].note > VETU[*DEB].note) {
            // Inserer au debut si la note est la plus elevee
            SUIVANT[i] = *DEB;
            *DEB = i;
        } else {
            // Trouver la bonne position en maintenant l'ordre decroissant
            int j = *DEB;
            while (SUIVANT[j] != 0 && VETU[SUIVANT[j]].note > VETU[i].note) {
                j = SUIVANT[j];
            }
            SUIVANT[i] = SUIVANT[j];
            SUIVANT[j] = i;
        }
    }
}
