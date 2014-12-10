
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

  double energy;
  double longRangeOrder;
  int n = 10*10*10;  // Number of Cu and Zn particles (10 unit cells in each dimension), there are 2 atoms per unit cell

  // variables that depend on earlier set variables:
  int latticeA[n], latticeB[n];
  int neighboursToA[n][8], neighboursToB[n][8];

  int i,j,k;

  // File handles for saving
  FILE *neighbourAFile;
  neighbourAFile = fopen("granneA.data","w");
  FILE *neighbourBFile;
  neighbourBFile = fopen("granneB.data","w");

  srand(time(NULL));

  //Initialization (so far we only construct a perfectly ordered structure)
  InitializeLattice(n, latticeA, CU);
  InitializeLattice(n, latticeB, ZN);


  longRangeOrder = GetLongRangeOrder(n, latticeA);
  
  printf("long: %e\n", longRangeOrder);
  InitializeNeighbourMatrices(n, neighboursToA, neighboursToB);

  energy = GetEnergy(n, latticeA, latticeB, neighboursToA, neighboursToB);
  printf("%e\n", energy);

  int temp;
  temp = latticeA[5];
  latticeA[5] = latticeB[7];
  latticeB[7] = temp;

  energy = GetEnergy(n, latticeA, latticeB, neighboursToA, neighboursToB);
  printf("%e\n", energy);

  longRangeOrder = GetLongRangeOrder(n, latticeA);
  printf("long: %e\n", longRangeOrder);

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
