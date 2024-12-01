#include <stdio.h>
#include <stdlib.h>
#include <math.h>

///////////////////////////////////////////////////////

typedef struct _matrice matrice;
struct _matrice{
    int ligne;
    int colonne;
    float **tab;

};

void remplissage_n(matrice *matrice, float n){
    for(int i=0; i<(*matrice).ligne; i++){
        for(int j=0; j<(*matrice).colonne; j++){
            (*matrice).tab[i][j] = n;
        }
    }
}

matrice creation_matrice(int ligne, int colonne){

    // Déf d'une matrice avec ses dimensions
    matrice matrice;
    matrice.colonne = colonne;
    matrice.ligne = ligne;

    // Allocation de la taille d'une ligne 
    matrice.tab = (float**)malloc(ligne * sizeof(float *));

    if (matrice.tab == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }
    // Allocation dans chaque cases de la ligne, d'une colonne 
    for(int i=0; i<ligne; i++){
        matrice.tab[i] = (float *)malloc(colonne * sizeof(float));
    }
    remplissage_n(&matrice, 0);
    return matrice;
}

void liberation_matrice(matrice *matrice){
    for(int i=0; i<(*matrice).ligne; i++){
        free((*matrice).tab[i]);
    }
    free((*matrice).tab);
}

void affichage_matrice(matrice *matrice){
    for(int i=0; i<(*matrice).ligne; i++){
        printf("[  ");
        for(int j=0; j<(*matrice).colonne; j++){
            printf("%f  ", (*matrice).tab[i][j]);
        }
    printf("]\n");
    }
}

void dimension_matrice(matrice *matrice){
    printf("(%d ; %d)\n", (*matrice).ligne, (*matrice).colonne);
}

void remplissage(matrice *matrice, float *liste){
    int index = 0;
    for(int i=0; i<(*matrice).ligne; i++){
        for(int j=0; j<(*matrice).colonne; j++){
            (*matrice).tab[i][j] = liste[index];
            index++;
        }
    }
}

//////////////////////////////////////////////////////

void prod_matriciel(matrice *matrice_finale, matrice *matrice1, matrice *matrice2){

    if ((*matrice1).colonne != (*matrice2).ligne) {
        printf("Erreur lors du prod matriciel : pb de dim !\n");
        printf("(%d,%d)  (%d,%d)", (*matrice1).ligne, (*matrice1).colonne, (*matrice2).ligne, (*matrice2).colonne);
        exit(EXIT_FAILURE);
    }

    if ((*matrice_finale).tab == NULL){
        *matrice_finale = creation_matrice((*matrice1).ligne, (*matrice2).colonne);
    }
    
    for(int i=0; i<(*matrice1).ligne; i++){
        for(int j=0; j<(*matrice2).colonne; j++){
            (*matrice_finale).tab[i][j] = 0;
            for(int k=0; k<(*matrice1).colonne; k++){
                (*matrice_finale).tab[i][j] += (*matrice1).tab[i][k]*(*matrice2).tab[k][j];
            }
        }
    }
}

void soustraction_matriciel(matrice *matrice_finale, matrice *matrice1, matrice *matrice2, float learning_rate){
    
    if (((*matrice1).ligne != (*matrice2).ligne) || ((*matrice1).colonne != (*matrice2).colonne)){
        printf("Erreur lors de la sous matriciel : pb de dim !");
        printf("(%d,%d)  (%d,%d)", (*matrice1).ligne, (*matrice1).colonne, (*matrice2).ligne, (*matrice2).colonne);
        exit(EXIT_FAILURE);
    }

    if ((*matrice_finale).tab == NULL){
        *matrice_finale = creation_matrice((*matrice1).ligne, (*matrice1).colonne);
    }

    for(int i=0; i<(*matrice1).ligne; i++){
        for(int j=0; j<(*matrice1).colonne; j++){
            (*matrice_finale).tab[i][j] = (*matrice1).tab[i][j]- learning_rate*(*matrice2).tab[i][j];
        }
    }
}

matrice transposee(matrice *matrice1){

    matrice matrice2 = creation_matrice((*matrice1).colonne, (*matrice1).ligne);

    for(int i=0; i<(*matrice1).colonne; i++){
        for(int j=0; j<(*matrice1).ligne; j++){
            matrice2.tab[i][j] = (*matrice1).tab[j][i];
        }
    }
    return matrice2;
}

void multiplication_scalaire(matrice *matrice1, float n){
    for(int i=0; i<(*matrice1).ligne; i++){
        for(int j=0; j<(*matrice1).colonne; j++){
            (*matrice1).tab[i][j] *= n;
        }
    }
}

void somme_matrice_b(matrice *matrice1, matrice *matrice2){

    if((*matrice2).colonne != 1){
        printf("Erreur lors de somme_matrice_b : pb de dim !");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<(*matrice1).ligne; i++){
        for(int j=0; j<(*matrice1).colonne; j++){
            (*matrice1).tab[i][j] += (*matrice2).tab[i][0];
        }
    }
}

void somme_colonne(matrice *matrice_finale, matrice *matrice1){

    float somme=0;

    if ((*matrice_finale).tab == NULL){
        *matrice_finale = creation_matrice((*matrice1).ligne, 1);
    }

    int j;
    for(int i=0; i<(*matrice1).ligne; i++){
        somme=0;
        j=0;
        for(j; j<(*matrice1).colonne; j++){
            somme+=(*matrice1).tab[i][j];
        }
        (*matrice_finale).tab[i][0] = somme/j;
    }
}

void prod_Hadamard(matrice *matrice1, matrice *matrice2){

    if ((*matrice1).colonne != (*matrice2).colonne || (*matrice1).ligne != (*matrice2).ligne){
        printf("Erreur lors du prod Hadamard : pb de dim !\n");
        printf("(%d,%d)  (%d,%d)", (*matrice1).ligne, (*matrice1).colonne, (*matrice2).ligne, (*matrice2).colonne);
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<(*matrice1).ligne; i++){
        for(int j=0; j<(*matrice1).colonne; j++){
            (*matrice1).tab[i][j] *= (*matrice2).tab[i][j];
        }
    }
}

void cp_matrice(matrice *matrice_finale, matrice *matrice1){

    if ((*matrice_finale).tab == NULL){
        *matrice_finale = creation_matrice((*matrice1).ligne, (*matrice1).colonne);
    }

    for(int i=0; i<(*matrice1).ligne; i++){
        for(int j=0; j<(*matrice1).colonne; j++){
            (*matrice_finale).tab[i][j] = (*matrice1).tab[i][j];
        }
    }
}



void initialiser_poids_he(matrice *matrice) {
    float stddev = sqrt(2.0 / (*matrice).ligne);  

    for (int i = 0; i < (*matrice).ligne; i++) {
        for (int j = 0; j < (*matrice).colonne; j++) {
            (*matrice).tab[i][j] = ((float)rand() / (float)(RAND_MAX)) * 2.0 - 1.0;  
            (*matrice).tab[i][j] *= stddev; 
        }
    }
}

void initialiser_matrice_biais(matrice *matrice) {
    for (int i = 0; i < (*matrice).ligne; i++) {
        for (int j = 0; j < (*matrice).colonne; j++) {
            (*matrice).tab[i][j] = 0.01; 
        }
    }
}

//////////////////////////////////////////////////////
