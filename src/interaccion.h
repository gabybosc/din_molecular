#ifndef INTERACCION_H
#define INTERACCION_H


int Lennard_Jones(double *potencial, double *fuerza, double *r2, int SIZE);
double forces(double *r, double *f, double *tabla_r2, double *tabla_f, int long_tabla, int N, double L);
int CCP(double *r, int N, double L);
double coef_verlet(double *r, int N, double L);

#endif
