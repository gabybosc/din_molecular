#include "general.h"
#include "inicializar.h"
// #include "interaccion.h"
// #include "tabla.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define N 27

int main(){
  double dL;
  double *r, *f, *r_tabla, *f_tabla;
  double r_LUT, r2_LUT, f_LUT, v_LUT;
  int i=0;
  FILE * file;
  file = fopen( "tabla_LJ.txt", "r");

  r = malloc(3*N * sizeof(double));
  f = calloc(3*N, sizeof(double));
  r_tabla = malloc(100000000 * sizeof(double));
  f_tabla = malloc(100000000 * sizeof(double));

  dL = set_box(x, N, 10);
  printf("dL = %f\n",dL);
  // forces(x, f, tabla_f, tabla_x, long_tabla);

  while (fscanf(file, "%lf %lf %lf %lf", &r_LUT, &r2_LUT, &f_LUT, &v_LUT) != EOF){
    *(f_tabla+i) = f_LUT;
    *(r_tabla+i) = r_LUT;
    i += 1;
  }

  fclose(file);

  free(r);
  free(f);
  free(r_tabla);
  free(f_tabla);

  return 0;
}
