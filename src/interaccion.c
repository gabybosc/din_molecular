#include "general.h"
#include "interaccion.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

int Lennard_Jones(double *potencial, double *fuerza, double *r2, int SIZE){//calcula el pot y la fuerza de LJ para r² con epsilon = sigma = 1
  double offset = 4 * (pow(2.5, -12) - pow(2.5, -6));
  double r6, r;
  int i;

  for (i = 0; i < SIZE; i++){
    r6 = pow(*(r2+i), -3); //es r⁻⁶
    r = sqrt(*(r2+i));

    *(potencial+i) = 4 * (r6 * ( r6 - 1)) - offset;
    *(fuerza + i) = 24 * r6/r * (2 * r6 - 1); //si trabajamos con r2 en lugar de r
    // *(fuerza + i) = 24 * r6 * (2 * r6 - 1);
  }
  return 0;
}

double forces(double *r, double *f, double *tabla_f, double *tabla_r, int long_tabla, int N){ //*f tiene que estar calloc-queada
  int i, j, indice;
  double x, y, z, r2, fuerza_par;
// vamos a necesitar: x, y, z, fuerza_par
  for(i = 1; i < N; i++){
    x = *r - *(r+3*i);
    y = *(r+1) - *(r+3*i+1);
    z = *(r+2) - *(r+3*i+2);
    r2 = pow(x, 2) + pow(y, 2) + pow(z, 2);
    indice = find_nearest(r2, tabla_r, long_tabla);
    fuerza_par = *(tabla_f+indice);
    *f += fuerza_par * x / sqrt(r2); //fx
    *(f+1) += fuerza_par * y / sqrt(r2); //fy
    *(f+2) += fuerza_par * z / sqrt(r2); //fz
  }
  printf("indice = %f\n", indice); //corregir find_nearest
return 0;
}
