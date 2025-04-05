#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gestion_etudiants.h"

#define MAX_ETUDIANTS 99

void afficherAccueil() {
    printf("\t\t\t+------------------------------------------------------+\n");
    printf("\t\t\t|         BIENVENUE DANS L'APPLICATION DE              |\n");
    printf("\t\t\t|            GESTION DES ETUDIANTS                     |\n");
    printf("\t\t\t+------------------------------------------------------+\n");
}

void afficherMenuPrincipal() {
    printf("\n\t\t\t+------------------ MENU PRINCIPAL -------------------+\n");
    printf("\t\t\t| 1. Ajouter un etudiant                              |\n");
    printf("\t\t\t| 2. Supprimer un etudiant                            |\n");
    printf("\t\t\t| 3. Sauvegarder les donnees                          |\n");
    printf("\t\t\t| 4. Restaurer les donnees                            |\n");
    printf("\t\t\t| 5. Afficher les etudiants                           |\n");
    printf("\t\t\t| 0. Quitter l'application                            |\n");
    printf("\t\t\t+-----------------------------------------------------+\n");
}

void afficherSousMenuAffichage() {
    printf("\n\t\t\t+------------- AFFICHAGE DES ETUDIANTS --------------+\n");
    printf("\t\t\t| a. Par ordre de merite                             |\n");
    printf("\t\t\t| b. Par ordre alphabetique                          |\n");
    printf("\t\t\t| c. De maniere aleatoire                            |\n");
    printf("\t\t\t| x. Retour au menu principal                        |\n");
    printf("\t\t\t+----------------------------------------------------+\n");
}

char demanderConfirmation(const char *message) {
    char reponse[10];

    // Vider le buffer résiduel pour éviter l'affichage de la question deux fois
    while (getchar() != '\n');

    do {
        printf("%s (oui/non) : ", message);
        fgets(reponse, sizeof(reponse), stdin);
        reponse[strcspn(reponse, "\n")] = '\0'; // Supprime le saut de ligne
        for (int i = 0; reponse[i]; i++) {
            reponse[i] = tolower(reponse[i]);
        }
    } while (strcmp(reponse, "oui") != 0 && strcmp(reponse, "non") != 0);

    return (strcmp(reponse, "oui") == 0) ? 'o' : 'n';
}

int main() {
    Etudiant VETU[NBETU];
    int SUIVANT[NBETU];
    int n = 0, DEB = 0;
    char fichier[] = "etudiants.txt";

    int choix;
    char sousChoix;

    afficherAccueil();

    do {
        afficherMenuPrincipal();
        printf("Votre choix : ");
        
        if (scanf("%d", &choix) != 1) {
            while (getchar() != '\n'); // vider le buffer d'entree
            printf("Entree invalide. Veuillez entrer un nombre valide.\n");
            continue;
        }
        while (getchar() != '\n'); // vider correctement le buffer

        switch (choix) {
            case 1:
                if (n >= MAX_ETUDIANTS) {
                    printf("Nombre maximal d'etudiants atteint !\n");
                } else {
                    ajouterUnEtudiant(VETU, &n);
                    while (n < MAX_ETUDIANTS && demanderConfirmation("Voulez-vous ajouter un autre etudiant ?") == 'o') {
                        ajouterUnEtudiant(VETU, &n);
                    }
                }
                break;

            case 2:
                if (n == 0) {
                    printf("Aucun etudiant a supprimer !\n");
                } else {
                    do {
                        int num;
                        printf("Numero de l'etudiant a supprimer : ");
                        if (scanf("%d", &num) != 1) {
                            while (getchar() != '\n');
                            printf("Entree invalide. Veuillez entrer un nombre valide.\n");
                            continue;
                        }
                        while (getchar() != '\n');
                        supprimerUnEtudiant(VETU, &n, num);
                    } while (n > 0 && demanderConfirmation("Voulez-vous supprimer un autre etudiant ?") == 'o');
                }
                break;

            case 3:
                sauvegarderEtudiants(VETU, n, fichier);
                break;

            case 4:
                restaurerEtudiants(VETU, &n, fichier);
                break;

            case 5:
                do {
                    afficherSousMenuAffichage();
                    printf("Choisissez une option : ");
                    if (scanf(" %c", &sousChoix) != 1) {
                        while (getchar() != '\n');
                        printf("Entree invalide. Veuillez choisir une option valide.\n");
                        continue;
                    }
                    while (getchar() != '\n');

                    switch (sousChoix) {
                        case 'a':
                            trierEtudiantsMerite(VETU, SUIVANT, n, &DEB);
                            afficherEtudiantsMerite(VETU, SUIVANT, DEB);
                            break;
                        case 'b':
                            afficherEtudiantsAlphabetique(VETU, n);
                            break;
                        case 'c':
                            afficherEtudiantsAleatoire(VETU, n);
                            break;
                        case 'x':
                            break;
                        default:
                            printf("Option invalide, veuillez reessayer.\n");
                    }
                } while (sousChoix != 'x');
                break;

            case 0:
                printf("Merci d'avoir utilise l'application. A bientot !\n");
                break;

            default:
                printf("Option invalide, veuillez reessayer !\n");
        }

        if (choix != 0) {
            printf("\nAppuyez sur Entree pour continuer...");
            getchar();
        }

    } while (choix != 0);

    return 0;
}
