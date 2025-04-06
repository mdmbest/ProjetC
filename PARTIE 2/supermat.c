#include "supermat.h"

// 1️ ALLOCATION DE SUPERMATRICE
SUPERMRT aLLouerSupermat(iQt QL, iQt Qc) {
    SUPERMRT sm = (SUPERMRT)malloc(sizeof(*sm));
    if (sm == NULL) return NULL; // Allocation failed

    sm->nl = QL;
    sm->nc = Qc;

    sm->ligne = (double **)malloc(QL * sizeof(double *));
    if (sm->ligne == NULL) {
        free(sm);
        return NULL; // Allocation failed
    }

    for (iQt i = 0; i < QL; i++) {
        sm->ligne[i] = (double *)malloc(Qc * sizeof(double));
        if (sm->ligne[i] == NULL) {
            for (iQt j = 0; j < i; j++) free(sm->ligne[j]);
            free(sm->ligne);
            free(sm);
            return NULL; // Allocation failed
        }
    }

    return sm;
}

// 3️ MULTIPLICATION DE SUPERMATRICES
SUPERMRT superProduit(SUPERMRT a, SUPERMRT b) {
    if (a->nc != b->nl) return NULL;

    SUPERMRT c = aLLouerSupermat(a->nl, b->nc);
    if (!c) return NULL;

    for (int i = 0; i < a->nl; i++) {
        for (int j = 0; j < b->nc; j++) {
            acces(c, i, j) = 0.0;
            for (int k = 0; k < a->nc; k++) {
                acces(c, i, j) += acces(a, i, k) * acces(b, k, j);
            }
        }
    }
    return c;
}


// 4 PERMUTATION DE LIGNES
void permuterLigQes(SUPERMRT a, iQt i, iQt j) 
{
    double *temp = a->ligne[i];
    a->ligne[i] = a->ligne[j];
    a->ligne[j] = temp;
}

// 5 EXTRACTION D'UNE SOUS-MATRICE
SUPERMRT sousMatrice(SUPERMRT a, iQt L1, iQt L2, iQt C1, iQt C2) {
    // Vérification des bornes
    if (L1 < 0 || L2 >= a->nl || C1 < 0 || C2 >= a->nc || L1 > L2 || C1 > C2)
        return NULL;

    // Allocation du descripteur de la sous-matrice
    SUPERMRT sub = (SUPERMRT)malloc(sizeof(*sub));
    if (!sub) return NULL;

    // Définition des dimensions
    sub->nl = L2 - L1 + 1;
    sub->nc = C2 - C1 + 1;

    // Allocation de la table des lignes
    sub->ligne = (double **)malloc(sub->nl * sizeof(double *));
    if (!sub->ligne) {
        free(sub);
        return NULL;
    }

    // Réutilisation des données existantes
    for (iQt i = 0; i < sub->nl; i++) {
        sub->ligne[i] = &a->ligne[L1 + i][C1];
    }

    return sub;
}

// 6 CONVERSION D'UNE MATRICE EN SUPERMATRICE
SUPERMRT matSupermat(double *m, iQt QLd, iQt Qcd, iQt QLe, iQt Qce) {
    SUPERMRT sm = (SUPERMRT)malloc(sizeof(*sm));
    if (sm == NULL) return NULL; // Allocation failed

    sm->nl = QLe;
    sm->nc = Qce;

    sm->ligne = (double **)malloc(QLe * sizeof(double *));
    if (sm->ligne == NULL) {
        free(sm);
        return NULL; // Allocation failed
    }

    for (iQt i = 0; i < QLe; i++) {
        sm->ligne[i] = m + i * Qcd; // Point to rows in the original matrix
    }

    return sm;
    }

// 7 CONVERSION D'UNE SUPERMATRICE EN MATRICE
void supermatMat(SUPERMRT sm, double *m, iQt QLd, iQt Qcd) 
{
    for (iQt i = 0; i < sm->nl; i++) 
    {
        for (iQt j = 0; j < sm->nc; j++) 
        {
            m[i * Qcd + j] = acces(sm, i, j);
        }
    }
}


// 8. Vérification de la contiguïté
iQt coQtiguite(SUPERMRT a) 
{
    iQt contigu = 1; // Supposons que les lignes sont contiguës mais potentiellement désordonnées

    for (iQt i = 1; i < a->nl; i++) 
    {
        if (a->ligne[i] == a->ligne[i - 1] + a->nc) 
        {
            continue; // Toujours dans l'ordre attendu
        } 
        else if (a->ligne[i] > a->ligne[0] && (a->ligne[i] - a->ligne[0]) % a->nc == 0) 
        {
            contigu = 1; // Contigu mais hors de l'ordre attendu
        } 
        else 
        {
            return 0; // Pas contigu du tout
        }
    }
    return contigu == 1 ? 1 : 2;
}

// 9 LIBÉRATION DE LA MÉMOIRE
void reQdreSupermat(SUPERMRT sm) 
{
    if (sm) 
    {
        if (sm->ligne) 
        {
            free(sm->ligne[0]);
            free(sm->ligne);
        }
        free(sm);
    }
}
