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

void remplissage_n(matrice *matrice, float n){
    for(int i=0; i<(*matrice).ligne; i++){
        for(int j=0; j<(*matrice).colonne; j++){
            (*matrice).tab[i][j] = n;
        }
    }
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

matrice prod_matriciel(matrice *matrice1, matrice *matrice2){

    if ((*matrice1).colonne != (*matrice2).ligne) {
        printf("Erreur lors du prod matriciel : pb de dim !\n");
        printf("(%d,%d)  (%d,%d)", (*matrice1).ligne, (*matrice1).colonne, (*matrice2).ligne, (*matrice2).colonne);
        exit(EXIT_FAILURE);
    }

    matrice matrice3 = creation_matrice((*matrice1).ligne, (*matrice2).colonne);
    remplissage_n(&matrice3, 0);
    
    for(int i=0; i<(*matrice1).ligne; i++){
        for(int j=0; j<(*matrice2).colonne; j++){
            for(int k=0; k<(*matrice1).colonne; k++){
                matrice3.tab[i][j] += (*matrice1).tab[i][k]*(*matrice2).tab[k][j];
            }
        }
    }
    
    return matrice3;
}

matrice soustraction_matriciel(matrice *matrice1, matrice *matrice2){
    
    if (((*matrice1).ligne != (*matrice2).ligne) || ((*matrice1).colonne != (*matrice2).colonne)){
        printf("Erreur lors de la sous matriciel : pb de dim !");
        exit(EXIT_FAILURE);
    }

    matrice matrice3 = creation_matrice((*matrice1).ligne, (*matrice1).colonne);
    remplissage_n(&matrice3, 0);

    for(int i=0; i<(*matrice1).ligne; i++){
        for(int j=0; j<(*matrice1).colonne; j++){
            matrice3.tab[i][j] = (*matrice1).tab[i][j]-(*matrice2).tab[i][j];
        }
    }
    
    return matrice3;
}

matrice transposee(matrice *matrice1){

    matrice matrice2 = creation_matrice((*matrice1).colonne, (*matrice1).ligne);
    remplissage_n(&matrice2, 0);

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

matrice somme_colonne(matrice *matrice1){

    float somme=0;

    matrice matrice2 = creation_matrice((*matrice1).ligne, 1);
    remplissage_n(&matrice2, 0);

    for(int i=0; i<(*matrice1).ligne; i++){
        somme=0;
        for(int j=0; j<(*matrice1).colonne; j++){
            somme+=(*matrice1).tab[i][j];
        }
        matrice2.tab[i][0] = somme;
    }
    return matrice2;
}

void prod_Hadamard(matrice *matrice1, matrice *matrice2){
    for(int i=0; i<(*matrice1).ligne; i++){
        for(int j=0; j<(*matrice1).colonne; j++){
            (*matrice1).tab[i][j] *= (*matrice2).tab[i][j];
        }
    }
}

matrice cp_matrice(matrice *matrice1){

    matrice matrice2 = creation_matrice((*matrice1).ligne, (*matrice1).colonne);
    remplissage_n(&matrice2, 0);

    for(int i=0; i<(*matrice1).ligne; i++){
        for(int j=0; j<(*matrice1).colonne; j++){
            matrice2.tab[i][j] = (*matrice1).tab[i][j];
        }
    }
    return matrice2;
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
            (*matrice).tab[i][j] = 0.0; 
        }
    }
}

//////////////////////////////////////////////////////
