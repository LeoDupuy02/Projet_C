#ifndef FICHIER_H
#define FICHIER_H

int lire_int(FILE *fichier);

void charger_images(const char *nom_fichier, matrice *X, int num_images, int taille_image);

void charger_labels(const char *nom_fichier, matrice *Y, int num_images);

#endif