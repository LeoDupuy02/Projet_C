#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrice.h"
#include "activation.h"
#include "fichier.h"

//#define DEBUG
#define DEBUG_ini
#define DEBUG_FP
//#define DEBUG_BP
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

void initialisation_2(matrice *w, matrice *b, int taille_hidden_layers, int *hidden_layers){
    #ifndef DEBUG
    printf("Initialisation...\n");
    #endif

    w[0] = creation_matrice(4, 4);
    float liste_w0[] = {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.8,0.7,0.6,0.5,0.4,0.3,0.2};
    remplissage(&w[0], liste_w0);

    b[0] = creation_matrice(4, 1);
    float liste_b0[] = {0,0,0,0};
    remplissage(&b[0], liste_b0);

    w[1] = creation_matrice(2, 4);
    float liste_w1[] = {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8};
    remplissage(&w[1], liste_w1);

    b[1] = creation_matrice(2,1);
    float liste_b1[] = {0,0};
    remplissage(&b[1], liste_b1);

}

void forward_propagation(matrice *a, matrice *z, matrice *w, matrice *b, matrice *X, int taille_hidden_layers, int *hidden_layers){
    #ifndef DEBUG
    printf("Forward...\n");
    #endif

    a[0] = *X;
    #ifndef DEBUG_FP
    printf("a[0]\n");
    affichage_matrice(&a[0]);
    dimension_matrice(&a[0]);
    printf("\n");
    #endif

    for(int i=1; i<taille_hidden_layers; i++){

        z[i] = prod_matriciel(&w[i-1], &a[i-1]);

        somme_matrice_b(&z[i], &b[i-1]);
        a[i] = cp_matrice(&z[i]);

        if (i<taille_hidden_layers-1){
            ReLU(&a[i]);
        } 
        else {
            softmax(&a[i]);
        }
        #ifndef DEBUG_FP
        printf("z[%d]\n", i);
        affichage_matrice(&z[i]);
        dimension_matrice(&z[i]);
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

    // Gradient de la dernière couche
    dz[taille_hidden_layers-2] = soustraction_matriciel(&a[taille_hidden_layers-1], Y);
    db[taille_hidden_layers-2] = somme_colonne(&dz[taille_hidden_layers-2]);
    matrice t = transposee(&a[taille_hidden_layers-2]);
    dw[taille_hidden_layers-2] = prod_matriciel(&dz[taille_hidden_layers-2], &t);

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

        
        t = transposee(&w[i+1]);
        dz[i] = prod_matriciel(&t, &dz[i+1]);
        liberation_matrice(&t);

        #ifndef DEBUG_BP
        printf("dz[%d]\n", i);
        affichage_matrice(&dz[i]);
        dimension_matrice(&dz[i]);
        printf("\n");
        #endif

        db[i] = prod_matriciel(&t, &db[i+1]);
        t = d_ReLU(&z[i+1]);
        prod_Hadamard(&db[i], &t);
        liberation_matrice(&t);

        #ifndef DEBUG_BP
        printf("db[%d]\n", i);
        affichage_matrice(&db[i]);
        dimension_matrice(&db[i]);
        printf("\n");
        #endif

        t = transposee(&a[i]);
        ReLU(&dz[i]);
        liberation_matrice(&t);

        #ifndef DEBUG_BP
        printf("a%d\n",i);
        affichage_matrice(&a[i]);
        dimension_matrice(&a[i]);
        printf("t\n");
        affichage_matrice(&t);
        dimension_matrice(&t);
        printf("\n");
        printf("dz[%d]\n", i);
        affichage_matrice(&dz[i]);
        dimension_matrice(&dz[i]);
        printf("\n");
        #endif

        dw[i] = prod_matriciel(&dz[i], &t);

        #ifndef DEBUG_BP
        printf("dw[%d]\n", i);
        affichage_matrice(&dw[i]);
        dimension_matrice(&dw[i]);
        printf("\n");
        #endif
    }
}

void update(matrice *w, matrice *b, matrice *dw, matrice *db, float learning_rate, int taille_hidden_layers){
    #ifndef DEBUG
    printf("Update...\n");
    #endif

    for(int i=0; i<taille_hidden_layers-1; i++){

        multiplication_scalaire(&dw[i], learning_rate);
        w[i] = soustraction_matriciel(&w[i], &dw[i]);

        multiplication_scalaire(&db[i], learning_rate);
        b[i] = soustraction_matriciel(&b[i], &db[i]);

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

    // Création des listes des matrices w et b coontenant les paramètres des neurones 
    matrice *w = malloc((taille_hidden_layers-1)*sizeof(matrice));
    matrice *b = malloc((taille_hidden_layers-1)*sizeof(matrice));
    matrice *z = malloc((taille_hidden_layers-1)*sizeof(matrice));
    matrice *a = malloc((taille_hidden_layers)*sizeof(matrice));

    // Création des listes dw et db contenant les gardients 
    matrice *dw = malloc((taille_hidden_layers-1)*sizeof(matrice));
    matrice *db = malloc((taille_hidden_layers-1)*sizeof(matrice));
    matrice *dz = malloc((taille_hidden_layers-1)*sizeof(matrice));

    float *loss_history = (float *)malloc(nb_iter * sizeof(float));

    initialisation(w, b, taille_hidden_layers, hidden_layers);


    for(int j=0; j<nb_iter; j++){

        forward_propagation(a, z, w, b, X, taille_hidden_layers, hidden_layers);

        back_propagation(dz, dw, db, w, a, z, Y, taille_hidden_layers, hidden_layers);

        update(w, b, dw, db, learning_rate, taille_hidden_layers);

        float loss = log_loss(&a[taille_hidden_layers-1], Y); // Calcul de la log loss
        loss_history[j] = loss;  // Enregistrer la perte
        printf("Iteration %d - Log Loss: %f\n", j, loss);

    }

    // À la fin de l'entraînement, écrivez la perte dans un fichier pour le graphique en Python
    FILE *f = fopen("loss_data.csv", "w");
    for (int i = 0; i < nb_iter; i++) {
        fprintf(f, "%f\n", loss_history[i]);
    }
    fclose(f);

    // Libérez la mémoire après utilisation
    free(loss_history);







    // Séction libération de la mémoire 
    for(int i=0; i<taille_hidden_layers-1; i++){
        printf("%d\n", i);
        liberation_matrice(&w[i]);
        liberation_matrice(&b[i]);
        liberation_matrice(&a[i]);
        (i!=0) ? liberation_matrice(&z[i]) : 0;

        liberation_matrice(&dw[i]);
        liberation_matrice(&db[i]);
        liberation_matrice(&dz[i]);
    }
    printf("Fin des liberation\n");
    liberation_matrice(&a[taille_hidden_layers-1]);

    free(z);
    printf("free z\n");
    free(a);
    printf("free a\n");
    free(b);
    printf("free b\n");
    free(w);
    printf("free w\n");

    free(db);
    printf("free db\n");
    free(dw);
    printf("free dw\n");
    free(dz);
    printf("free dz\n");

    printf("FIN !");
}

////////////////////////////////////////

void main(){

    int num_images = 50;      
    int taille_image = 28*28;  
    int nb_classes = 10;         

    matrice X = creation_matrice(taille_image, num_images);
    matrice Y = creation_matrice(nb_classes, num_images);

    charger_images("train-images.idx3-ubyte", &X, num_images, taille_image);
    charger_labels("train-labels.idx1-ubyte", &Y, num_images);

    affichage_matrice(&X);
    affichage_matrice(&Y);

    // Création des couhes intermédiaires et de sa taille
    int hidden_layers[3] = {0, 4, 0};
    int taille_hidden_layers = sizeof(hidden_layers) / sizeof(hidden_layers[0]);

    perceptron(&X, &Y, hidden_layers, taille_hidden_layers, 0.1, 10);
}
