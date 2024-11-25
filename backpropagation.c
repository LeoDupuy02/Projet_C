
/* La première couche de neurones est notée 1. Les poids avant elle et ses biais sont indexés comme 1 
    La seconde couche de neurones est notée 2. Les poids avant elle et ses biais sont indexés comme 1
    Chaque rangée de neurones possède donc un indice i.
    Chaque neurone possède un indice n au sein de sa rangée.
    Par conséquent si on veut updater les biais 1 et le poids 1 liés au neurone [i;n] on peut le faire en même temps
*/

#include "matrix.h"
#include "math.h"

/*--------------------------------------------------------------------------------------------------------------*/
/* Activation functions */

float RELU( float x ){
    if( x<=0 ){ return 0; }
    else{ return x;}
}

float derivative_RELU( float x ){
    if( x<=0 ){ return 0.0;}
    else{ return 1.0; }
}

int softmax(matrix *return_matrix, matrix *output){

    float Z;
    Z = partition_function(output);

    for( int i = 0; i < (*output).row; i++ ){
        (*return_matrix).data[i][0] = expf((*output).data[i][0])/Z;
    }

    return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/
/*Loss - Cross Entropy Loss / Log Loss*/

float partition_function(matrix *output){

    float Z = 0;

    for( int i = 0; i < (*output).row; i++ ){
        Z += expf((*output).data[i][0]);
    }

    return Z;
}

float CrossEntropyLoss(matrix *output, matrix *labels){
    
    float Z = 0;
    float C = 0;
    float exp = 0;

    Z = partition_function(output);

    for( int i = 0; i < (*output).row; i++ ){
        exp = expf((*output).data[i][0]);
        C += -logf( exp/Z )*(*labels).data[0][i];
    }

    return C;
}

int derivative_CrossEntropyLoss(matrix *return_matrix, matrix *output, matrix *labels){

    softmax(return_matrix, output);
    matrix_difference(return_matrix, return_matrix,labels);

    return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/
/* Backpropagation by layer*/

int delta_L(matrix *return_matrix, matrix *output, matrix *labels){

    matrix D_sigma;
    D_sigma.column = output->column;
    D_sigma.row = output->row;
    init_matrix(&D_sigma);
    derivative_softmax(&D_sigma, output);

    derivative_CrossEntropyLoss(return_matrix, output, labels);
    matrix_hadamard_product(return_matrix, return_matrix, &D_sigma);

    free_matrix(D_sigma);

    return 0;
}

int delta_l(matrix *return_matrix, matrix *prev_delta_l, matrix *prev_W, matrix *output, float (*d_sigma)()){

    matrix D_sigma;
    init_matrix(&D_sigma, (*output).column, (*output).row);
    d_sigma(&D_sigma, output);

    matrix_transpose(return_matrix, prev_W);
    matrix_product(return_matrix, return_matrix, prev_delta_l);
    matrix_hadamard_product(return_matrix, return_matrix, D_sigma);

    free_matrix(D_sigma);

    return 0;
}

int D_loss_weight_layer(matrix *return_matrix, float learning_rate, matrix *delta, matrix *activation){
    
    matrix_transpose(return_matrix, activation);
    matrix_product(return_matrix, delta, return_matrix, learning_rate);

    return 0;
}

int D_loss_biais_layer(matrix *return_matrix, float learning_rate, matrix *delta){

    matrix_mult_const(return_matrix, learning_rate, delta);

    return 0;

}

/*-----------------------------------------------------------------------------------------------------------*/
/*updates*/

int update_W(matrix *W, matrix *dW){

    /*Parcours des poids*/

    matrix_difference(*W, *dW);

    return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/


