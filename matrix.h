/* Dans ce fichier tous les arguments d'une fonction commencent par la matrice à retourner et les matrices */
/* en entrée sont notés A, B... */

#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//#define DEBUG

// Déclaration de la structure matrix
typedef struct {
    int row;
    int column;
    float **data;
} matrix;

/* Define matrices */
int init_matrix(matrix* A);
int init_zero_matrix(matrix *A);
int init_unit_matrix(matrix *A);

int display_matrix(matrix M);

/* Operations on matrices */
int matrix_product(matrix *output, matrix *A, matrix *B);
int matrix_sum(matrix *output, matrix *A, matrix *B);
int matrix_hadamard_product(matrix *output, matrix *A, matrix *B);
int matrix_convolution(matrix *output, matrix *M, matrix *K, int size, int step);

/* Modify matrices */
int matrix_transpose(matrix *output, matrix *A);
int matrix_rotate_180(matrix *output, matrix *A);
int matrix_crop(matrix *A, matrix *Z, int new_width, int new_height, int shift_left, int shift_top);

/*free matrices*/
int free_matrix(matrix M);

#ifndef DEBUG
#endif // DEBUG

#endif // MATRIX_OPERATIONS_H