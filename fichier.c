#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "matrice.h"

void train_images(char *nom_fichier, matrice *X_train, int num_images){
    FILE *fichier = fopen(nom_fichier, "rb");

    // Passer Header
    for(int i=0; i<16;i++){
        fgetc(fichier);
    }

    // Récup des images
    for (int i = 0; i < num_images; i++) {
        for (int j = 0; j < 28*28; j++) {
            (*X_train).tab[j][i] = fgetc(fichier) / 255.0;
        }
    }

    fclose(fichier);
    printf("Chargement des images_train terminés !\n");
}

void train_labels(const char *nom_fichier, matrice *Y_train, int num_images){

    FILE *fichier = fopen(nom_fichier, "rb");

    // Passer Header
    for(int i=0; i<8;i++){
        fgetc(fichier);
    }

    // Lecture des labels et stockage dans Y
    for (int i = 0; i < num_images; i++) {
        int label = fgetc(fichier);
        (*Y_train).tab[label][i] = 1.0; // Mise du bit de l'étiquette à 1
    }

    fclose(fichier);
    printf("Chargement des labels_train terminés !\n");
}

void test_images(char *nom_fichier, matrice *X_test, int num_images){
    FILE *fichier = fopen(nom_fichier, "rb");

    // Passer Header
    for(int i=0; i<16;i++){
        fgetc(fichier);
    }

    // Récup des images
    for (int i = 0; i < num_images; i++) {
        for (int j = 0; j < 28*28; j++) {
            (*X_test).tab[j][i] = fgetc(fichier) / 255.0;
        }
    }

    fclose(fichier);
    printf("Chargement des images_test terminés !\n");
}

void test_labels(const char *nom_fichier, matrice *Y_test, int num_images){

    FILE *fichier = fopen(nom_fichier, "rb");

    // Passer Header
    for(int i=0; i<8;i++){
        fgetc(fichier);
    }

    // Lecture des labels et stockage dans Y
    for (int i = 0; i < num_images; i++) {
        int label = fgetc(fichier);
        (*Y_test).tab[label][i] = 1.0; // Mise du bit de l'étiquette à 1
    }

    fclose(fichier);
    printf("Chargement des labels_test terminés !\n");
}

void enregistrement_matrice(char *nom_fichier, matrice *matrice1){
    FILE *fichier = fopen(nom_fichier, "wb");
        if (!fichier) {
        perror("Erreur lors de l'enregistrement du fichier\n");
        exit(EXIT_FAILURE);
    }
    // Écriture nb ligne sur 4 bits
    fwrite(&(*matrice1).ligne, sizeof(int), 1, fichier);
    // Écriture nb colonne sur 4 bits
    fwrite(&(*matrice1).colonne, sizeof(int), 1, fichier);

    // Écriture des lignes avec chaque valeurs sur 4 bits
    for(int i=0; i<(*matrice1).ligne; i++){
        for(int j=0; j<(*matrice1).colonne; j++){
            fwrite(&(*matrice1).tab[i][j], sizeof(float), 1, fichier);           
        }
    }

    fclose(fichier);
    printf("Matrice enregistree !\n");
}

void chargement_matrice(char *nom_fichier, matrice *matrice1){
    FILE *fichier = fopen(nom_fichier, "rb");
    if (!fichier) {
        perror("Erreur lors du chargement du fichier\n");
        exit(EXIT_FAILURE);
    }

    int ligne, colonne;
    // Lecture nb ligne sur 4 bits
    fread(&ligne, sizeof(int), 1, fichier);
    // Lecture nb colonne sur 4 bits
    fread(&colonne, sizeof(int), 1, fichier);

    if((*matrice1).ligne == ligne && (*matrice1).colonne == colonne){
        // Lire des lignes avec chaque valeurs sur 4 bits
        for(int i=0; i<(*matrice1).ligne; i++){
            fread(&(*matrice1).tab[i], sizeof(float), colonne, fichier);
        }
    } else {
        printf("Erreur lors du chargement des matrices : pb de dim !\n");
        printf("(%d,%d)  (%d,%d)", (*matrice1).ligne, (*matrice1).colonne, ligne, colonne);
        exit(EXIT_FAILURE);
    }

    fclose(fichier);
    printf("Matrice chargee !\n");
}
