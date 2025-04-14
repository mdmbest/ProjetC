#include "supermat.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//vous faites gcc main.c supermat.c -o programme.exe pour exécuter le programme

void afficherSupermat(SUPERMRT sm) {
    for (int i = 0; i < sm->nl; i++) {
        for (int j = 0; j < sm->nc; j++) {
            printf("%.2f ", acces(sm, i, j)); //sm[i][j]
        }
        printf("\n");
    }
}

int main() {
    // Création et initialisation d'une supermatrice
    int ligne = 3, colonne = 3;  //3*3
    SUPERMRT A = aLLouerSupermat(ligne, colonne);
    
    if (A == NULL) {
        printf("Échec d'allocation de la matrice A\n");
        return 1;
    }

    // Remplissage de la matrice A
    printf("Matrice A :\n");
    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < colonne; j++) {
            acces(A, i, j) = (i + 1) * (j + 1);
        }
    }
    afficherSupermat(A);

    // Création d'une deuxième super matrice B pour le produit
    SUPERMRT B = aLLouerSupermat(colonne, ligne);
    if (B == NULL) {
        printf("Échec d'allocation de la matrice B\n");
        rendreSupermat(A);
        return 1;
    }

    // Remplissage de la matrice B
    printf("\nMatrice B :\n");
    for (int i = 0; i < colonne; i++) {
        for (int j = 0; j < ligne; j++) {
            acces(B, i, j) = (i + 1) + (j + 1);
        }
    }
    afficherSupermat(B);

    // Produit de A et B
    SUPERMRT C = superProduit(A, B);
    if (C == NULL) {
        printf("Échec du produit matriciel.\n");
    } else {
        printf("\nProduit A * B :\n");
        afficherSupermat(C);
        rendreSupermat(C);
    }

    // Permutation de lignes
    printf("\nPermutation des lignes 0 et 1 dans A :\n");
    permuterLignes(A, 0, 1);
    afficherSupermat(A);

    // Extraction d'une sous-matrice
    printf("\nSous-matrice de A (0,1) -> (0,2) :\n");
    SUPERMRT subA = sousMatrice(A, 0, 1, 0, 2);
    if (subA) {
        afficherSupermat(subA);
        rendreSupermat(subA);
    } else {
        printf("Échec de l'extraction de sous-matrice\n");
    }

    // Vérification de la contiguïté
    printf("\nVérification de la contiguïté de A : %d\n", contiguite(A));

    // TEST DE CONVERSION MATRICE <-> SUPERMATRICE
    printf("\nTest conversion matrice -> supermatrice -> matrice\n");

    double matrice[] = {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    // Conversion matrice → supermatrice
    SUPERMRT SM = matSupermat(matrice, 3, 3, 3, 3);
    if (SM == NULL) {
        printf("Échec de la conversion matrice -> supermatrice\n");
    } else 
    {
        printf("Supermatrice SM (à partir d'un tableau) :\n");
        afficherSupermat(SM);
    }

    // Conversion supermatrice → matrice
    double m_resultat[9] = {0};
    supermatMat(SM, m_resultat, 3, 3);

    printf("\nMatrice reconstruite à partir de la supermatrice :\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%.2f ", m_resultat[i * 3 + j]);
        }
        printf("\n");
    }

    // Libération mémoire
    rendreSupermat(SM);
    rendreSupermat(A);
    rendreSupermat(B);

    return 0;
}
