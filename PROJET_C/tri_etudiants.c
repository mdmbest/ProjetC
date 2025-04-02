//tri_etudiants.c
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


void supprimer_etudiant(Etudiant VETU[], int SUIVANT[], int *DEB, int n, int num) {
    int index = *DEB;   // Commence au début de la liste
    int precedent = 0;  // Aucun précédent au début

    // Chercher l'étudiant à supprimer
    while (index != 0 && VETU[index].num != num) {
        precedent = index;
        index = SUIVANT[index];  // Avancer dans la liste
    }

    if (index == 0) {
        printf("⚠️ Étudiant avec numéro %d non trouvé.\n", num);
        return;
    }

    // Suppression : mise à jour du chaînage
    if (precedent == 0) {
        // Cas où l'étudiant à supprimer est le premier
        *DEB = SUIVANT[index];
    } else {
        // Sauter l'étudiant à supprimer
        SUIVANT[precedent] = SUIVANT[index];
    }

    printf("✅ Étudiant avec numéro %d supprimé avec succès.\n", num);
}

