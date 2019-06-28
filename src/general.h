#ifndef GENERAL_H
#define GENERAL_H
#include <stdio.h>

double norma_cuadrado(double *vector, int N);
double gaussiana(double mu, double sigma);
double mean(double *vector, int length, int k, int j);
int find_nearest(double escalar, double *puntero, int longitud_puntero);
int contador_lineas(FILE *file);
int leer_tabla(FILE *file, double *r_tabla, double *r2_tabla, double *f_tabla, double *v_tabla);
double max(double *pointer, int longitud);
double min(double *pointer, int longitud);

#endif
