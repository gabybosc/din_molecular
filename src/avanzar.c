#include "general.h"
#include "interaccion.h"
#include "inicializar.h"
#include "avanzar.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

int velocity_verlet(double *r, double *v, double *f, int N, double h, double L, double *tabla_r2, double *tabla_f, int long_tabla){
	int i;
	
	double f_buffer[3*N]; //para almacenar la fuerza del paso temporal anterior
	for(i=0; i < 3*N; i++)
		f_buffer[i] = *(f+i);

	//avanzamos x, y, z de la partícula i
	for (i=0; i<N; i++){
		*(r+3*i) = *(r+3*i) + *(v+3*i) *h + *(f+3*i) * pow(h,2)/2;
		*(r+3*i+1) = *(r+3*i+1) + *(v+3*i+1) *h + *(f+3*i+1) * pow(h,2)/2;
		*(r+3*i+2) = *(r+3*i+2) + *(v+3*i+2) *h + *(f+3*i+2) * pow(h,2)/2;
	}//end loop i posicion
	
	CCP(r,N,L);

	forces(r, f, tabla_r2, tabla_f, long_tabla, N, L);

	//avanzamos vx, vy, vz de la particula i
	for (i=0; i<N; i++){
		*(v+3*i) = *(v+3*i) + (f_buffer[3*i] + *(f+3*i)) * h/2;
		*(v+3*i+1) = *(v+3*i+1) + (f_buffer[3*i+1] + *(f+3*i+1)) * h/2;
		*(v+3*i+2) = *(v+3*i+2) + (f_buffer[3*i+2] + *(f+3*i+2)) * h/2;
	}//end loop i velocidad
	return 0;
}


int hist(int *histograma, double *velocidades, int longitud, int k, int j){
	int i, indice, n_bins;
	double *vector;
	double maxvalue, minvalue, width;
	
	vector = malloc(longitud * sizeof(double));
	for (i=0; i<longitud; i++)
		*(vector+i) = *(velocidades+(k*i+j)); //recorre de a k lugares, con offset j
		
	maxvalue = max(vector, longitud);
	minvalue = min(vector, longitud);
	n_bins = 2*cbrt(longitud);
	width=(maxvalue - minvalue)/n_bins;	
	
	//nota: se podria cambiar el tamaño del histograma con histograma=realloc(histograma,n*sizeof(int)); 
	for (i=0; i<n_bins; i++)
		*(histograma+i)=0;
	
	for (i=0; i<longitud; i++){
		if (*(vector+i)==maxvalue){
			indice = n_bins-1;
		}else{
			indice = (int)((*(vector+i) - minvalue)/width);
		}
		*(histograma+indice)+=1;
	}//end loop i
	
	for (i=0; i<n_bins; i++)
		printf("%d ",*(histograma+i));
	printf("\n");
	
	free(vector);
	return 0;
}
