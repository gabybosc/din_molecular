#ifndef AVANZAR_H
#define AVANZAR_H

int velocity_verlet(double *r, double *v, double *f, int N, double h, double L, double *tabla_r2,double *tabla_f, int long_tabla);
int hist(double *puntero, int longitud, int k, int j);

#endif
