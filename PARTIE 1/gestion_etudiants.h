#ifndef GESTION_ETUDIANTS_H
#define GESTION_ETUDIANTS_H

#define NBETU 100  // Nombre maximum d'etudiants

// Structure pour stocker les informations d'un etudiant
typedef struct {
    int num;
    char nom[50];
    float note;
} Etudiant;

// Declarations des fonctions
void ajouterUnEtudiant(Etudiant VETU[], int *n);
void supprimerUnEtudiant(Etudiant VETU[], int *n, int num);
void sauvegarderEtudiants(Etudiant VETU[], int n, char *fichier);
void restaurerEtudiants(Etudiant VETU[], int *n, char *fichier);
void afficherEtudiantsMerite(Etudiant VETU[], int SUIVANT[], int DEB);
void afficherEtudiantsAlphabetique(Etudiant VETU[], int n);
void afficherEtudiantsAleatoire(Etudiant VETU[], int n);
void trierEtudiantsMerite(Etudiant VETU[], int SUIVANT[], int n, int *DEB);
#endif
