#ifndef INTERACCION_H
#define INTERACCION_H


int Lennard_Jones(double *potencial, double *fuerza, double *r2, int SIZE);
double forces(double *x, double *f, double *tabla_f, double *tabla_x, int long_tabla, int N);

#endif
