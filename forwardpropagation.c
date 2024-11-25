/* Dans les textes suivants le réseau a N couches en comptant la couche d'entrée et celle de sortie. */
/* les couches sont de dimension D( numéro de la couche ) */


/*-----------------------------------------------------------------------------------------------------------*/
/* Imports */

#include "matrix.h"
#include "save.h"

/*-----------------------------------------------------------------------------------------------------------*/
/* Generate usefull matrices : 
/*- activations (A de 0 à N-1 avec 0 la couche d'entrée et N-1 la couche de sortie après le softmax)*/
/*- neurones (Z de 0 à N-1 avec 0 la couche d'entrée et N-1 la couche de sortie)  */
/*- weights (W de 0 à N-1 avec N-1 la matrice identité de dimension D(N-1)xD(N-1) )*/
/*- biais (B de 0 à N-1 avec 0 une matrice de 0 et N-1 une matrice de 0)*/

matrix generate_dense_layer(matrix **W, matrix **B, matrix **X, matrix **A ,int nb_layers ,float *size_neurons){

    /* Entrées : nb_layer : nombre de couches cachées + 2 (entrée et sortie) */
    /* Sortie : return 0 / 1 */

    int n;

    matrix **X;
    X = (matrix**)malloc(nb_layers*sizeof(matrix*));

    matrix **A;
    A = (matrix**)malloc(nb_layers*sizeof(matrix*));

    matrix **W;
    W = (matrix**)malloc(nb_layers*sizeof(matrix*));

    matrix **B;
    B = (matrix**)malloc(nb_layers*sizeof(matrix*));

    for(int i = 0; i < nb_layers; i++){

        n = size_neurons[i];

        /*X*/
        X[i] = init_matrix(size_neurons[i], 1);

        /*A*/
        A[i] = init_matrix(size_neurons[i], 1);

        /*W*/
        if(i != nb_layers-1){
            W[i] = init_matrix(size_neurons[i+1], size_neurons[i]);
        }
        else{
            W[i] = init_unitary_matrix(size_neurons[i], size_neurons[i]);
        }

        /*B*/
        if(i==0){
            B[i] = init_null_matrix(size_neurons[i], 1);
        }
        else{
            B[i] = init_matrix(size_neurons[i], 1);
        }

    } 

}

/*-----------------------------------------------------------------------------------------------------------*/
/*get Z*/

int get_Z(matrix *return_matrix, matrix *W, matrix *B, matrix *X){

    matrix_product(return_matrix, W, X);
    matrix_sum(return_matrix,return_matrix,B);
    
    return 0;
}

int get_A(matrix *return_matrix, matrix *Z, int (*activation)()){

    activation(return_matrix, Z);

    return 0;

}

int set_inputs(matrix **X, matrix **A, matrix *input){

    A[0] = input;
    X[0] = input;

    return 0;

}

/*--------------------------------------------------------------------------------------------------------*/
/*forward propagation*/

int forward_propagation(matrix **Z, matrix **A, matrix **W, matrix **B, int (**activations)()){

    int layers = sizeof(Z)/sizeof(Z[0]);

    for(int i = 1; i <= layers; i++){
        
        get_Z(Z[i], W[i-1], A[i-1], B[i-1]);
        get_A(A[i], Z[i], activations[i]);

    }

    return 0;
}

