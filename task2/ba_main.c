
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ba_func.h"

#define PI 3.14159265
#define BOLTZMANN 1.3806488*pow(10,-23)
#define BOLTZMANNeV 8.61734*pow(10,-5)
#define CU 1
#define ZN 0

#define ECC -0.436
#define EZZ -0.113
#define ECZ -0.294


int main()
{ 

  double E_CuCu = -0.436; // eV
  double E_ZnZn = -0.113; // eV
  double E_CuZn = -0.294; // eV
  double Pstep = 0.1;
  double Tstep = 5;
  double Tstart = 250;
  double Tstop = 1200;
  double dE, E0;
  double T_c;   //Phase transition temperature
  double E;
  double E_save;
  double freeEnergy_min, freeEnergy;
  double P_save;
  double heatCapacity;
  double heatCapacityTemporary[2];
  double Energy;
  
  int n = 10*10*10;  // Number of Cu and Zn particles (10 unit cells in each dimension), there are 2 atoms per unit cell

  // variables that depend on earlier set variables:
  double CuParticles[n][8], ZnParticles[n][8];
  double temporaryStorage[8];
  int latticeA[n], latticeB[n];
  int neighboursToA[n][8], neighboursToB[n][8];

  int i,j,k;
  double P, T;
  int randZn, randCu;
  int nZnChanges, nCuChanges;

  // File handles for saving
  FILE *neighbourAFile;
  neighbourAFile = fopen("granneA.data","w");
  FILE *neighbourBFile;
  neighbourBFile = fopen("granneB.data","w");

  srand(time(NULL));

  //Initialization (so far we only construct a perfectly ordered structure)
  InitializeLattice(n, latticeA, CU);
  InitializeLattice(n, latticeB, ZN);

  InitializeNeighbourMatrices(n, neighboursToA, neighboursToB);
  printf("%d\n",neighboursToA[0][1]);

  for(i=0; i<n; i++){
    for(j=0; j<8; j++){
      fprintf(neighbourAFile, "%d\t", neighboursToA[i][j]);
      fprintf(neighbourBFile, "%d\t", neighboursToB[i][j]);
    }
    fprintf(neighbourAFile,"\n");
    fprintf(neighbourBFile, "\n");
  }

  printf("Done!\n");



  return 0;
}
