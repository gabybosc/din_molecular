#include "general.h"
#include "interaccion.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

int Lennard_Jones(double *potencial, double *fuerza, double *r2, int SIZE){//calcula el pot y la fuerza de LJ para r² con epsilon = sigma = 1
  double offset = 4 * (pow(2.5, -12) - pow(2.5, -6));
  double r, r6;
  int i;

  for (i = 0; i < SIZE; i++){
    r6 = pow(*(r2+i), -3); //es r⁻⁶
    r = sqrt(*(r2+i));

    *(potencial+i) = 4 * (r6 * ( r6 - 1)) - offset;
    *(fuerza + i) = 24 * r6/r * (2 * r6 - 1);
  }
  return 0;
}
