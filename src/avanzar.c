#include "general.h"
#include "interaccion.h"
#include "inicializar.h"
#include "avanzar.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

int velocity_verlet(double *r, double *v, double *f, int N, double h, double L, double *tabla_r2, double *tabla_f, int long_tabla){
  double f_buffer[3*N];
  int i;

  //avanzamos x, y, z de la partícula 0
  *r = *r + *v *h + *f * pow(h,2)/2;
  *(r+1) = *(r+1) + *(v+1) *h + *(f+1) * pow(h,2)/2;
  *(r+2) = *(r+2) + *(v+2) *h + *(f+2) * pow(h,2)/2;

  CCP(r,N,L);

  for(i=0; i < 3*N; i++)
    f_buffer[i] = *(f+i);

  forces(r, f, tabla_r2, tabla_f, long_tabla, N, L);

  //avanzamos vx, vy, vz de la particula 0
  *v = *v + (f_buffer[0] + *f) * h/2;
  *(v+1) = *(v+1) + (f_buffer[1] + *(f+1)) * h/2;
  *(v+2) = *(v+2) + (f_buffer[2] + *(f+2)) * h/2;

  return 0;
}
