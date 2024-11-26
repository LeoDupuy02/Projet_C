/* On crée ici un code pour récupérer les informations de la bdd MNIST */
/* D'après CHatGPT les fichiers sont composés comme suit : */
/*   
Images :
    4 bytes : Magic number (0x00000803 pour les images).
    4 bytes : Nombre d'images.
    4 bytes : Nombre de lignes par image (28 pour MNIST).
    4 bytes : Nombre de colonnes par image (28 pour MNIST).
    Les pixels (1 byte par pixel, valeur entre 0 et 255).

Labels (train-labels-idx1-ubyte et t10k-labels-idx1-ubyte) :

    4 bytes : Magic number (0x00000801 pour les labels).
    4 bytes : Nombre de labels.
    Les labels (1 byte par label, valeur entre 0 et 9). 
    
Le set étant de taille convenable on va d'abord le stocker dans un premier temps en entiéreté dans un tableau :
- deux tableaux pour le set d'entrainement
- deux tableaux pour le set de validation 
*/

#include <stdio.h>

int read_32bits(FILE *fp){
    /*permet de retourner un numéro sur 32 bits interprété comme un entier*/

    unsigned char *buffer[4];
    fread(buffer, 1, 4, fp);

    return  *buffer[0] << 24 | *buffer[1] << 16 | *buffer[2] << 8 | *buffer[3];
}
