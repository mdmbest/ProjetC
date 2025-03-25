#include <stdio.h>
#include "tri_etudiants.h"

int main() {
    int n;  // Nombre d'étudiants
    Etudiant VETU[NBETU];  // Tableau des étudiants
    int SUIVANT[NBETU + 1];  // Chaînage
    int DEB;  // Indice du premier étudiant classé

    // 📌 Saisie du nombre d'étudiants
    printf("Entrez le nombre d'étudiants : ");
    scanf("%d", &n);

    // 📌 Saisie des informations des étudiants
    for (int i = 1; i <= n; i++) {
        printf("Étudiant %d :\n", i);
        printf("Numéro : ");
        scanf("%d", &VETU[i].num);
        printf("Nom : ");
        scanf("%s", VETU[i].nom);
        printf("Note : ");
        scanf("%f", &VETU[i].note);
    }

    // 📌 Tri des étudiants avec le tableau SUIVANT
    trier_etudiants(VETU, SUIVANT, n, &DEB);

    // 📌 Affichage des étudiants triés
    afficher_etudiants(VETU, SUIVANT, DEB, n);

    return 0;
}
