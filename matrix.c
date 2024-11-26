#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG

/*----------------------------------------------------------------------------------------------------------------------------------*/
/* structures */

typedef  struct{
    int row;
    int column;
    float **data;
}matrix;

/*---------------------------------------------------------------------------------------------------------------------------------*/
/* Initializations */

matrix *init_matrix(int lines, int columns){

    /* Function which initialise with float random values a matrix of size row*col */
    /* Return a success or failure */

    matrix *A;
    A->column = columns;
    A->row = lines;

    /* Alloue de l'espace mémoire à la matrice */
    A->data = (float**)malloc((*A).column*sizeof(float*));
    if(A->data == NULL){
        fprintf(stderr,"Erreur lors de l'allocation de la matrice initialisée..");
        free(A->data);
        return NULL;
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

    return A;
}

matrix *init_unit_matrix(int lines, int columns){

    /* Function which initialise a unit matrix of size NxN */
    /* Return a success or failure */

    matrix *A;
    A->column = columns;
    A->row = lines;

    /* Alloue de l'espace mémoire à la matrice */
    A->data = (float**)malloc((*A).column*sizeof(float*));
    if(A->data == NULL){
        fprintf(stderr,"Erreur lors de l'allocation de la matrice initialisée..");
        free(A->data);
        return NULL;
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

    return A;
}

matrix *init_zero_matrix(int lines, int columns){

    /* Function which initialise a unit matrix of size NxN */
    /* Return a success or failure */

    matrix *A;
    A->column = columns;
    A->row = lines;

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

    /* Effectue la somme entre A et B et le retourne */
    /* Il faut que nb_col(A) = nb_col(B) */
    /* Il faut que nb_row(A) = nb_row(B) */

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
            (*output).data[j][i] = (*A).data[j][i] + (*B).data[j][i];
        }
    }

    return 0;
}

int matrix_hadamard_product(matrix *output, matrix *A, matrix *B){

    /* Génére la structure de la matrice produit */
    (*output).column = (*A).column;
    (*output).row = (*A).row;
    (*output).data = (float**)malloc((*A).column*sizeof(float*));
    if( (*output).data == NULL ){
        fprintf(stderr, "Erreur lors de l'allocation du produit de Hadamard..");
        free((*output).data);
        return 0;
    }

    for(int col = 0 ; col < (*A).column ; col++ ){
        *((*output).data+col) = (float*)malloc((*A).row*sizeof(float*));
        for(int row = 0 ; row < (*A).row ; row++ ){
            *(*((*output).data+col)+row) = (*A).data[col][row]*(*B).data[col][row];
        }
    }

    return 0;
}

int matrix_convolution(matrix *output, matrix *M, matrix *K, int size, int step){

    /* Function which converts a matrix into another used for convolution */
    /* It uses the size (nb of cols or rows) of the kernel and the step of the convolution */

    int N_col = (((*M).column-size)/step)+1;
    int N_row = (((*M).row-size)/step)+1;

    (*output).row = N_row;
    (*output).column = N_col;
    (*output).data = (float**)malloc(N_col*sizeof(float*));

    /* crawling through the output matrix */
    for(int out_col = 0 ; out_col < N_col ; out_col++ ){
        *((*output).data+out_col) = (float*)malloc(N_row*sizeof(float));
        for( int out_line = 0 ; out_line < N_row; out_line++){
            *(*((*output).data+out_col)+out_line) = 0;
            /* Filing slot out_col, out_line */
            for(int c = 0 ; c < size ; c++){
                for(int l = 0 ; l < size ; l++){
                   *(*((*output).data+out_col)+out_line) += (*M).data[out_line*step+l][out_col*step+c] * (*K).data[l][c];
                }
            }
        }
    }

    return 0;

}

int matrix_crop(matrix *output, matrix *A, int new_width, int new_height, int shift_left, int shift_top){

    (*output).row = new_height;
    (*output).column = new_width;
    (*output).data = (float **)malloc(new_width*sizeof(float*));
    if((*output).data == NULL){
        fprintf(stderr,"Erreur lors de l'allocation de la matrice cropped..");
        free((*output).data);
        return 1;
    }

    for(int col = shift_left; col<shift_left+new_width; col++){
        *((*output).data + col - shift_left) = (float*)malloc(new_height*sizeof(float));
        for(int row = shift_top; row<shift_top+new_height; row++){
            *(*((*output).data + col - shift_left) + row -shift_top) = (*output).data[col][row];
        }
    }

    return 0;

}

/*-------------------------------------------------------------------------------------------------------------------------*/
/* Modify matrices */

int matrix_transpose(matrix *output, matrix *A){

    float **new_img = (float**)malloc((*A).row*sizeof(float*));
    if(new_img == NULL){
        fprintf(stderr, "Erreur lors de l'allocation de la transposée..");
        return 1;
    }

    for( int col = 0; col<(*A).row; col++ ){
        *(new_img + col) = (float*)malloc((*A).column*sizeof(float));
        for( int row = 0; row<(*A).column; row++ ){
            *(*(new_img + col)+row) = (*A).data[row][col];
        }
    }

    (*output).data = new_img;
    (*output).column = (*A).row;
    (*output).row = (*A).column;

    return 0;
}

int matrix_rotate_180(matrix *output, matrix A){

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

    (*output).data = new_img;
    (*output).column = A.column;
    (*output).row = A.row;

    return 0;
}

/*-------------------------------------------------------------------------------------------------------------------------------------*/
/* Libération de l'espace mémoire */

int free_matrix(matrix *M){

    for(int i = 0; i < (*M).row ; i++){
        free((*M).data[i]);
        (*M).data[i] = NULL;
    }
    free((*M).data);
    (*M).data = NULL;

    return 0;
}

