#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gestion_etudiants.h"

void afficherEtudiantsAleatoire(Etudiant VETU[], int n) {
    int indices[n + 1]; // Assez d'espace pour les indices 1 à n
    for (int i = 1; i <= n; i++) {
        indices[i] = i;
    }

    // Mélange de Fisher-Yates en partant de l'indice 1
    srand(time(NULL));
    for (int i = n; i > 1; i--) {
        int j = 1 + rand() % (i); // entre 1 et i
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    printf("\n\t\t\t+-----------+----------------------+------------+");
    printf("\n\t\t\t|   ID      |        NOM           |    NOTE    |");
    printf("\n\t\t\t+-----------+----------------------+------------+");

    for (int i = 1; i <= n; i++) {
        int idx = indices[i];
        char id_str[10], note_str[10];
        snprintf(id_str, sizeof(id_str), "%d", VETU[idx].num);
        snprintf(note_str, sizeof(note_str), "%.2f", VETU[idx].note);
        char nom_trunc[21] = {0};
        strncpy(nom_trunc, VETU[idx].nom, 20);

        printf("\n\t\t\t| %-9s | %-20s | %-10s |", id_str, nom_trunc, note_str);
    }

    printf("\n\t\t\t+-----------+----------------------+------------+\n");
}
