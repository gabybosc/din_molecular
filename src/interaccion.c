#include "general.h"
#include "interaccion.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

int Lennard_Jones(double *potencial, double *fuerza, double *r2, int SIZE){//calcula el pot y la fuerza de LJ para r² con epsilon = sigma = 1
	double offset = 4 * (pow(2.5, -12) - pow(2.5, -6));
	double r6, r;
	int i;

	for (i = 0; i < SIZE; i++){
		r6 = pow(*(r2+i), -3); //es r⁻⁶
		r = sqrt(*(r2+i));

		*(potencial+i) = 4 * (r6 * ( r6 - 1)) - offset;
		*(fuerza + i) = 24 * r6/r * (2 * r6 - 1); //si trabajamos con r2 en lugar de r
		// *(fuerza + i) = 24 * r6 * (2 * r6 - 1);
	}//end loop i
	return 0;
}

double forces(double *r, double *f, double *tabla_r2, double *tabla_f, int long_tabla, int N, int L){
	int i, j, indice;
	double dx, dy, dz, r2, fuerza_par;

	//set fuerzas a 0
	for (i=0; i<3*N; i++){
		*(f+i) = 0;
	}

	for(j=0; j< N-1; j++){
		for(i = j+1; i < N; i++){
			dx = *(r+3*j) - *(r+3*i);
			dy = *(r+3*j+1) - *(r+3*i+1);
			dz = *(r+3*j+2) - *(r+3*i+2);

			// si abs(dr) > L/2, lo corregimos tomando su imagen mas cercana
			if(dx > L/2)
				dx -= L;
			else if(dx < -L/2)
				dx += L;
			if(dy > L/2)
				dy -= L;
			else if(dy < -L/2)
				dy += L;
			if(dz > L/2)
				dz -= L;
			else if(dz < -L/2)
				dz += L;

			r2 = pow(dx, 2) + pow(dy, 2) + pow(dz, 2);

			if(r2 < pow(2.5, 2)){ //solo dentro del radio de corte
				indice = find_nearest(r2, tabla_r2, long_tabla);
				//se puede agregar una interpolacion aca
				fuerza_par = *(tabla_f+indice);

				*(f+3*j) += fuerza_par * dx / sqrt(r2);   //fx(j)
				*(f+3*j+1) += fuerza_par * dy / sqrt(r2); //fy(j)
				*(f+3*j+2) += fuerza_par * dz / sqrt(r2); //fz(j)

				*(f+3*i) -= fuerza_par * dx / sqrt(r2);   //fx(i)
				*(f+3*i+1) -= fuerza_par * dy / sqrt(r2); //fy(i)
				*(f+3*i+2) -= fuerza_par * dz / sqrt(r2); //fz(i)
			}// end if radio
		}//end loop i
	}//end loop j
	return 0;
}

int CCP(double *r, int N, double L){//condiciones de contorno periodicas (no republica socialista sovietica)
	// si cae fuera de la caja, lo corregimos
	int i;
	for(i=0; i < 3*N; i++){
		if(*(r+i) < 0)
			*(r+i) += L;
		else if(*(r+i) > L)
			*(r+i) -= L;
	}
	return 0;
}
