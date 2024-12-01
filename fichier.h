#ifndef FICHIER_H
#define FICHIER_H

void train_images(char *nom_fichier, matrice *X, int num_images);

void train_labels(const char *nom_fichier, matrice *Y, int num_images);

void test_images(char *nom_fichier, matrice *X_test, int num_images);

void test_labels(const char *nom_fichier, matrice *Y_test, int num_images);

void enregistrement_matrice(char *nom_fichier, matrice *matrice1);

void chargement_matrice(char *nom_fichier, matrice *matrice1);

#endif