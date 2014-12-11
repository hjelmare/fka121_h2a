
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
  double oldEnergy, newEnergy, energyDifference;
  double longRangeOrder;
  double shortRangeOrder;
  double targetTemperature = 50000;
  int n = 10*10*10;

  int latticeA[n], latticeB[n];
  int neighboursToA[n][8], neighboursToB[n][8];

  int i,j,k;
  int q,r,p;

  srand(time(NULL));

  // File handles for saving
/*  FILE *neighbourAFile;
  neighbourAFile = fopen("granneA.data","w");
  FILE *neighbourBFile;
  neighbourBFile = fopen("granneB.data","w");
*/
 
  //Initialization (so far we only construct a perfectly ordered structure)
  InitializeLattice(n, latticeA, CU);
  InitializeLattice(n, latticeB, ZN);

  InitializeNeighbourMatrices(n, neighboursToA, neighboursToB);

  oldEnergy = GetEnergy(n, latticeA, latticeB, neighboursToA, neighboursToB);
  
  k = 0;  // replace this, use some intelligent condition for the metropolis algo
  while ( k < 10 ) {
    q = ((double) rand() / (double) RAND_MAX) * n;
    r = ((double) rand() / (double) RAND_MAX) * n;


    SwapParticles(n, latticeA, latticeB, q, r);

    // this is wrong, we need to be able to swap A<->A and B<->B as well...
    newEnergy = GetEnergy(n, latticeA, latticeB, neighboursToA, neighboursToB);
    energyDifference = newEnergy - oldEnergy;
    printf("eDiff: %e\n",energyDifference);

    if(energyDifference > 0) {
      p = (double) rand() / (double) RAND_MAX;
      if ( exp( - energyDifference/(BOLTZMANNeV * targetTemperature) ) > p ) {
        oldEnergy = newEnergy;
      } else {
        SwapParticles(n, latticeA, latticeB, q, r);
      }
    } else {
      oldEnergy = newEnergy;
    }
    
    k++;
  }
  
  longRangeOrder = GetLongRangeOrder(n, latticeA);
  shortRangeOrder = GetShortRangeOrder(n, latticeA, latticeB, neighboursToA);

  printf("energy=%e\tlro=%e\t sro=%e\n", newEnergy, longRangeOrder, shortRangeOrder);
/*
  for(i=0; i<n; i++){
    for(j=0; j<8; j++){
      fprintf(neighbourAFile, "%d\t", neighboursToA[i][j]);
      fprintf(neighbourBFile, "%d\t", neighboursToB[i][j]);
    }
    fprintf(neighbourAFile,"\n");
    fprintf(neighbourBFile, "\n");
  }
*/
  printf("Done!\n");


  return 0;
}
