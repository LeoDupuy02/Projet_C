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
#include "matrix.c"

int read_32bits(FILE *fp){
    /*permet de retourner un numéro sur 32 bits interprété comme un entier*/

    unsigned char buffer[4];
    fread(buffer, 1, 4, fp);

    return buffer[0] << 24 | buffer[1] << 16 | buffer[2] << 8 | buffer[3];
}

float read_byte(FILE *fp){
    /*permet de retourner un numéro flotant sur 8 bits*/

    unsigned char buffer[1];
    fread(buffer, 1, 1, fp);

    float retour = (float)buffer[0];

    return retour;
}

int *get_data_mnist(FILE *fp){

    int *output[3];
    int validation;

    validation = read_32bits(fp);
    if(validation != 2051){
        printf("Les données entrées ne sont pas des images...");
        return NULL;
    }

    output[0] = read_32bits(fp);
    output[1] = read_32bits(fp);
    output[2] = read_32bits(fp);

    return output;
}

void load_images(matrix *output, int nb, int width, int height, FILE *fp){

    (*output).column = nb;
    (*output).row = width*height;
    
    (*output).data = (float**)malloc( nb*sizeof(float *) );

    for(int i = 0; i<nb; i++){
        ((*output).data)[i] = (float*)malloc( height*width*sizeof(float));
        for(int j = 0; j<width*height; j++){
            ((*output).data[i])[j] = read_byte(fp);
        }
    }
}

void print_image_MNIST(matrix *input, int image_nb){
    for( int j = 0; j<28; j++){
        for(int i = 0; i<28; i++){
            if((*input).data[image_nb][i+j*28] > 127){
                printf("#");
            }
            else{
                printf("0");
            }
        }
        printf("\n");
    }
}

void main(){

    FILE *f = fopen("train-images.idx3-ubyte","rw");
    read_32bits(f);
    int nb = read_32bits(f);
    printf("%d \n", nb);
    int height= read_32bits(f);
    printf("%d \n", height);
    int width = read_32bits(f);
    printf("%d \n", width);

    matrix images_MNIST;
    load_images(&images_MNIST,nb,width,height,f);

    print_image_MNIST(&images_MNIST, 750);

}

