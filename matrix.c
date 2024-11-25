#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG

/*----------------------------------------------------------------------------------------------------------------------------------*/
/* type */

typedef  struct{
    int row;
    int column;
    float **data;
}matrix;

/*---------------------------------------------------------------------------------------------------------------------------------*/

int init_matrix(matrix *A){

    /* Function which initialise with float random values a matrix of size row*col */
    /* Return a success or failure */

    /* Alloue de l'espace mémoire à la matrice */
    A->data = (float**)malloc((*A).column*sizeof(float*));
    if(A->data == NULL){
        fprintf(stderr,"Erreur lors de l'allocation de la matrice initialisée..");
        free(A->data);
        return 1;
    }

    /* Remplie A.data avec des floats aléatoires */
    for(int i = 0; i<(*A).column; i++){
        *(A->data+ i) = (float*)malloc(((*A).row)*sizeof(float));
        if(*(A->data+i) == NULL){
            fprintf(stderr,"Erreur lors de l'allocation de la matrice initialisée..");
            free(A->data[i]);
            free(A->data);
            return 1;
        }
        for(int j = 0; j<(*A).row ; j++){
             *(*(A->data+i)+j) = (float)(rand() % 100) / 100;
        }
    }

    return 0;
}

int init_unit_matrix(matrix *A){

    /* Function which initialise a unit matrix of size NxN */
    /* Return a success or failure */

    /* Alloue de l'espace mémoire à la matrice */
    A->data = (float**)malloc((*A).column*sizeof(float*));
    if(A->data == NULL){
        fprintf(stderr,"Erreur lors de l'allocation de la matrice initialisée..");
        free(A->data);
        return 1;
    }

    /* Remplie A.data avec des floats aléatoires */
    for(int i = 0; i<(*A).column; i++){
        *(A->data+ i) = (float*)malloc(((*A).row)*sizeof(float));
        if(*(A->data+i) == NULL){
            fprintf(stderr,"Erreur lors de l'allocation de la matrice initialisée..");
            free(A->data[i]);
            free(A->data);
            return 1;
        }
        for(int j = 0; j<(*A).row ; j++){
            if(i == j){
                *(*(A->data+i)+j) = 1;
            }
            else{
                *(*(A->data+i)+j) = 0;
            }
        }
    }

    return 0;
}

int init_zero_matrix(matrix *A){

    /* Function which initialise a unit matrix of size NxN */
    /* Return a success or failure */

    /* Alloue de l'espace mémoire à la matrice */
    A->data = (float**)malloc((*A).column*sizeof(float*));
    if(A->data == NULL){
        fprintf(stderr,"Erreur lors de l'allocation de la matrice initialisée..");
        free(A->data);
        return 1;
    }

    /* Remplie A.data avec des floats aléatoires */
    for(int i = 0; i<(*A).column; i++){
        *(A->data+ i) = (float*)malloc(((*A).row)*sizeof(float));
        if(*(A->data+i) == NULL){
            fprintf(stderr,"Erreur lors de l'allocation de la matrice initialisée..");
            free(A->data[i]);
            free(A->data);
            return 1;
        }
        for(int j = 0; j<(*A).row ; j++){
            *(*(A->data+i)+j) = 0;
        }
    }

    return 0;
}

/*-----------------------------------------------------------------------------------------------------------------*/

int display_matrix(matrix M){

    /* Function which display with printf a matrix */

    for(int i = 0; i < M.row ; i++){
        for(int j = 0; j < M.column ; j++ ){
            printf("%f", M.data[j][i]);
        }
        printf("\n");
    }

    return 0;
}

/*-------------------------------------------------------------------------------------------------------------------*/
/* Operations on matrices */

int matrix_product(matrix *output, matrix *A, matrix *B){

    /* Effectue le produit entre A et B et le retourne */
    /* Il faut que nb_col(A) = nb_row(B) */

    /* Génére la structure de la matrice produit */
    (*output).column = (*B).column;
    (*output).row = (*A).row;
    (*output).data = (float**)malloc((*output).column*sizeof(float*));
    if((*output).data == NULL){
        fprintf(stderr,"Erreur lors de l'allocation de la matrice produit..");
        free((*output).data);
        return 1;
    }

    /* Remplissage de la matrice produit */
    for(int i = 0 ; i < (*output).column ; i++ ){
        *((*output).data+i) = (float*)malloc((*output).row*sizeof(float*));
        for(int j = 0 ; j < (*output).row ; j++ ){
            (*output).data[i][j] = 0;
            for(int k = 0 ; k < (*A).column ; k++){
                (*output).data[i][j] += (*A).data[k][j]*(*B).data[i][k];
            }
        }
    }

    return 0;
}

int matrix_sum(matrix *output, matrix *A, matrix *B){

    /* Effectue le produit entre A et B et le retourne */
    /* Il faut que nb_col(A) = nb_row(B) */

    /* Génére la structure de la matrice produit */
    (*output).column = (*B).column;
    (*output).row = (*A).row;
    (*output).data = (float**)malloc((*output).column*sizeof(float*));
    if((*output).data == NULL){
        fprintf(stderr,"Erreur lors de l'allocation de la matrice produit..");
        free((*output).data);
        return 1;
    }

    /* Remplissage de la matrice produit */
    for(int i = 0 ; i < (*output).column ; i++ ){
        *((*output).data+i) = (float*)malloc((*output).row*sizeof(float*));
        for(int j = 0 ; j < (*output).row ; j++ ){
            (*output).data[i][j] = 0;
            for(int k = 0 ; k < (*A).column ; k++){
                (*output).data[i][j] += (*A).data[k][j]*(*B).data[i][k];
            }
        }
    }

    return 0;
}

#ifndef DEBUG

matrix vect_matrix_convolution(matrix M, int size, int step){

    /* Function which converts a matrix into another used for convolution */
    /* It uses the size (nb of cols or rows) of the kernel and the step of the convolution */
    /*  Return matrix */

    matrix R;
    int N_col = ((M.column-size)/step)+1;
    int N_row = ((M.row-size)/step)+1;

    R.row = size*size;
    R.column = N_col*N_row;

    R.data = (float**)malloc(R.column*sizeof(float*));

    int k = 0;
    int vect_kern = 0;

    for(int i = 0 ; i < N_row ; i++ ){
        for( int j = 0 ; j < N_col; j++){
            *(R.data+k) = (float*)malloc(size*size*sizeof(float*));
            vect_kern = 0;
            for(int l = 0 ; l < size ; l++){
                for(int c = 0 ; c < size ; c++){
                   *(*(R.data+k)+vect_kern)= M.data[j*step+c][i*step+l];
                   vect_kern ++;                
                }
            }
            k++;
        }
    }

    return R;

}

int matrix_hadamard_product(matrix A, matrix B, matrix Z){

    /* Génére la structure de la matrice produit */
    Z.column = A.column;
    Z.row = A.row;
    Z.data = (float**)malloc(A.column*sizeof(float*));
    if( Z.data == NULL ){
        fprintf(stderr, "Erreur lors de l'allocation du produit de Hadamard..");
        free(Z.data);
        return 0;
    }

    for(int col = 0 ; col < A.column ; col++ ){
        *(Z.data+col) = (float*)malloc(A.row*sizeof(float*));
        for(int row = 0 ; row < A.row ; row++ ){
            *(*(Z.data+col)+row) = A.data[col][row]*B.data[col][row];
        }
    }

    return 0;
}

int matrix_crop(matrix A, matrix Z, int new_width, int new_height, int shift_left, int shift_top){

    Z.row = new_height;
    Z.column = new_width;
    Z.data = (float **)malloc(new_width*sizeof(float*));
    if(Z.data == NULL){
        fprintf(stderr,"Erreur lors de l'allocation de la matrice cropped..");
        free(Z.data);
        return 1;
    }

    for(int col = shift_left; col<shift_left+new_width; col++){
        *(Z.data + col - shift_left) = (float*)malloc(new_height*sizeof(float));
        for(int row = shift_top; row<shift_top+new_height; row++){
            *(*(Z.data + col - shift_left) + row -shift_top) = A.data[col][row];
        }
    }

    return 0;

}

int matrix_transpose(matrix A, matrix Z){

    float **new_img = (float**)malloc(A.row*sizeof(float*));
    if(new_img == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la transposée..");
        return 1;
    }

    for( int col = 0; col<A.row; col++ ){
        *(new_img + col) = (float*)malloc(A.column*sizeof(float));
        for( int row = 0; row<A.column; row++ ){
            *(*(new_img + col)+row) = A.data[row][col];
        }
    }

    Z.data = new_img;
    Z.column = A.row;
    Z.row = A.column;

    return 0;
}

int matrix_rotate_180(matrix A, matrix Z){

    float **new_img = (float**)malloc(A.column*sizeof(float*));
    if(new_img == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la matrice de 180 degrés..");
        return 1;
    }

    for( int col = 0; col<A.column; col++ ){
        *(new_img + col) = (float*)malloc(A.row*sizeof(float));
        for( int row = 0; row<A.row; row++ ){
            *(*(new_img + col)+row) = A.data[col][A.row-1-row];
        }
    }

    Z.data = new_img;
    Z.column = A.column;
    Z.row = A.row;

    return 0;
}

int free_matrix(matrix M){

    for(int i = 0; i < M.row ; i++){
        free(M.data[i]);
        M.data[i] = NULL;
    }
    free(M.data);
    M.data = NULL;

    return 0;
}

#endif DEBUG

