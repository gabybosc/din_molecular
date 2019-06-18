#include "general.h"
#include "inicializar.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

double set_box(double *X, int N, double L){ //N tiene que ser un número cúbico
  int n = cbrt(N);
  int i = 0;
  int x,y,z;
  double dL = L/n;

  for (x = 0; x < n; x++){
    for(y = 0; y < n; y++){
      for (z = 0; z < n; z++){
        *(X+3*i) = dL * (x + 0.5);
        *(X+3*i+1) = dL * (y + 0.5);
        *(X+3*i+2) = dL * (z + 0.5);
        i++;
      }//end loop z
    }//end loop y
  }//end loop x

  return dL;
}

int set_vel(double *vel, int N, double T){
  double sigma = sqrt(T);
  double vx, vy, vz;
  int i,j;

  for(j = 0; j < 3*N; j++){
    *(vel+j) = gaussiana(0.0, sigma);
  }

  vx = mean(vel, N, 3, 0);
  vy = mean(vel, N, 3, 1);
  vz = mean(vel, N, 3, 2);

  for(i = 0; i < N; i++){
    *(vel+3*i) -=vx;
    *(vel+3*i+1) -=vy;
    *(vel+3*i+2) -=vz;
  }

  return 0;
}
