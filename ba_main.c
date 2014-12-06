
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ba_func.h"

#define PI 3.14159265
#define BOLTZMANN 1.3806488*pow(10,-23)
#define BOLTZMANNeV 8.61734*pow(10,-5)

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
  
  int N = 10*10*10;  // Number of Cu and Zn particles (10 unit cells in each dimension), there are 2 atoms per unit cell

  // variables that depend on earlier set variables:
  double CuParticles[N][8], ZnParticles[N][8];
  double temporaryStorage[8];

  int i,j,k;
  int storeNbr;  //a variable that changes value in each loop (Task 1).
  double P, T;

  // open files to save values in.
  FILE *valuesFile;
  valuesFile = fopen("values.data","w");
  FILE *energyFile;
  energyFile = fopen("energyTask1.data","w");
  FILE *p_TFile;
  p_TFile = fopen("P_T.data","w");
  FILE *testFile;
  testFile = fopen("test.data", "w");
  FILE *UFile;
  UFile = fopen("UofT.data","w");
  FILE *CFile;
  CFile = fopen("heatCapacity.data","w");

  //Initialization (so far we only construct a perfectly ordered structure)
  InitializeSystem(N, CuParticles, ZnParticles); 
 
  randZn = rand() * scale; // skala till particlearraystorlek, int
  randCu = rand() * scale;

  for ( i = 0 ; i < 8 ; i++) {
    if( CuParticles[randCu][i] == 1 ) {
      nZnChanges++;
    }
    if( ZnParticles[randZn][i] == 1 ) {
      nCuChanges++;
    }
  }
  
  while ( nZnChanges > 0 ) {
    if ( ZnParticles[(int) i / (int) 8][i%8] == 1 ) {   // how do we denote an opposite-type particle?
      nZnChanges--;
      ZnParticles[(int) i / (int) 8][i%8] = 0;
    }
    i++;
    if ( (int) i / (int) 8 == randZn ) {
      i += 8;
    }
  }

  while ( nCuChanges > 0 ) {
    if ( CuParticles[(int) i / (int) 8][i%8] == 1 ) { // same as ^^
      nCuChanges--;
      CuParticles[(int) i / (int) 8][i%8] = 0;
    }
    i++;
    if ( (int) i / (int) 8 == randCu ) {
      i += 8;
    }
  }
  
  for ( i = 0 ; i < 8 ; i++ ) {
    temporaryStorage[i] = CuParticles[randCu][i];
    CuParticles[randCu][i] = ZnParticles[randZn][i];
    ZnParticles[randZn][i] = temporaryStorage[i];
  }

  return 0;
}
