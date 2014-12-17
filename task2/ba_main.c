
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ba_func.h"

#define PI 3.14159265
#define BOLTZMANN (1.3806488*pow(10,-23))
#define BOLTZMANNeV (8.61734*pow(10,-5))
#define CU 1
#define ZN 0

#define ECC (-0.436)
#define EZZ (-0.113)
#define ECZ (-0.294)


int main()
{
  double oldEnergy, newEnergy, energyDifference;
  double longRangeOrder;
  double shortRangeOrder;
  int n = 10*10*10;
  int nEquilibrationSteps = 8 * 100 * 1000;
//  nEquilibrationSteps = 2000000;
  int nProductionSteps = 20 * 1000 * 1000;

  // Change these two lines for runs at different T
  FILE *fEnergy = fopen("T600.data","w"); // <-----
  double targetTemperature = 600;  // <-----

  int latticeA[n], latticeB[n];
  int neighboursToA[n][8], neighboursToB[n][8];

  int i,j,k;
  int q,r;
  double p;

  srand(time(NULL));

  // File handles for saving neighbour files
  // only needed for checking that they're ok
/*  FILE *neighbourAFile;
  neighbourAFile = fopen("granneA.data","w");
  FILE *neighbourBFile;
  neighbourBFile = fopen("granneB.data","w");
*/
 
  //Initialization (perfectly ordered structure)
  InitializeLattice(n, latticeA, CU);
  InitializeLattice(n, latticeB, ZN);

  InitializeNeighbourMatrices(n, neighboursToA, neighboursToB);

  oldEnergy = GetEnergy(n, latticeA, latticeB, \
      neighboursToA, neighboursToB);

//  FILE *equilibrationFile = fopen("equilibration.data","w");

  k = 0;  
  printf("Starting equilibration...\t\t");
  while ( k < nEquilibrationSteps) {
    q = ((double) rand() / (double) RAND_MAX) * 2*n;
    r = ((double) rand() / (double) RAND_MAX) * 2*n;

    SwapParticles(n, latticeA, latticeB, q, r);

    newEnergy = GetEnergy(n, latticeA, latticeB, \
        neighboursToA, neighboursToB);
    energyDifference = newEnergy - oldEnergy;

    if(energyDifference > 0) {
      p = (double) rand() / (double) RAND_MAX;
      if ( exp( - energyDifference/  \
        (BOLTZMANNeV * targetTemperature) ) > p ) {
        // keep the change
        oldEnergy = newEnergy;
      } else {
        // restore the swap
        SwapParticles(n, latticeA, latticeB, q, r);
      }
    } else {
      // keep the change
      oldEnergy = newEnergy;
    }

    // Needs this just for one equilibration plot, comment later!
//    longRangeOrder = GetLongRangeOrder(n, latticeA);
//    shortRangeOrder = GetShortRangeOrder(n, latticeA, \
//        latticeB, neighboursToA);
//    fprintf(equilibrationFile, "%e\t%e\t%e\n", oldEnergy, longRangeOrder, shortRangeOrder);
    k++;
  }
  printf("Equilibration done!\nStarting production...\t\t\t");

// Start of production 
  k = 0; 
//  k=nProductionSteps;
  while ( k < nProductionSteps ) {
    q = ((double) rand() / (double) RAND_MAX) * 2*n;
    r = ((double) rand() / (double) RAND_MAX) * 2*n;

    SwapParticles(n, latticeA, latticeB, q, r);

    newEnergy = GetEnergy(n, latticeA, latticeB, \
    neighboursToA, neighboursToB);
    energyDifference = newEnergy - oldEnergy;

    if(energyDifference > 0) {
      p = (double) rand() / (double) RAND_MAX;
      if ( exp( - energyDifference/  \
        (BOLTZMANNeV * targetTemperature) ) > p ) {
        oldEnergy = newEnergy;
      } else {
        SwapParticles(n, latticeA, latticeB, q, r);
      }
    } else {
      oldEnergy = newEnergy;
    }
   
    // Prepare and save data each iteration
    longRangeOrder = GetLongRangeOrder(n, latticeA);
    shortRangeOrder = GetShortRangeOrder(n, latticeA, \
        latticeB, neighboursToA);
    fprintf(fEnergy,"%e\t%e\t%e\n",oldEnergy, \
        longRangeOrder, shortRangeOrder);

    k++;
  }

/*    // Saving neighbour tables, only used for checking correctness
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
