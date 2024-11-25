#define DENSE

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef DENSE
#include "matrix.h"

matrix layer(matrix W, matrix X, matrix B, matrix (* A)( matrix )){

    matrix C;
    C.row = R.column;
    C.column = 1;
    C.matrix = (**float)malloc(1*sizeof(float *));

    /* Retourne la sortie d'une couche de neurone à partir de la sortie de la couche précédente */
    /* W = les poids des synapses, X = la sortie de la couche précédente, B = les biais des neurones, A = la fonction d'activation */
    /* Return : Z = Sortie de la couche de neurones (vecteur colonne) */

    C = matrix_product(W,X);
    C = matrix_sum(C,B);
    C = A(C);

    return C;
}

#endif DENSE