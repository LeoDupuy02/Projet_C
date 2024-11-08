#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef  struct{
    int row;
    int column;
    float **data;
}matrix;


matrix init_matrix(int row, int col){

    /* Function which initialise with float random values a matrix of size row*col */
    /* Return a matrix */

    matrix M;
    M.row = row;
    M.column = col;

    M.data = (float**)malloc(col*sizeof(float*));
    for(int i = 0; i<col; i++){
        *(M.data+ i) = (float*)malloc(row*sizeof(float));
        for(int j = 0; j<row ; j++){
             *(*(M.data+i)+j) = (float)(rand() % 100) / 100;
        }
    }

    return M;
}

int display_matrix(matrix M){

    /* Function which display with printf a matrix */

    for(int i = 0; i < M.row ; i++){
        for(int j = 0; j < M.column ; j++ ){
            printf("%2.6f", M.data[j][i]);
        }
        printf("\n");
    }

    return 0;
}

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

matrix matrix_product(matrix A, matrix B){

    matrix C;
    C.column = B.column;
    C.row = A.row;

    for(int i = 0 ; i < C.row ; i++ ){
        for(int j = 0 ; i < C.column ; i++ ){
            C.data[j][i] = 0;
            for(int k = 0 ; i < A.column ; i++){
                C.data[j][i] += A.data[j+k][i]*B.data[j][i+k];
            }
        }
    }

    return C;
}

int free_matrix(matrix M){

    for(int i = 0; i < M.row ; i++){
        free(M.data[i]);
        M.data[i] = NULL;
    }
    free(M.data);
    M.data = NULL;

}

int main() {

    srand( time(0) );

    matrix A = init_matrix(9,9);
    display_matrix(A);

    printf("\n");

    matrix B = init_matrix(9,9);
    display_matrix(B);

    printf("\n");

    matrix C = matrix_product(A,B);
    display_matrix(C);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);

    return 0;

}