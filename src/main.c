#include "general.h"
#include "inicializar.h"
#include "interaccion.h"
// #include "tabla.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define N 27

int main(){
  double dL;
  double *r, *f, *r_tabla, *f_tabla;
  double r_LUT, r2_LUT, f_LUT, v_LUT;
  int lines, i=0;
  char c;
  FILE *file;

  file = fopen( "tabla_LJ.txt", "r");
  lines = 0;
  for (c = getc(file); c != EOF; c = getc(file))
        if (c == '\n') // Increment count if this character is newline
            lines = lines + 1;
  printf("number of lines in file %d\n", lines);


  r = malloc(3*N * sizeof(double));
  f = calloc(3*N, sizeof(double));
  r_tabla = malloc((lines-1) * sizeof(double));
  f_tabla = malloc((lines-1) * sizeof(double));

  dL = set_box(r, N, 10);
  printf("dL = %f\n",dL);
  forces(r, f, f_tabla, r_tabla, lines-1, N);

  while (fscanf(file, "%lf %lf %lf %lf", &r_LUT, &r2_LUT, &f_LUT, &v_LUT) != EOF){
    *(f_tabla+i) = f_LUT;
    *(r_tabla+i) = r_LUT;
    i += 1;
  }

  printf("%f,%f,%f\n", *f, *(f+1), *(f+2));

  fclose(file);

  free(r);
  free(f);
  free(r_tabla);
  free(f_tabla);

  return 0;
}
