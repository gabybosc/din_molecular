#include "general.h"
#include "interaccion.h"
#include "tabla.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

int make_tabla(int SIZE){
  double *potencial, *fuerza, *r2;
  double r0 = 0.001;
  double r_max = 2.5;
  int i;
	FILE *fp;

  r2 = malloc(SIZE * sizeof(double));
  fuerza = malloc(SIZE * sizeof(double));
  potencial = malloc(SIZE * sizeof(double));

  *r2 = r0;

  for(i = 1; i < SIZE; i++){
    *(r2+i) = r0 + (r_max * i)/SIZE;
  }

  Lennard_Jones(potencial, fuerza, r2, SIZE);

	char fn[50];
	sprintf(fn, "tabla_LJ.txt");
	fp = fopen(fn, "w");
  fprintf(fp, "r0 = %f, r_max = %f, size = %d", r0, r_max, SIZE);
	fprintf(fp, "\nr2\tfuerza\tpotencial");

  for(i = 0; i < SIZE; i++){
    fprintf(fp, "\n%lf\t%lf\t%lf", *(r2+i),*(fuerza+i),*(potencial+i));
  }


  return 0;
}
