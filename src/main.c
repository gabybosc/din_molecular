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
#define L cbrt(N/0.8442) //L tiene que ser mayor a 5 para no tener problemas con nuestro radio de corte.
#define T 1
#define H 0.001

int main(){
  // double dL;
  double *r, *f, *vel, *r_tabla, *r2_tabla, *f_tabla, *V_tabla, fmax;
  int lines, i, *histograma;
  int frame_file;
  FILE *fp_tab, *fp_en, *fp_lambda, *fp_lammps;
  fp_en = fopen("energias.txt", "a");
  fp_lambda = fopen("coef_verlet.txt", "a");
  fp_lammps = fopen("prueba_1000pasos.lammpstrj", "r");

  srand(time(NULL));

  int N_verlet = 3000;

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

  frame_file = load_lammpstrj(fp_lammps, r, vel, N, L, 99);

  // dL = set_box(r, N, L);
  // set_vel(vel, N, T);

  forces(r, f, r2_tabla, f_tabla, V_tabla, lines, N, L);
  printf("Lado = %f, frame_file = %d\nCONDICIONES INICIALES\n",L, frame_file);
  printf("r=%f %f %f\nvel = %f %f %f\nfuerza = %f %f %f\n", *r, *(r+1), *(r+2), *vel, *(vel+1), *(vel+2), *f, *(f+1), *(f+2));

  for(i = 0; i < N_verlet; i++){
    fmax = velocity_verlet(r, vel, f, N, H, L, r2_tabla, f_tabla, V_tabla, lines-1, fp_en);
    coef_verlet(r, N, L, fp_lambda);

    if(i%10 == 0){
      printf("%.1f%%, fmax = %lf\n", 100.0*i/N_verlet, fmax);
      save_lammpstrj(fn_vmd, r, vel, N, L, i/10);
    }
  }

  printf("CONDICIONES FINALES\n");
  printf("r=%f %f %f\nvel = %f %f %f\nfuerza = %f %f %f\n", *r, *(r+1), *(r+2), *vel, *(vel+1), *(vel+2), *f, *(f+1), *(f+2));
  printf("\a");
  /*
  printf("Histograma vx\n");
  hist(histograma, vel, N, 3, 0);
  printf("Histograma vy\n");
  hist(histograma, vel, N, 3, 1);
  printf("Histograma vz\n");
  hist(histograma, vel, N, 3, 2);
  */
  fclose(fp_tab);
  fclose(fp_en);
  fclose(fp_lambda);
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
//
// r=0.677450 0.503586 0.129177
// vel = -0.215063 0.257087 0.191255
// fuerza = -8.608441 -6.167530 1.089648
