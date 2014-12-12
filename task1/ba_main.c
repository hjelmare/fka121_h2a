#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ba_func.h"

#define PI 3.14159265

#define BOLTZMANN (1.3806488*pow(10,-23))
#define BOLTZMANNeV (8.61734*pow(10,-5))

#define ECC (-0.436)  // bond energies in eV
#define EZZ (-0.113)
#define ECZ (-0.294)

int main()
{ 
  double Pstep = 0.05;  // P for pressure
  int Tstep = 1;        // T for temperature
  int Tstart = 250;
  int Tstop = 1200;
  double dE, E0;        // E for energy
  double T_c;   //Phase transition temperature
  double E;
  double E_save;
  double freeEnergy_min, freeEnergy;  // Helmholtz free energy
  double P_save;
  double heatCapacity;
  double heatCapacityTemporary[2];
  double Energy;
  
  int n = 10*10*10;  // Num of particles on each sublattice

  double CuParticles[n][8], ZnParticles[n][8];

  int i,j,k;
  int storeNbr; 
  double P;
  int T;

  // open files to save values in.
  FILE *valuesFile;
  valuesFile = fopen("values.data","w");
  FILE *energyFile;
  energyFile = fopen("energyTask1.data","w");
  FILE *p_TFile;
  p_TFile = fopen("P_T.data","w");
  FILE *UFile;
  UFile = fopen("UofT.data","w");
  FILE *CFile;
  CFile = fopen("heatCapacity.data","w");


  // Mean field approximation
  dE = ECC + EZZ - 2*ECZ;
  E0 = 2*n*(ECC + EZZ + 2*ECZ);
  T_c = 2*dE/BOLTZMANNeV;
  fprintf(valuesFile,"%e\tPhase transition temp - \
  NB! Should be ~468 C\n", T_c);
  // Somehow, the phase transition temperature is wrong
  // Not sure why. It's a simple expression...

  storeNbr = 0;
  // Step through temperatures...
  for(T=Tstart; T<Tstop; T+=Tstep){
    freeEnergy_min = pow(10,100);
    P_save = 2;
    E_save = 0;
    // ... and step through P and different T ...
    for(P =- 1; P<1; P += Pstep){
      E = E0 - 2*n*pow(P,2)*dE;
      freeEnergy = E - 2*n*BOLTZMANNeV*log(2) + \
      n*BOLTZMANNeV*T*((1 + P)*log(1 + P) + (1 - P)*log(1 - P));
      // ... to find P that gives minimal E
      if(freeEnergy < freeEnergy_min){
        freeEnergy_min = freeEnergy;
        P_save = P;
        E_save = E;
      }
      // Save energies at all different P and T ...
      fprintf(p_TFile, "%e\t%e\t%d\n", P, freeEnergy, T);
    }
    // ... and save lowest energy for each temperature
    fprintf(UFile, "%d\t%e\n", T, E_save);
    
    // Calculating heat capacity
    if(storeNbr < 2){
      heatCapacityTemporary[storeNbr] = E_save; 
      storeNbr += 1;
    } else {
      heatCapacity = (E_save - heatCapacityTemporary[0])/(2*Tstep);
      fprintf(CFile, "%d \t %e \n", T, heatCapacity);
        
      heatCapacityTemporary[0] = heatCapacityTemporary[1];
      heatCapacityTemporary[1] = E_save;
    }
    // Saves the P that gives the lowest energy at temperature T.
    fprintf(energyFile,"%d \t %e\n", T, P_save);  
  }
    
  printf("NB! PHASE TRANSITION TEMPERATURE SAVED \
    IN values.data IS INCORRECT\n");
  return 0;
}
