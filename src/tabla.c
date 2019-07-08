#include "general.h"
#include "interaccion.h"
#include "tabla.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

int make_tabla(int SIZE){
	double *potencial, *fuerza, *r, *r2;
	double r0 = 0.001;
	double r_max = 2.5;
	int i;
	FILE *fp;

	r = malloc(SIZE * sizeof(double));
	r2 = malloc(SIZE * sizeof(double));
	fuerza = malloc(SIZE * sizeof(double));
	potencial = malloc(SIZE * sizeof(double));

	*r = r0;

	for(i = 1; i < SIZE; i++)
		*(r+i) = r0 + (r_max * i)/SIZE;

	for(i = 0; i < SIZE; i++)
		*(r2+i) = *(r+i) * *(r+i);

	Lennard_Jones(potencial, fuerza, r2, SIZE);

	fp = fopen("tabla_LJ.txt", "w");
	
	for(i = 0; i < SIZE; i++){
		fprintf(fp, "%.9f\t%.9f\t%.9f\t%.9f\n", *(r+i),*(r2+i),*(fuerza+i),*(potencial+i));
	}
	fprintf(fp, "r\tr2\tfuerza\tpotencial\n");

	return 0;
}
