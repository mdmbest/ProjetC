#include <stdio.h>
#include "tri_etudiants.h"

void afficher_menu() {
    printf("\n=== MENU ===\n");
    printf("1. Afficher la liste des étudiants\n");
    printf("2. Supprimer un étudiant\n");
    printf("3. Quitter\n");
    printf("Entrez votre choix : ");
}

int main() {
    int n;  
    Etudiant VETU[NBETU];  
    int SUIVANT[NBETU];  
    int DEB;  

    // 📌 Saisie du nombre d'étudiants
    printf("Entrez le nombre d'étudiants : ");
    scanf("%d", &n);

    // 📌 Saisie des informations des étudiants
    for (int i = 1; i <= n; i++) {  // On commence à 1 pour respecter la structure en liste chaînée
        printf("\nÉtudiant %d :\n", i);
        printf("Numéro : ");
        scanf("%d", &VETU[i].num);
        printf("Nom : ");
        scanf("%s", VETU[i].nom);
        printf("Note : ");
        scanf("%f", &VETU[i].note);
    }

    // 📌 Tri des étudiants
    trier_etudiants(VETU, SUIVANT, n, &DEB);

    int choix;
    do {
        afficher_menu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:  // Afficher les étudiants
                afficher_etudiants(VETU, SUIVANT, DEB, n);
                break;

            case 2:  // Supprimer un étudiant
                {
                    int num_a_supprimer;
                    printf("Entrez le numéro de l'étudiant à supprimer : ");
                    scanf("%d", &num_a_supprimer);
                    supprimer_etudiant(VETU, SUIVANT, &DEB, n, num_a_supprimer);
                    printf("\nListe après suppression :\n");
                    afficher_etudiants(VETU, SUIVANT, DEB, n);
                }
                break;

            case 3:  // Quitter
                printf("Merci d'avoir utilisé le programme.\n");
                break;

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 3);

    return 0;
}
