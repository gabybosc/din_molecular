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

#define N 125
#define T 1.5
#define H 0.001

int main(){
  double dL, entropia, Epot, Ecin, rho, L;
  double *r, *f, *vel, *r_tabla, *r2_tabla, *f_tabla, *V_tabla;
  int lines, i, j=0;
  FILE *fp_tab;
  FILE *fp_en;
  srand(time(NULL));
  clock_t tic = clock();
  
  int N_verlet = 1000;
  int paso = 5;
  
  fp_tab = fopen("tabla_LJ.txt", "r");
  lines = contador_lineas(fp_tab);

  r = malloc(3*N * sizeof(double));
  f = malloc(3*N * sizeof(double));
  vel = malloc(3*N * sizeof(double));
  r_tabla = malloc((lines-1) * sizeof(double));
  r2_tabla = malloc((lines-1) * sizeof(double));
  f_tabla = malloc((lines-1) * sizeof(double));
  V_tabla = malloc((lines-1) * sizeof(double));

  leer_tabla(fp_tab, r_tabla, r2_tabla, f_tabla, V_tabla);

  char fn_en[255];
  char fn_vmd[255];
  
  for (rho=0.6; rho<1.1; rho+=0.2){//loop rho
	L=cbrt(N/rho);
	sprintf(fn_en, "radial_rho%.1f.txt",rho);
	fp_en = fopen(fn_en, "a");
	fprintf(fp_en, "N %d, L %f, rho %.1f\n",N,L,rho);
	fprintf(fp_en, "Ecin\tEpot\tH\n");
	  
	sprintf(fn_vmd, "radial_rho%.1f.lammpstrj",rho);

	//inicializo
	dL = set_box(r, N, L);
	set_vel(vel, N, T);
	  
	for(i = 0; i < N_verlet; i++){
	  Epot = velocity_verlet(r, vel, f, N, H, L, r2_tabla, f_tabla, V_tabla, lines-1);
	  if(i%paso == 0){
	    entropia = teo_h(vel, N);
	    Ecin = cinetica(vel, N);
	    fprintf(fp_en, "%lf\t%lf\t%lf\n",Ecin,Epot,entropia);
	    printf("%.1f%%\n", 100.0*(j*N_verlet+i)/(N_verlet*3));
	    save_lammpstrj(fn_vmd, r, vel, N, L, (j*N_verlet+i)/paso);
	  }
	}//end verlet
	  
	fclose(fp_en);
	j++;
  }//end loop rho
  
  fclose(fp_tab);
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
