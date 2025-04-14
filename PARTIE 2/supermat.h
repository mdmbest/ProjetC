#ifndef SUPERMATRICES_H
#define SUPERMATRICES_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int nl;       // Nombre de lignes
    int nc;       // Nombre de colonnes
    double **ligne; // Tableau de pointeurs vers les lignes
} *SUPERMRT;

// 2- Macros
#define acces(a, i, j) (a->ligne[i][j])

// Prototypes des fonctions
SUPERMRT aLLouerSupermat(int nL, int nc);
SUPERMRT superProduit(SUPERMRT a, SUPERMRT b);
void permuterLignes(SUPERMRT a, int i, int j);
SUPERMRT sousMatrice(SUPERMRT a, int Ll, int L2, int cl, int c2);
SUPERMRT matSupermat(double *m, int nLd, int ncd, int nLe, int nce);
void supermatMat(SUPERMRT sm, double *m, int nLd, int ncd);
int contiguite(SUPERMRT a);
void rendreSupermat(SUPERMRT sm);

#endif 



