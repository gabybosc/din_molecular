#include "general.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

double norma_cuadrado(double *vector, int N){//N es el len(vector)
  double suma = 0;
  int i;

  for(i=0; i<N; i++){
    suma += pow(*(vector+i), 2);
  }

  return suma;
}

double gaussiana(double mu, double sigma){
  int n = 10;
  int i;
  double z = 0;

  for(i = 0; i < n; i++){
    z += ((double)rand()) / ((double)RAND_MAX);
  }

  z = sqrt(12) * (z / n - 0.5);

  return z*sigma+mu;
}


double mean(double *vector, int length, int k, int j){//para el mean normal, tomar k = 1, j =0.
	//valor medio de un vector. Calcula el vector diezmado v[k*i+j]
	int i;
	double avg = 0;

	for (i = 0; i < length; i++){
		avg += *(vector+(k*i+j)); //recorre de a k lugares salteando j pasos
	}

return(avg/length);
}
