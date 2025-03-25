#include <stdio.h>
#include "tri_etudiants.h"

void afficher_etudiants(Etudiant VETU[], int SUIVANT[], int DEB, int n) {
    printf("\n========================================================\n");
    printf("      🏆 CLASSEMENT DES ÉTUDIANTS PAR ORDRE DE MÉRITE 🏆  \n");
    printf("========================================================\n");
    printf("| %-4s | %-20s | %-6s |\n", "N°", "Nom", "Note");
    printf("--------------------------------------------------------\n");

    int index = DEB;
    while (index != 0) {
        printf("| %-4d | %-20s | %-6.2f |\n", 
               VETU[index].num, VETU[index].nom, VETU[index].note);
        index = SUIVANT[index];  // Passer au suivant
    }

    printf("========================================================\n");
    printf("🎓 Félicitations aux meilleurs étudiants ! 🎓\n");
}
