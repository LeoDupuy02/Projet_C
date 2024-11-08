#ifndef ACTIVATION_H
#define ACTIVATION_H

void ReLU(matrice *matrice);

void sigmoide(matrice *matrice);

void softmax(matrice *matrice);

matrice d_ReLU(matrice *matrice1);

float log_loss(matrice *matrice1, matrice *matrice2);

#endif