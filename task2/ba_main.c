
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
  double targetTemperature = 50;
  int n = 10*10*10;

  int latticeA[n], latticeB[n];
  int neighboursToA[n][8], neighboursToB[n][8];

  int i,j,k;
  int q,r,p;
  int swap;

  srand(time(NULL));

  // File handles for saving
  FILE *neighbourAFile;
  neighbourAFile = fopen("granneA.data","w");
  FILE *neighbourBFile;
  neighbourBFile = fopen("granneB.data","w");

  //Initialization (so far we only construct a perfectly ordered structure)
  InitializeLattice(n, latticeA, CU);
  InitializeLattice(n, latticeB, ZN);

  longRangeOrder = GetLongRangeOrder(n, latticeA);
  printf("long: %e\n", longRangeOrder);

  InitializeNeighbourMatrices(n, neighboursToA, neighboursToB);

  oldEnergy = GetEnergy(n, latticeA, latticeB, neighboursToA, neighboursToB);
  
  k = 0;  // replace this, use some intelligent condition for the metropolis algo
  while ( k < 100000 ) {
    q = ((double) rand() / (double) RAND_MAX) * n;
    r = ((double) rand() / (double) RAND_MAX) * n;

    // this is wrong, we need to be able to swap A<->A and B<->B as well...
    swap = latticeA[q];
    latticeA[q] = latticeB[r];
    latticeB[r] = swap;

    newEnergy = GetEnergy(n, latticeA, latticeB, neighboursToA, neighboursToB);
    energyDifference = newEnergy - oldEnergy;
    printf("eDiff: %e\n",energyDifference);

    if(energyDifference > 0) {
      p = (double) rand() / (double) RAND_MAX;
      if ( exp( - energyDifference/(BOLTZMANNeV * targetTemperature) ) > p ) {
        oldEnergy = newEnergy;
      } else {
        latticeB[r] = latticeA[q];
        latticeA[q] = swap;
      }
    } else {
      oldEnergy = newEnergy;
    }
    
    k++;
  }
  
  longRangeOrder = GetLongRangeOrder(n, latticeA);
  printf("long: %e\n", longRangeOrder);

  printf("energy\t%e\tlro\t%e\n", newEnergy, longRangeOrder);

/*  for(i=0; i<n; i++){
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
