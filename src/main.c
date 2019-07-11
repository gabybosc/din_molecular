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
#define RO 0.4
#define L cbrt(N/RO) //L tiene que ser mayor a 5 para no tener problemas con nuestro radio de corte.
//#define T 0.65
#define H 0.001

int main(){
  double dL, entropia, Epot, Ecin, T, T_old;
  double *r, *f, *vel, *r_tabla, *r2_tabla, *f_tabla, *V_tabla, *pres;
  int lines, i, j=0;
  FILE *fp_tab;
  FILE *fp_en;
  srand(time(NULL));
  clock_t tic = clock();
  
  int N_verlet = 500;
  int paso = 5;
  double T_min = 0.4;
  double T_max = 2.0;
  double T_paso = 0.1;
  int T_cant = (T_max - T_min)/T_paso;
  
  char fn_en[255];
  sprintf(fn_en, "energiasTs_N%dL%.2f.txt",N,L);
  fp_en = fopen(fn_en, "a");
  fprintf(fp_en, "N %d, L %f, ro %f\n",N,L,RO);
  fprintf(fp_en, "Ecin\tEpot\tH\tP\n");

  fp_tab = fopen("tabla_LJ.txt", "r");
  lines = contador_lineas(fp_tab);

  char fn_vmd[255];
  sprintf(fn_vmd, "N%dL%.2f.lammpstrj",N,L);

  r = malloc(3*N * sizeof(double));
  f = malloc(3*N * sizeof(double));
  vel = malloc(3*N * sizeof(double));
  r_tabla = malloc((lines-1) * sizeof(double));
  r2_tabla = malloc((lines-1) * sizeof(double));
  f_tabla = malloc((lines-1) * sizeof(double));
  V_tabla = malloc((lines-1) * sizeof(double));
  
  pres = malloc(sizeof(double));

  leer_tabla(fp_tab, r_tabla, r2_tabla, f_tabla, V_tabla);
  
  //inicializo
  T_old = T_max;
  dL = set_box(r, N, L);
  set_vel(vel, N, T_old);
  
  for (T = T_max; T>=T_min; T-=T_paso){//loop T
	  printf("T = %lf\n",T);
	  
	  //rescaling de velocidades
	  for (i = 0; i<3*N; i++)
		  *(vel+i) = sqrt(T/T_old) * *(vel+i);
	  
	  for(i = 0; i < N_verlet; i++){
		Epot = velocity_verlet_presion(r, vel, f, N, H, L, r2_tabla, f_tabla, V_tabla, lines-1,pres);
		if(i%paso == 0){
		  entropia = teo_h(vel, N);
		  Ecin = cinetica(vel, N);
		  fprintf(fp_en, "%lf\t%lf\t%lf\t%lf\n",Ecin,Epot,entropia,*pres);
		  printf("%.1f%%\n", 100.0*(j*N_verlet+i)/(N_verlet*T_cant));
		  save_lammpstrj(fn_vmd, r, vel, N, L, (j*N_verlet+i)/paso);
		}
	  }//end verlet
	  j++;
	  T_old = T;
  }//end loop T
  
  //save_lammpstrj(fn_vmd, r, vel, N, L, 0); //guardo solo el ultimo frame
  
  fclose(fp_tab);
  fclose(fp_en);
  free(r);
  free(f);
  free(vel);
  free(r2_tabla);
  free(f_tabla);
  free(r_tabla);
  free(V_tabla);
  free(pres);
  clock_t toc = clock();
  printf("\nDuracion: %.1f minutos (%.2f horas)\a\n", (double)(toc - tic) / (CLOCKS_PER_SEC*60),(double)(toc - tic) / (CLOCKS_PER_SEC*3600));

  return 0;
}
