
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ba_func.h"

#define PI 3.14159265
#define BOLTZMANN 1.3806488*pow(10,-23)


int main()
{ 

  double E_CuCu = -436; // meV
  double E_ZnZn = -113; // meV
  double E_CuZn = -294; // meV
  double dE = E_CuCu + E_ZnZn - 2*ECuZn;
  double T_c = 2*dE/boltzmannsConstant;
  printf("the phase transition temperature is %e \n", T_c);

  // open files to save values in.
  FILE *valuesFile;
  valuesFile = fopen("values.data","w");

  fprintf(valuesFile,"%e\tphase transition temperature\n");

  

  return 0;
}
