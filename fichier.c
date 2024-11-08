#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "matrice.h"


// Fonction pour lire un entier de 4 octets (format big-endian) dans le fichier
int lire_int(FILE *fichier){
    int valeur = 0;
    for (int i = 0; i < 4; i++) {
        valeur = (valeur << 8) | fgetc(fichier);
    }
    return valeur;
}

// Lecture du fichier d'images et stockage dans la matrice X
void charger_images(const char *nom_fichier, matrice *X, int num_images, int taille_image){
    FILE *fichier = fopen(nom_fichier, "rb");
    if (!fichier) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier d'images.\n");
        exit(1);
    }

    // Lecture de l'en-tête
    lire_int(fichier);  // Magic number
    int nb_images = lire_int(fichier);
    int nb_lignes = lire_int(fichier);
    int nb_colonnes = lire_int(fichier);

    if (nb_images < num_images || nb_lignes * nb_colonnes != taille_image) {
        fprintf(stderr, "Les dimensions de l'image ne correspondent pas aux attentes.\n");
        exit(1);
    }

    // Lecture des images et stockage dans X
    for (int i = 0; i < num_images; i++) {
        for (int j = 0; j < taille_image; j++) {
            X->tab[j][i] = fgetc(fichier) / 255.0;  // Normalisation
        }
    }

    fclose(fichier);
}

// Lecture du fichier de labels et stockage dans la matrice Y
void charger_labels(const char *nom_fichier, matrice *Y, int num_images){

    FILE *fichier = fopen(nom_fichier, "rb");
    if (!fichier) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de labels.\n");
        exit(1);
    }

    // Lecture de l'en-tête
    lire_int(fichier);  // Magic number
    int nb_labels = lire_int(fichier);

    if (nb_labels < num_images) {
        fprintf(stderr, "Le nombre de labels est inférieur au nombre d'images.\n");
        exit(1);
    }

    // Lecture des labels et stockage dans Y
    for (int i = 0; i < num_images; i++) {
        int label = fgetc(fichier);
        if (label >= 0 && label < 10) {
            Y->tab[label][i] = 1.0;  // Encodage one-hot
        }
    }

    fclose(fichier);
}
