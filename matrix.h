#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Définition des macros
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
int matrix_product(matrix *output_matrix, matrix *A, matrix *B);
int matrix_sum(matrix *output_matrix, matrix *A, matrix *B);
int matrix_hadamard_product(matrix *output_matrix, matrix *A, matrix *B);

/* Modify matrices */
int matrix_transpose(matrix *output_matrix, matrix *A);
int matrix_rotate_180(matrix *output_matrix, matrix *A);
int matrix_crop(matrix *A, matrix *Z, int new_width, int new_height, int shift_left, int shift_top);

/*free matrices*/
int free_matrix(matrix M);

#ifndef DEBUG
matrix vect_matrix_convolution(matrix M, int size, int step);
#endif // DEBUG

#endif // MATRIX_OPERATIONS_H