#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gestion_etudiants.h"

void ajouterUnEtudiant(Etudiant VETU[], int *n) {
    if (*n >= 99) {
        printf("Nombre maximal d'etudiants atteint.\n");
        return;
    }

    int num;
    printf("Numero de l'etudiant : ");
    scanf("%d", &num);

    // Vérification de l’unicité du numéro
    for (int i = 1; i <= *n; i++) {
        if (VETU[i].num == num) {
            printf("Ce numero est deja attribue a un autre etudiant.\n");
            return;
        }
    }

    VETU[*n + 1].num = num;
    getchar(); // Consommer le '\n' laissé par scanf

    printf("Nom complet de l'etudiant : ");
    fgets(VETU[*n + 1].nom, sizeof(VETU[*n + 1].nom), stdin);

    // Supprimer le retour à la ligne à la fin si présent
    size_t len = strlen(VETU[*n + 1].nom);
    if (len > 0 && VETU[*n + 1].nom[len - 1] == '\n') {
        VETU[*n + 1].nom[len - 1] = '\0';
    }

    printf("Note de l'etudiant : ");
    scanf("%f", &VETU[*n + 1].note);

    (*n)++;
    printf("Etudiant ajoute avec succes !\n");
}
