#include "general.h"
#include "inicializar.h"
#include "interaccion.h"
#include "avanzar.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define N 512
#define L cbrt(N/0.8442) //L tiene que ser mayor a 5 para no tener problemas con nuestro radio de corte.
#define T 1
#define H 0.001

int main(){
  double dL;
  double *r, *f, *vel, *r2_tabla, *r_tabla, *f_tabla, *V_tabla;
  int lines, i;
  FILE *file;

  file = fopen( "tabla_LJ.txt", "r");
  lines = contador_lineas(file);

  r = malloc(3*N * sizeof(double));
  f = calloc(3*N, sizeof(double));
  vel = malloc(3*N * sizeof(double));
  r_tabla = malloc((lines-1) * sizeof(double));
  r2_tabla = malloc((lines-1) * sizeof(double));
  f_tabla = malloc((lines-1) * sizeof(double));
  V_tabla = malloc((lines-1) * sizeof(double));

  dL = set_box(r, N, L);
  set_vel(vel, N, T);

  leer_tabla(file, r_tabla, r2_tabla, f_tabla, V_tabla);
  printf("Condiciones iniciales\n");
  printf("r=%f %f %f\nvel = %f %f %f\nfuerza = %f %f %f\n", *r, *(r+1), *(r+2), *vel, *(vel+1), *(vel+2), *f, *(f+1), *(f+2));

  for(i = 0; i < 5; i++){
    printf("paso %d\n", i);
    velocity_verlet(r, vel, f, N, H, L, r2_tabla, f_tabla, lines-1);
    printf("r=%f %f %f\nvel = %f %f %f\nfuerza = %f %f %f\n", *r, *(r+1), *(r+2), *vel, *(vel+1), *(vel+2), *f, *(f+1), *(f+2));
  }

  printf("Final\n");
  printf("r=%f %f %f\nvel = %f %f %f\nfuerza = %f %f %f\n", *r, *(r+1), *(r+2), *vel, *(vel+1), *(vel+2), *f, *(f+1), *(f+2));

  fclose(file);

  free(r);
  free(f);
  free(vel);
  free(r2_tabla);
  free(f_tabla);
  free(r_tabla);
  free(V_tabla);

  return 0;
}
