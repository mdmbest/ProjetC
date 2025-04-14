#include <stdio.h>
#include <string.h>
#include "gestion_etudiants.h"

void afficherEtudiantsMerite(Etudiant VETU[], int SUIVANT[], int DEB) {
    printf("\n\t\t\t+-----------+----------------------+------------+");
    printf("\n\t\t\t|   ID      |        NOM           |    NOTE    |");
    printf("\n\t\t\t+-----------+----------------------+------------+");

    int index = DEB;
    while (index != 0) {
        // Formatage des champs pour un alignement correct
        char id_str[10];
        char note_str[10];
        
        snprintf(id_str, sizeof(id_str), "%d", VETU[index].num);
        snprintf(note_str, sizeof(note_str), "%.2f", VETU[index].note);
        
        // Tronquer le nom si trop long
        char nom_trunc[21] = {0};
        strncpy(nom_trunc, VETU[index].nom, 20);
        
        printf("\n\t\t\t| %-9s | %-20s | %-10s |", 
            id_str, nom_trunc, note_str);
        
        index = SUIVANT[index];
    }
    
    printf("\n\t\t\t+-----------+----------------------+------------+\n");
}

