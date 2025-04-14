#include <stdio.h>
#include <string.h>
#include "gestion_etudiants.h"

void afficherEtudiantsAlphabetique(Etudiant VETU[], int n) {
    // Tri alphabétique insensible à la casse
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcasecmp(VETU[i].nom, VETU[j].nom) > 0) { 
                Etudiant temp = VETU[i];
                VETU[i] = VETU[j];
                VETU[j] = temp;
            }
        }
    }

    // Affichage des entêtes
    printf("\n\t\t\t+-----------+----------------------+------------+");
    printf("\n\t\t\t|   ID      |        NOM           |    NOTE    |");
    printf("\n\t\t\t+-----------+----------------------+------------+");

    // Affichage des étudiants triés
    for (int i = 0; i < n; i++) {
        char id_str[10], note_str[10];
        snprintf(id_str, sizeof(id_str), "%d", VETU[i].num);
        snprintf(note_str, sizeof(note_str), "%.2f", VETU[i].note);
        char nom_trunc[21] = {0};
        strncpy(nom_trunc, VETU[i].nom, 20);

        printf("\n\t\t\t| %-9s | %-20s | %-10s |", id_str, nom_trunc, note_str);
    }

    printf("\n\t\t\t+-----------+----------------------+------------+\n");
}
