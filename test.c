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
    R.row = size*size;
    R.column = ((M.column-size)/step)*((M.row-size)/step);

    R.data = (float**)malloc(R.column*sizeof(float*));

    int k = 0;
    int vect_kern = 0;

    for(int i = 0 ; i < M.row-size+1 ; i++ ){
        for( int j = 0 ; j < M.column-size+1; j++){
            *(R.data+k) = (float*)malloc(size*size*sizeof(float*));
            vect_kern = 0;
            for(int l = 0 ; l < size ; l++){
                for(int c = 0 ; c < size ; c++){
                   *(*(R.data+k)+vect_kern)= M.data[j+c][i+l];
                   vect_kern ++;                
                }
            }
            k++;
        }
    }

    return R;
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

    matrix X = init_matrix(9,9);
    display_matrix(X);

    printf("\n");

    matrix Vect = vect_matrix_convolution(X, 3, 2);
    display_matrix(Vect);

    free_matrix(X);
    free_matrix(Vect);

    return 0;

}