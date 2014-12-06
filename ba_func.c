
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ba_func.h"

#define PI 3.14159265

//Initializes a parfectly ordered system.
//Cn/Zn-Particles are the nearest neighbour matrixes.
void InitializeSystem(int N, double CnParticles[][8], double ZnParticles[][8])
{
  int i,j;
  for(i = 0; i<N; i++){
    for(j = 0; j<8; j++){
      CnParticles[i][j] = 0;  //0 ==> Zn Particles
      ZnParticles[i][j] = 1;  //1 ==> Cu Particles
    }
  }
}
