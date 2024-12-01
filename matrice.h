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

void prod_matriciel(matrice *matrice_finale, matrice *matrice1, matrice *matrice2);

void soustraction_matriciel(matrice *matrice_finale, matrice *matrice1, matrice *matrice2, float learning_rate);

matrice transposee(matrice *matrice1);

void multiplication_scalaire(matrice *matrice1, float n);

void somme_matrice_b(matrice *matrice1, matrice *matrice2);

void somme_colonne(matrice *matrice_finale, matrice *matrice1);

void prod_Hadamard(matrice *matrice1, matrice *matrice2);

void cp_matrice(matrice *matrice_finale, matrice *matrice1);

void initialiser_poids_he(matrice *matrice);

void initialiser_matrice_biais(matrice *matrice);


#endif