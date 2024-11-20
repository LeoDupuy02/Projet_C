#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrice.h"
#include "activation.h"
#include "fichier.h"

#define DEBUG
#define DEBUG_ini
#define DEBUG_FP
#define DEBUG_BP
#define DEBUG_Up

////////////////////////////////////////

void initialisation(matrice *w, matrice *b, int taille_hidden_layers, int *hidden_layers){
    #ifndef DEBUG
    printf("Initialisation...\n");
    #endif

    for(int i=0; i<taille_hidden_layers-1; i++){

        w[i] = creation_matrice(hidden_layers[i+1], hidden_layers[i]);
        initialiser_poids_he(&w[i]);

        b[i] = creation_matrice(hidden_layers[i+1], 1);
        initialiser_matrice_biais(&b[i]);


        #ifndef DEBUG_ini
        printf("w[%d]\n", i);
        affichage_matrice(&w[i]);
        dimension_matrice(&w[i]);
        printf("\n");
        printf("b[%d]\n", i);
        affichage_matrice(&b[i]);
        dimension_matrice(&b[i]);
        printf("\n");
        #endif
    }
}

void forward_propagation(matrice *a, matrice *z, matrice *w, matrice *b, matrice *X, int taille_hidden_layers, int *hidden_layers){
    #ifndef DEBUG
    printf("Forward...\n");
    #endif

    #ifndef DEBUG_FP
    printf("a[0]\n");
    affichage_matrice(&a[0]);
    dimension_matrice(&a[0]);
    printf("\n");
    #endif

    for(int i=1; i<taille_hidden_layers; i++){
        
        // Z = W * A + B
        prod_matriciel(&z[i-1], &w[i-1], &a[i-1]);
        somme_matrice_b(&z[i-1], &b[i-1]);

        // A = ReLU(z) ou softmax(z)
        cp_matrice(&a[i], &z[i-1]);
        (i<taille_hidden_layers-1) ? ReLU(&a[i]) : softmax(&a[i]);

        #ifndef DEBUG_FP
        printf("z[%d]\n", i-1);
        affichage_matrice(&z[i-1]);
        dimension_matrice(&z[i-1]);
        printf("\n");
        printf("a[%d]\n", i);
        affichage_matrice(&a[i]);
        dimension_matrice(&a[i]);
        printf("\n");
        #endif
    }   
}

void back_propagation(matrice *dz, matrice *dw, matrice *db, matrice *w, matrice *a, matrice *z, matrice *Y, int taille_hidden_layers, int *hidden_layers){
    #ifndef DEBUG
    printf("Back...\n");
    #endif

    matrice filtre;
    matrice tranposee_w;

    //Gradient de la dernière couche

    // dZ = A - Y
    soustraction_matriciel(&dz[taille_hidden_layers-2], &a[taille_hidden_layers-1], Y, 1);
    // db = somme colonne (dZ)
    somme_colonne(&db[taille_hidden_layers-2], &dz[taille_hidden_layers-2]);

    // dW = dZ * At
    matrice tranposee_a = transposee(&a[taille_hidden_layers-2]);
    prod_matriciel(&dw[taille_hidden_layers-2], &dz[taille_hidden_layers-2], &tranposee_a);
    liberation_matrice(&tranposee_a);

    #ifndef DEBUG_BP
    printf("dz[%d]\n", taille_hidden_layers-2);
    affichage_matrice(&dz[taille_hidden_layers-2]);
    dimension_matrice(&dz[taille_hidden_layers-2]);
    printf("\n");
    printf("db[%d]\n", taille_hidden_layers-2);
    affichage_matrice(&db[taille_hidden_layers-2]);
    dimension_matrice(&db[taille_hidden_layers-2]);
    printf("\n");
    printf("dw[%d]\n", taille_hidden_layers-2);
    affichage_matrice(&dw[taille_hidden_layers-2]);
    dimension_matrice(&dw[taille_hidden_layers-2]);
    printf("\n");
    #endif
    
    for(int i=taille_hidden_layers-3; i>-1; i--){

        // dZ = Wt * dZ prod_hadamard filtre
        tranposee_w = transposee(&w[i+1]);
        filtre = d_ReLU(&z[i]);
        prod_matriciel(&dz[i], &tranposee_w, &dz[i+1]);
        prod_Hadamard(&dz[i], &filtre);

        // db = somme_colonne(dZ)
        somme_colonne(&db[i], &dz[i]);

        // dW = dZ * At
        tranposee_a = transposee(&a[i]);
        prod_matriciel(&dw[i], &dz[i], &tranposee_a);

        #ifndef DEBUG_BP
        printf("dz[%d]\n", i);
        affichage_matrice(&dz[i]);
        dimension_matrice(&dz[i]);
        printf("\n");
        printf("db[%d]\n", i);
        affichage_matrice(&db[i]);
        dimension_matrice(&db[i]);
        printf("\n");
        printf("a%d\n",i);
        affichage_matrice(&a[i]);
        dimension_matrice(&a[i]);
        printf("\n");
        printf("dw[%d]\n", i);
        affichage_matrice(&dw[i]);
        dimension_matrice(&dw[i]);
        printf("\n");
        #endif

        liberation_matrice(&tranposee_w);
        liberation_matrice(&filtre);
        liberation_matrice(&tranposee_a);
    }
}

void update(matrice *w, matrice *b, matrice *dw, matrice *db, float learning_rate, int taille_hidden_layers){
    #ifndef DEBUG
    printf("Update...\n");
    #endif

    for(int i=0; i<taille_hidden_layers-1; i++){

        soustraction_matriciel(&w[i], &w[i], &dw[i], learning_rate);
        soustraction_matriciel(&b[i], &b[i], &db[i], learning_rate);

        #ifndef DEBUG_Up
        printf("w[%d]\n", i);
        affichage_matrice(&w[i]);
        dimension_matrice(&w[i]);
        printf("\n");
        printf("b[%d]\n", i);
        affichage_matrice(&b[i]);
        dimension_matrice(&b[i]);
        printf("\n");
        #endif
    }
}

//////////////////////////////////////// 

void perceptron(matrice *X, matrice *Y, int *hidden_layers, int taille_hidden_layers, float learning_rate, int nb_iter){
    #ifndef DEBUG
    printf("Perceptron...\n");
    #endif

    // Ajout du nb de ligne de X et Y en première et dernière position
    hidden_layers[0]=(*X).ligne;
    hidden_layers[taille_hidden_layers-1]=(*Y).ligne;

    // Allocation des listes des matrices w et b coontenant les paramètres des neurones 
    matrice *w = malloc((taille_hidden_layers-1)*sizeof(matrice));
    matrice *b = malloc((taille_hidden_layers-1)*sizeof(matrice));
    matrice *z = malloc((taille_hidden_layers-1)*sizeof(matrice));
    matrice *a = malloc((taille_hidden_layers)*sizeof(matrice));

    // Allocation des listes dw et db contenant les gardients 
    matrice *dw = malloc((taille_hidden_layers-1)*sizeof(matrice));
    matrice *db = malloc((taille_hidden_layers-1)*sizeof(matrice));
    matrice *dz = malloc((taille_hidden_layers-1)*sizeof(matrice));

    // Mise au niveau NULL
    for(int i=0;i<taille_hidden_layers-1;i++){
        w[i].tab = NULL;
        b[i].tab = NULL;
        z[i].tab = NULL;
        a[i].tab = NULL;
        dw[i].tab = NULL;
        db[i].tab = NULL;
        dz[i].tab = NULL;
    }
    a[taille_hidden_layers-1].tab = NULL;

    // Création du tableau contenant les valeurs log_loss
    float *loss_history = (float *)malloc(nb_iter * sizeof(float));

    initialisation(w, b, taille_hidden_layers, hidden_layers);

    // Entrainement
    cp_matrice(&a[0], X);
    for(int j=0; j<nb_iter; j++){

        forward_propagation(a, z, w, b, X, taille_hidden_layers, hidden_layers);

        back_propagation(dz, dw, db, w, a, z, Y, taille_hidden_layers, hidden_layers);

        update(w, b, dw, db, learning_rate, taille_hidden_layers);

        float loss = log_loss(&a[taille_hidden_layers-1], Y); 
        loss_history[j] = loss; 
        printf("Iteration %d - Log Loss: %f\n", j, loss);

    }

    // Sauvegarde du log_loss
    FILE *f = fopen("loss_data.csv", "w");
    for (int i = 0; i < nb_iter; i++) {
        fprintf(f, "%f\n", loss_history[i]);
    }
    fclose(f);

    // Séction libération de la mémoire 
    for(int i=0; i<taille_hidden_layers-1; i++){
        liberation_matrice(&w[i]);
        liberation_matrice(&b[i]);
        liberation_matrice(&a[i]);
        liberation_matrice(&z[i]);

        liberation_matrice(&dw[i]);
        liberation_matrice(&db[i]);
        liberation_matrice(&dz[i]);
    }
    liberation_matrice(&a[taille_hidden_layers-1]);

    free(z);
    free(a);
    free(b);
    free(w);

    free(db);
    free(dw);
    free(dz);

    free(loss_history);

    printf("FIN !");
}

////////////////////////////////////////

void main(){

    int num_images = 1000;       

    matrice X = creation_matrice(28*28, num_images);
    matrice Y = creation_matrice(10, num_images);

    // Chargement des datasets
    charger_images("train-images.idx3-ubyte", &X, num_images, 28*28);
    charger_labels("train-labels.idx1-ubyte", &Y, num_images);

    // Création des couhes intermédiaires et de sa taille
    int hidden_layers[3] = {0, 128, 0};
    int taille_hidden_layers = sizeof(hidden_layers) / sizeof(hidden_layers[0]);

    perceptron(&X, &Y, hidden_layers, taille_hidden_layers, 0.0001, 40);

    liberation_matrice(&X);
    liberation_matrice(&Y);
}