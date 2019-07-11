#include "general.h"
#include "interaccion.h"
#include "avanzar.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

double velocity_verlet(double *r, double *v, double *f, int N, double h, double L, double *tabla_r2, double *tabla_f, double *tabla_v, int long_tabla){
	int i;
	double h2 = h*h/2;
	//double fmax;
	double Epot;

	double f_buffer[3*N]; //para almacenar la fuerza del paso temporal anterior
	for(i=0; i < 3*N; i++)
		f_buffer[i] = *(f+i);

	//avanzamos x, y, z de la partícula i
	for (i=0; i<N; i++){
		*(r+3*i) += *(v+3*i) *h + *(f+3*i) * h2;
		*(r+3*i+1) += *(v+3*i+1) *h + *(f+3*i+1) * h2;
		*(r+3*i+2) += *(v+3*i+2) *h + *(f+3*i+2) * h2;
	}//end loop i posicion

	CCP(r,N,L);

	Epot = forces(r, f, tabla_r2, tabla_f, tabla_v, long_tabla, N, L);

	//avanzamos vx, vy, vz de la particula i
	for (i=0; i<N; i++){
		*(v+3*i) += (f_buffer[3*i] + *(f+3*i)) * h/2;
		*(v+3*i+1) += (f_buffer[3*i+1] + *(f+3*i+1)) * h/2;
		*(v+3*i+2) += (f_buffer[3*i+2] + *(f+3*i+2)) * h/2;

		if(*(v+3*i) > L * 1000 || *(v+3*i+1) > L *1000 || *(v+3*i+2) > 1000 * L)
			printf("la velocidad se fue\n");
	}//end loop i velocidad
	
	//fmax = max(f, 3*N);
	//return fmax;
	return Epot;
}

double velocity_verlet_presion(double *r, double *v, double *f, int N, double h, double L, double *tabla_r2, double *tabla_f, double *tabla_v, int long_tabla, double *pres){
	int i;
	double h2 = h*h/2;
	//double fmax;
	double Epot;

	double f_buffer[3*N]; //para almacenar la fuerza del paso temporal anterior
	for(i=0; i < 3*N; i++)
		f_buffer[i] = *(f+i);

	//avanzamos x, y, z de la partícula i
	for (i=0; i<N; i++){
		*(r+3*i) += *(v+3*i) *h + *(f+3*i) * h2;
		*(r+3*i+1) += *(v+3*i+1) *h + *(f+3*i+1) * h2;
		*(r+3*i+2) += *(v+3*i+2) *h + *(f+3*i+2) * h2;
	}//end loop i posicion

	CCP(r,N,L);

	Epot = forces_presion(r, f, tabla_r2, tabla_f, tabla_v, long_tabla, N, L, pres);

	//avanzamos vx, vy, vz de la particula i
	for (i=0; i<N; i++){
		*(v+3*i) += (f_buffer[3*i] + *(f+3*i)) * h/2;
		*(v+3*i+1) += (f_buffer[3*i+1] + *(f+3*i+1)) * h/2;
		*(v+3*i+2) += (f_buffer[3*i+2] + *(f+3*i+2)) * h/2;

		if(*(v+3*i) > L * 1000 || *(v+3*i+1) > L *1000 || *(v+3*i+2) > 1000 * L)
			printf("la velocidad se fue\n");
	}//end loop i velocidad
	
	//fmax = max(f, 3*N);
	//return fmax;
	return Epot;
}

double cinetica(double * vel, int N){
	double Ecin=0.0;
	int i;
	
	for(i=0; i < 3*N; i++)
		Ecin += *(vel+i) * *(vel+i);
	Ecin = Ecin/2;
	return Ecin;
}
