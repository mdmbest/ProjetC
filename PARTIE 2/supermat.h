#ifndef SUPERMATRICES_H
#define SUPERMATRICES_H

#include <stdlib.h>
#include <stdio.h>

typedef unsigned int iQt;

typedef struct {
    iQt nl;       // Nombre de lignes
    iQt nc;       // Nombre de colonnes
    double **ligne; // Tableau de pointeurs vers les lignes
} *SUPERMRT;

// 2- Macros
#define acces(a, i, j) (a->ligne[i][j])

// Prototypes des fonctions
SUPERMRT aLLouerSupermat(iQt QL, iQt Qc);
SUPERMRT superProduit(SUPERMRT a, SUPERMRT b);
void permuterLigQes(SUPERMRT a, iQt i, iQt j);
SUPERMRT sousMatrice(SUPERMRT a, iQt Ll, iQt L2, iQt cl, iQt c2);
SUPERMRT matSupermat(double *m, iQt QLd, iQt Qcd, iQt QLe, iQt Qce);
void supermatMat(SUPERMRT sm, double *m, iQt QLd, iQt Qcd);
iQt coQtiguite(SUPERMRT a);
void reQdreSupermat(SUPERMRT sm);

#endif // SUPERMATRICES_H
