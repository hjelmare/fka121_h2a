
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ba_func.h"

#define PI 3.14159265
#define ECC -0.436
#define EZZ -0.113
#define ECZ -0.294

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

double GetEnergy(int N, double CnParticles[][8], double ZnParticles[][8])
{
  int i,j;
  double sum = 0;
  double E_CuCu = -0.436; //eV
  double E_ZnZn = -0.113; //eV
  double E_CuZn = -0.294; //eV

  for(i = 0; i<N; i++){
    for(j = 0; j<8; j++){
      if(CnParticles[i][j] == 0){
        sum += E_CuZn;
      }else{
        sum += E_CuCu;
      }

      if(ZnParticles[i][j] == 1){
        sum += E_CuZn;
      }else{
        sum += E_ZnZn;
      }
    }
  }
  sum = sum/2; //Every bond is counted twice, so we divide by 2;

  return sum;
}


