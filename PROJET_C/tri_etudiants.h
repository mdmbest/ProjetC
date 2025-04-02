//tri_etudiants.h
#ifndef TRI_ETUDIANTS_H
#define TRI_ETUDIANTS_H

#define NBETU 100  // Nombre maximum d'étudiants

// Structure pour stocker les informations d'un étudiant
typedef struct {
    int num;
    char nom[50];
    float note;
} Etudiant;

// Déclarations des fonctions
void trier_etudiants(Etudiant VETU[], int SUIVANT[], int n, int *DEB);
void afficher_etudiants(Etudiant VETU[], int SUIVANT[], int DEB, int n);
void supprimer_etudiant(Etudiant VETU[], int SUIVANT[], int *DEB, int n, int num);

#endif
