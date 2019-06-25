#ifndef GENERAL_H
#define GENERAL_H

double norma_cuadrado(double *vector, int N);
double gaussiana(double mu, double sigma);
double mean(double *vector, int length, int k, int j);
int find_nearest(double escalar, double *puntero, int longitud_puntero);

#endif
