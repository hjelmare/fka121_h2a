
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ba_func.h"

#define PI 3.14159265
#define ECC -0.436
#define EZZ -0.113
#define ECZ -0.294

void InitializeLattice(int n, int lattice[], int type)
{
  int i;

  for( i = 0 ; i < n ; i++ ) {
    lattice[i] = type;
  }

  return;
}

double GetEnergy(int n, int latticeA[], int latticeB[], int neighboursToA[][8], int neighboursToB[][8])
{
  // this needs to go through latticeA and latticeB and sum up NN-energies 
}

void InitializeNeighbourMatrices(int n, int neighboursToA[][8], int neighboursToB[][8])
{



  return;
}

