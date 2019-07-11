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
#define T 0.9
#define H 0.001

int main(){
  double dL, entropia, Epot, Ecin;
  double *r, *f, *vel, *r_tabla, *r2_tabla, *f_tabla, *V_tabla;
  int lines, i;
  FILE *fp_tab;
  FILE *fp_en;
  srand(time(NULL));
  clock_t tic = clock();
  
  int N_verlet = 1000;
  
  char fn_en[255];
  sprintf(fn_en, "energiasL%.2fT%.1f.txt",L,T);
  fp_en = fopen(fn_en, "a");
  fprintf(fp_en, "N %d, L %f, T %f\n",N,L,T);
  fprintf(fp_en, "Ecin\tEpot\tH\n");

  fp_tab = fopen("tabla_LJ.txt", "r");
  lines = contador_lineas(fp_tab);

  char fn_vmd[255];
  sprintf(fn_vmd, "L%.2fT%.1f.lammpstrj",L,T);

  r = malloc(3*N * sizeof(double));
  f = malloc(3*N * sizeof(double));
  vel = malloc(3*N * sizeof(double));
  r_tabla = malloc((lines-1) * sizeof(double));
  r2_tabla = malloc((lines-1) * sizeof(double));
  f_tabla = malloc((lines-1) * sizeof(double));
  V_tabla = malloc((lines-1) * sizeof(double));

  leer_tabla(fp_tab, r_tabla, r2_tabla, f_tabla, V_tabla);

  //inicializo
  dL = set_box(r, N, L);
  set_vel(vel, N, T);
  
  for(i = 0; i < N_verlet; i++){
    Epot = velocity_verlet(r, vel, f, N, H, L, r2_tabla, f_tabla, V_tabla, lines-1);
	if(i%5 == 0){
	  entropia = teo_h(vel, N);
	  Ecin = cinetica(vel, N);
	  fprintf(fp_en, "%lf\t%lf\t%lf\n",Ecin,Epot,entropia);
	  printf("%d%%\n", 100*i/N_verlet);
	}
  }//end verlet
  
  save_lammpstrj(fn_vmd, r, vel, N, L, 0); //guardo solo el ultimo frame
  
  fclose(fp_tab);
  fclose(fp_en);
  free(r);
  free(f);
  free(vel);
  free(r2_tabla);
  free(f_tabla);
  free(r_tabla);
  free(V_tabla);
  clock_t toc = clock();
  printf("\nDuracion: %.1f minutos (%.2f horas)\a\n", (double)(toc - tic) / (CLOCKS_PER_SEC*60),(double)(toc - tic) / (CLOCKS_PER_SEC*3600));

  return 0;
}
