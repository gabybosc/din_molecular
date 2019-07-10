#ifndef VISUALIZACION_H
#define VISUALIZACION_H

#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

int save_lammpstrj(char *filename, double* x, double* v, int N, double L, int frame);
int load_frame(FILE *fp, double* x, double* v, int N, double L);
int load_lammpstrj(FILE *fp, double* x, double* v, int N, double L, int frame);

#endif
