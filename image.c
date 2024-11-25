#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

#define CHAMANE

#ifndef CHAMANE

float** char_to_float_bw(unsigned char* img, int size, int channels){

    /* Crée un tableau de float à partir d'un tableau de char. Il ne garde que le premier canal. */

    float **new_img = (float**)malloc(size*sizeof(float*));
    if( new_img == NULL ){
        fprintf(stderr, "Erreur dans la transformation du tableau de char en float");
        return NULL;
    }
    for(int i = 0; i<size ; i++){
        *(new_img+i) = (float *)malloc(1*sizeof(float));
        *(*(new_img + i)) = (float)img[i*channels];
    }

    return new_img;

}

matrix vector_to_matrix(float** img, int size){

    matrix V;
    V.row = size;
    V.column = 1;
    V.data = img;

    return V;
}

matrix image_to_vector(const char *array) {

    /* Récupére une image dans un vecteur colonne */
    /* array est l'adresse de l'image à charger, img est le pointeur vers le vecteur colonne */
    /* la structure matrice associée au vecteur */

    int width, height, channels;
    unsigned char *img = stbi_load(array, &width, &height, &channels,1);
    if(img == NULL){
        fprintf(stderr,"Erreur dans le chargement de l'image : %s \n", array);
        return NULL;
    }

    float **new_img = char_to_float_bw(img, width*height, channels);

    matrix V = vector_to_matrix(new_img, width*height);

    return V;

}

matrix image_resize(const char *array, int new_width, int new_height){

    /* chargement de l'image */
    int width, height, channels;
    unsigned char *img = stbi_load(array, &width, &height, &channels,1);
    if(img == NULL){
        fprintf(stderr,"Erreur dans le chargement de l'image : %s \n", array);
        return NULL;
    }
    

    /* allocation de l'espace mémoire pour l'image redimensionnée */
    unsigned char* resized_image = (unsigned char*)malloc(new_width * new_height * channels);
    if (resized_image == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour l'image redimensionnée\n");
        stbi_image_free(img);
        return NULL;
    }

    /* redimenssionnement de l'image */
    int result = stbir_resize_uint8(img, width, height, 0, resized_image, new_width, new_height, 0, channels);

    /* check le redimenssionnement */
    if (result == 0) {
        fprintf(stderr, "Erreur lors du redimensionnement de l'image\n");
        free(resized_image);
        stbi_image_free(img);
        return NULL;
    }

    float **new_img = char_to_float_bw(resized_image, new_width*new_height, channels);

    matrix V = vector_to_matrix(new_img, new_width*new_height);

    return new_img;
}

#endif CHAMANE