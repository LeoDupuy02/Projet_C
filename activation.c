#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "matrice.h"

////////////////////////////////////////

void ReLU(matrice *matrice){
    for(int i=0; i<(*matrice).ligne; i++){
        for(int j=0; j<(*matrice).colonne; j++){
            (*matrice).tab[i][j] = ((*matrice).tab[i][j] < 0) ? 0 : (*matrice).tab[i][j];
        }
    }
}

void sigmoide(matrice *matrice){
    for(int i=0; i<(*matrice).ligne; i++){
        for(int j=0; j<(*matrice).colonne; j++){
            (*matrice).tab[i][j] = 1/(1+exp(-(*matrice).tab[i][j]));
        }
    }
}

void softmax(matrice *mat){
    for(int j=0; j<(*mat).colonne; j++){

        float somme = 0.0;
        for(int i=0; i<(*mat).ligne; i++){
            somme += exp((*mat).tab[i][j]);
        }
        if (somme > 0) {
            for(int i=0; i<(*mat).ligne; i++){
                (*mat).tab[i][j] = exp((*mat).tab[i][j]) / somme;
            }
        } else {
            for(int i=0; i<(*mat).ligne; i++){
                (*mat).tab[i][j] = 0.0;
            }
        }
    }
}

matrice d_ReLU(matrice *matrice1){

    matrice matrice2 = creation_matrice((*matrice1).ligne, (*matrice1).colonne);

    for(int i=0; i<(*matrice1).ligne; i++){
        for(int j=0; j<(*matrice1).colonne; j++){
            matrice2.tab[i][j] = ((*matrice1).tab[i][j] > 0) ? 1 : 0;
        }
    }
    return matrice2;
}

float log_loss(matrice *matrice1, matrice *matrice2) {
    float somme = 0.0;
    int nombre_labels = 0;

    for(int i = 0; i < (*matrice1).ligne; i++) {
        for(int j = 0; j < (*matrice1).colonne; j++) {

            if((*matrice2).tab[i][j] == 1) {

                float prob = (*matrice1).tab[i][j] > 0 ? (*matrice1).tab[i][j] : 1e-7;
                somme -= log(prob); 
                nombre_labels++;
            }
        }
    }
    
    if (nombre_labels > 0) {
        return somme / nombre_labels;
    } else {
        printf("Erreur : Aucun label 1 trouvé dans matrice2\n");
        return 0.0;
    }
}


////////////////////////////////////////
