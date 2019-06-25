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

double forces(double *x, double *f, double *tabla_f, double *tabla_x, int long_tabla){ //*f tiene que estar calloc-queada
  int i, j, indice;
  double r2;

  for(i = 1; i < N; i++){
    r2 = pow(*x - *(x+3*i), 2) + pow(*(x+1) - *(x+3*i+1), 2) + pow(*(x+2) - *(x+3*i+2), 2);
    indice = find_nearest(r2, *tabla_x, long_tabla);
    *f += *(tabla_f+indice);
  }

return 0;
}
