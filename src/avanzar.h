#ifndef AVANZAR_H
#define AVANZAR_H

double velocity_verlet(double *r, double *v, double *f, int N, double h, double L, double *tabla_r2,double *tabla_f, double *tabla_v, int long_tabla);
double velocity_verlet_presion(double *r, double *v, double *f, int N, double h, double L, double *tabla_r2, double *tabla_f, double *tabla_v, int long_tabla, double *pres);
double cinetica(double * vel, int N);

#endif
