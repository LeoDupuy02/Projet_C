#include <stdio.h>
#include "matrix.h"

int write_matrix_to_file(matrix *X, char *file){

    FILE *fptr;

    fptr = fopen(*file, "w");
    if (fptr == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    for(int i = 0; i<(*X).column; i++){
        for(int j = 0; j<(*X).row; j++){
            fprintf(fptr, (char)((*X).data[j][i]));
        }
        fprintf(fptr, "\n");
    }
    fprintf(fptr, "/n");

    fclose(fptr);

    return 0;
}

int write_matrices_to_file(matrix **X, char *file, int epoch){

    FILE *fptr;

    fptr = fopen(*file, "w");
    if (fptr == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    fprintf(fptr, (char)epoch);
    fprintf(fptr, ":");
    fprintf(fptr, "\n \n");

    int length = (int)(sizeof(X)/sizeof(X[0]));

    for(int i = 0; i < length; i++){
        write_matrix_to_file(&(X[i]), file);
    }

    return 0;

}

int write_loss_to_file(int epoch, float loss, char *file){

    FILE *fptr;

    fptr = fopen(*file, "w");
    if (fptr == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    fprintf(fptr, (char)epoch);
    fprintf(fptr, " ");
    fprintf(fptr, (char)loss);
    fprintf(fptr, "\n");

    return 0;

}