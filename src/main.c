#include "general.h"
#include "inicializar.h"
#include "interaccion.h"
#include "avanzar.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define T 5 //0.728
#define RO 0.8442
#define N 216 // N tiene que ser un cubo: 27 (cambiar el lado o densidad), 216, 343, 512
#define L cbrt(N/RO) //L tiene que ser >5 para no tener problemas con el radio de corte
#define H 0.005//0.001

int main(){
	double dL;
	double *r, *f, *vel, *r_tabla, *r2_tabla, *f_tabla, *V_tabla;
	int lines, i, *histograma;
	FILE *file;
	srand(time(NULL));

	file = fopen( "tabla_LJ.txt", "r");
	lines = contador_lineas(file);

	r = malloc(3*N * sizeof(double));
	f = malloc(3*N * sizeof(double));
	vel = malloc(3*N * sizeof(double));
	r_tabla = malloc((lines-1) * sizeof(double));
	r2_tabla= malloc((lines-1) * sizeof(double));
	f_tabla = malloc((lines-1) * sizeof(double));
	V_tabla = malloc((lines-1) * sizeof(double));
	histograma = malloc(2*cbrt(N) * sizeof(int));
	
	leer_tabla(file, r_tabla, r2_tabla, f_tabla, V_tabla);

	dL = set_box(r, N, L);
	set_vel(vel, N, T);

	printf("CONDICIONES INICIALES\n");
	printf("r\t= %lf %lf %lf\nvel\t= %lf %lf %lf\nfuerza\t= %lf %lf %lf\n", *r, *(r+1), *(r+2), *vel, *(vel+1), *(vel+2), *f, *(f+1), *(f+2));

	printf("Histograma vx\n");
	hist(histograma, vel, N, 3, 0);
	printf("Histograma vy\n");
	hist(histograma, vel, N, 3, 1);
	printf("Histograma vz\n");
	hist(histograma, vel, N, 3, 2);
	
	for(i = 0; i < 100; i++)
		velocity_verlet(r, vel, f, N, H, L, r2_tabla, f_tabla, lines-1);

	printf("CONDICIONES FINALES\n");
	printf("r\t= %lf %lf %lf\nvel\t= %lf %lf %lf\nfuerza\t= %lf %lf %lf\n", *r, *(r+1), *(r+2), *vel, *(vel+1), *(vel+2), *f, *(f+1), *(f+2));
	
	printf("Histograma vx\n");
	hist(histograma, vel, N, 3, 0);
	printf("Histograma vy\n");
	hist(histograma, vel, N, 3, 1);
	printf("Histograma vz\n");
	hist(histograma, vel, N, 3, 2);

	fclose(file);
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
