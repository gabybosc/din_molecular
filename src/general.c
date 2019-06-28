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
	// valor medio del puntero. Calcula el vector diezmado v[k*i+j]
	// length es longitud del vector ya diezmado
	int i;
	double avg = 0;

	for (i = 0; i < length; i++){
		avg += *(vector+(k*i+j)); //recorre de a k lugares, con offset j
	}

return(avg/length);
}

int find_nearest(double escalar, double *puntero, int longitud_puntero){
  double diferencia, delta;
  int indice, i;

  diferencia = abs(*puntero - escalar);
  indice = 0;

  for (i = 0; i < longitud_puntero; i++){
    delta = abs(*(puntero+i) - escalar);
    if (delta < diferencia){
      diferencia = delta;
      indice = i;
    }
  }//end loop

return indice;
}

int contador_lineas(FILE *file){
  char c;
  int lines = 0;

  for (c = getc(file); c != EOF; c = getc(file))
        if (c == '\n') // si se encuentra un newline aumenta el contador lineas
            lines = lines + 1;
            
  rewind(file);

  return lines;
}

int leer_tabla(FILE *file, double *r_tabla, double *r2_tabla, double *f_tabla, double *v_tabla){
	// hay que pasarle el archivo que tiene que leer y los punteros donde guarda las cosas
  double r_LUT, r2_LUT, f_LUT, v_LUT;
  int i=0;

  while (fscanf(file, "%lf %lf %lf %lf", &r_LUT, &r2_LUT, &f_LUT, &v_LUT) == 4){
    *(r_tabla+i) = r_LUT;
    *(r2_tabla+i) = r2_LUT;
    *(f_tabla+i) = f_LUT;
    *(v_tabla+i) = v_LUT;
    i += 1;
  }

  return 0;
}
