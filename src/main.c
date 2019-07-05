#include "general.h"
#include "inicializar.h"
#include "interaccion.h"
#include "avanzar.h"
#include "visualizacion.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define N 512
#define L 9.0//cbrt(N/0.8442) //L tiene que ser mayor a 5 para no tener problemas con nuestro radio de corte.
#define T 0.728
#define H 0.001

int main(){
  double dL;
  double *r, *f, *vel, *r_tabla, *r2_tabla, *f_tabla, *V_tabla, fmax;
  int lines, i, *histograma;
  FILE *fp_tab;
  FILE *fp_en;
  fp_en = fopen("energias.txt", "a");

  fprintf(fp_en, "N %d, L %f, T %f\n",N,L,T);
  fprintf(fp_en, "Ecin\tEpot\tEtot\n");

  srand(time(NULL));

  int N_verlet = 100;

  fp_tab = fopen("tabla_LJ.txt", "r");
  lines = contador_lineas(fp_tab);

  // El formato del filename ".lammpstrj", ese VMD lo lee comodamente
  char fn_vmd[255];
  sprintf(fn_vmd, "prueba.lammpstrj");

  r = malloc(3*N * sizeof(double));
  f = malloc(3*N * sizeof(double));
  vel = malloc(3*N * sizeof(double));
  r_tabla = malloc((lines-1) * sizeof(double));
  r2_tabla = malloc((lines-1) * sizeof(double));
  f_tabla = malloc((lines-1) * sizeof(double));
  V_tabla = malloc((lines-1) * sizeof(double));
  histograma = malloc(2*cbrt(N) * sizeof(int));

  leer_tabla(fp_tab, r_tabla, r2_tabla, f_tabla, V_tabla);

  dL = set_box(r, N, L);
  set_vel(vel, N, T);


  printf("Lado = %f\nCONDICIONES INICIALES\n",L);
  printf("r=%f %f %f\nvel = %f %f %f\nfuerza = %f %f %f\n", *r, *(r+1), *(r+2), *vel, *(vel+1), *(vel+2), *f, *(f+1), *(f+2));

  printf("Histograma vx\n");
  hist(histograma, vel, N, 3, 0);
  printf("Histograma vy\n");
  hist(histograma, vel, N, 3, 1);
  printf("Histograma vz\n");
  hist(histograma, vel, N, 3, 2);


  for(i = 0; i < N_verlet; i++){
    fmax = velocity_verlet(r, vel, f, N, H, L, r2_tabla, f_tabla, V_tabla, lines-1, fp_en);
    printf("%.1f%%, fmax = %lf\n", 100.0*i/N_verlet, fmax);
    if(i%10 == 0)
      save_lammpstrj(fn_vmd, r, vel, N, L, i/10);  // La guardo (append para 0<l)
  }

  printf("CONDICIONES FINALES\n");
  printf("r=%f %f %f\nvel = %f %f %f\nfuerza = %f %f %f\n", *r, *(r+1), *(r+2), *vel, *(vel+1), *(vel+2), *f, *(f+1), *(f+2));

  printf("Histograma vx\n");
  hist(histograma, vel, N, 3, 0);
  printf("Histograma vy\n");
  hist(histograma, vel, N, 3, 1);
  printf("Histograma vz\n");
  hist(histograma, vel, N, 3, 2);

  fclose(fp_tab);
  fclose(fp_en);
  free(r);
  free(f);
  free(vel);
  free(r2_tabla);
  free(f_tabla);
  free(r_tabla);
  free(V_tabla);
  free(histograma);

  return 0;
}
