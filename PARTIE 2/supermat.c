#include "supermat.h"

// 1️ ALLOCATION DE SUPERMATRICE
SUPERMRT aLLouerSupermat(int nL, int nc) {
    SUPERMRT sm = (SUPERMRT)malloc(sizeof(*sm));
    if (sm == NULL) return NULL; // L'allocation a échoué

    sm->nl = nL;
    sm->nc = nc;

    sm->ligne = (double **)malloc(nL * sizeof(double *));
    if (sm->ligne == NULL) {
        free(sm);
        return NULL; // L'allocation a échoué
    }

    for (int i = 0; i < nL; i++) {
        sm->ligne[i] = (double *)malloc(nc * sizeof(double));
        if (sm->ligne[i] == NULL) {
            for (int j = 0; j < i; j++) free(sm->ligne[j]);
            free(sm->ligne);
            free(sm);
            return NULL; // L'allocation a échoué
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

/*
Exemple de multiplication de matrices :

a = [   [1, 2],
        [3, 4] ]    → 2x2

b = [   [5, 6],
        [7, 8] ]    → 2x2

c[0][0] = 1×5 + 2×7 = 5 + 14 = 19
c[0][1] = 1×6 + 2×8 = 6 + 16 = 22
c[1][0] = 3×5 + 4×7 = 15 + 28 = 43
c[1][1] = 3×6 + 4×8 = 18 + 32 = 50

Résultat :
c = [   [19, 22],
        [43, 50] ]    → 2x2

*/


// 4 PERMUTATION DE LIGNES
void permuterLignes(SUPERMRT a, int i, int j) 
{
    double *temp = a->ligne[i];
    a->ligne[i] = a->ligne[j];
    a->ligne[j] = temp;
}

/*
Exemple de permutation de lignes :

On a par exemple cette supermatrice
a = [ [1.0, 2.0, 3.0],   // ligne 0
      [4.0, 5.0, 6.0],   // ligne 1
      [7.0, 8.0, 9.0] ]  // ligne 2

permuterLignes(a, 0, 1);
On permute la ligne 0 avec la ligne 1, ce nui donne :

a = [ [4.0, 5.0, 6.0],   // ligne 0 (ancienne ligne 1)
      [1.0, 2.0, 3.0],   // ligne 1 (ancienne ligne 0)
      [7.0, 8.0, 9.0] ]  // ligne 2 (ne change pas)



*/

// 5 EXTRACTION D'UNE SOUS-MATRICE
SUPERMRT sousMatrice(SUPERMRT a, int L1, int L2, int C1, int C2) {
    // Vérification des bornes
    if (L1 < 0 || L2 >= a->nl || C1 < 0 || C2 >= a->nc || L1 > L2 || C1 > C2)
        return NULL;
        // Vérification de la validité des indices

    // Allocation du descripteur de la sous-matrice
    SUPERMRT sub = (SUPERMRT)malloc(sizeof(*sub));
    if (!sub) return NULL;

    // Définition des dimensions
    sub->nl = L2 - L1 + 1; //L2 =3 et L1 = 1 donc 3-1+1=3
    sub->nc = C2 - C1 + 1; //C2 = 4 et C1 = 2 donc 4-2+1=3

    // Allocation de la table des lignes
    sub->ligne = (double **)malloc(sub->nl * sizeof(double *));
    if (!sub->ligne) {
        free(sub);
        return NULL;
    }

    // Réutilisation des données existantes
    for (int i = 0; i < sub->nl; i++) 
    {
        sub->ligne[i] = &a->ligne[L1 + i][C1];
    }  

    return sub;
}

/*
a->nl = 3;
a->nc = 3;

sousMatrice(a, 1, 4, 0, 2);
Ici L2 = 4, or a->nl = 3 ⇒ donc ligne 4 n'existe pas 
Donc on va retourner NULL



a = [ [1, 2, 3],    // ligne 0
      [4, 5, 6],    // ligne 1
      [7, 8, 9] ]   // ligne 2

SUPERMRT s = sousMatrice(a, 1, 2, 1, 2);

Cela veut dire :

lignes 1 à 2 → [4, 5, 6] et [7, 8, 9]
colonnes 1 à 2 → 5, 6 et 8, 9

sub = [     [5, 6],    // ligne 0
            [8, 9] ]   // ligne 1

*/

// 6 CONVERSION D'UNE MATRICE EN SUPERMATRICE
SUPERMRT matSupermat(double *m, int nLd, int ncd, int nLe, int nce) {
    SUPERMRT sm = (SUPERMRT)malloc(sizeof(*sm));
    if (sm == NULL) return NULL; // L'allocation a échoué

    sm->nl = nLe;
    sm->nc = nce;

    sm->ligne = (double **)malloc(nLe * sizeof(double *));
    if (sm->ligne == NULL) {
        free(sm);
        return NULL; // L'allocation a échoué
    }

    for (int i = 0; i < nLe; i++) 
    {
        sm->ligne[i] = m + i * ncd; // Ligne i
    }

    return sm;
}

/*
double m[6] = {1, 2, 3, 4, 5, 6}; // ncd = 3
SUPERMRT sm = matSupermat(m, ..., 2, 3);

sm->ligne[0] → m + 0 * 3 → &m[0] → [1, 2, 3]
sm->ligne[1] → m + 1 * 3 → &m[3] → [4, 5, 6]

sm[][] = {
    1, 2, 3
    4, 5, 6}

*/



// 7 CONVERSION D'UNE SUPERMATRICE EN MATRICE
void supermatMat(SUPERMRT sm, double *m, int nLd, int ncd) 
{
    for (int i = 0; i < sm->nl; i++) 
    {
        for (int j = 0; j < sm->nc; j++) 
        {
            m[i * ncd + j] = acces(sm, i, j); //sm[i][j]
            // m[i][j] = sm->ligne[i][j];
        }


    }
}

/*
sm =
| 1.1  1.2  1.3 |
| 2.1  2.2  2.3 |

sm->nl = 2

sm->nc = 3

sm->ligne[0] = {1.1, 1.2, 1.3}

sm->ligne[1] = {2.1, 2.2, 2.3}

// i = 0
m[0 * 3 + 0] = sm[0][0] = 1.1   → m[0] = 1.1  
m[0 * 3 + 1] = sm[0][1] = 1.2   → m[1] = 1.2  
m[0 * 3 + 2] = sm[0][2] = 1.3   → m[2] = 1.3  

// i = 1
m[1 * 3 + 0] = sm[1][0] = 2.1   → m[3] = 2.1  
m[1 * 3 + 1] = sm[1][1] = 2.2   → m[4] = 2.2  
m[1 * 3 + 2] = sm[1][2] = 2.3   → m[5] = 2.3  


*/


// 8. Vérification de la contiguïté
int contiguite(SUPERMRT a) 
{
    int contigu = 2; // On suppose contigu et dans l'ordre

    for (int i = 1; i < a->nl; i++) 
    {
        if (a->ligne[i] == a->ligne[i - 1] + a->nc) 
        {
            continue; // OK, dans l'ordre
        } 
        else if (a->ligne[i] > a->ligne[0] && (a->ligne[i] - a->ligne[0]) % a->nc == 0) 
        {
            contigu = 1; // Contigu mais désordonné
        } 
        else 
        {
            return 0; // Pas contigu
        }
    }

    return contigu;
}


/*
Cas 1 – Contigu et ordonné :
a->ligne[0] = m
a->ligne[1] = m + nc
a->ligne[2] = m + 2 * nc
On retourne 2 car Contigu en mémoiredans l'ordre

Cas 2 – Contigu mais désordonné :
a->ligne[0] = m + 2 * nc
a->ligne[1] = m
a->ligne[2] = m + nc
On retourne 1 car Contigu en mémoire mais dans un ordre différent

Cas 3 – Pas contigu :
a->ligne[0] = malloc(nc * sizeof(double));
a->ligne[1] = malloc(nc * sizeof(double));
On retourne 0 car Chanue ligne vient d’un bloc mémoire séparé


*/

// 9 LIBÉRATION DE LA MÉMOIRE
void rendreSupermat(SUPERMRT sm) 
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
