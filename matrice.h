#ifndef MATRICE_H
#define MATRICE_H

typedef struct _matrice matrice;
struct _matrice{
    int ligne;
    int colonne;
    float **tab;

};

matrice creation_matrice(int ligne, int colonne);

void liberation_matrice(matrice *matrice);

void affichage_matrice(matrice *matrice);

void dimension_matrice(matrice *matrice);

void remplissage_n(matrice *matrice, float n);

void remplissage(matrice *matrice, float *liste);

matrice prod_matriciel(matrice *matrice1, matrice *matrice2);

matrice soustraction_matriciel(matrice *matrice1, matrice *matrice2);

matrice transposee(matrice *matrice1);

void multiplication_scalaire(matrice *matrice1, float n);

void somme_matrice_b(matrice *matrice1, matrice *matrice2);

matrice somme_colonne(matrice *matrice1);

void prod_Hadamard(matrice *matrice1, matrice *matrice2);

matrice cp_matrice(matrice *matrice1);

void initialiser_poids_he(matrice *matrice);

void initialiser_matrice_biais(matrice *matrice);


#endif