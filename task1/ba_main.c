#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ba_func.h"

#define PI 3.14159265
#define BOLTZMANNeV (8.61734*pow(10,-5))

#define ECC (-0.436)  // bond energies in eV
#define EZZ (-0.113)
#define ECZ (-0.294)

int main()
{ 
  double Pstart = 0;
  double Pstep = 0.001; // P for long range order parameter
  double Pstop = 1;
  double Tstep = 1;
  double Tstart = 200;  // T for temperature
  double Tstop = 1200;
  
  int n = 10*10*10;  // Num of particles on each sublattice

  double freeEnergy_min, freeEnergy;  // Helmholtz free energy
  double dE, E0;        // E for energy
  double E;
  double E_save;
  double T;
  double T_c;   //Phase transition temperature
  double P;
  double P_save;
  double heatCapacity = 0;
  double prev_E_save = 0;
  int stepsSinceLastIncrease = 0;

  // open files to save values in.
  FILE *valuesFile = fopen("values.data","w");
  FILE *fFreeEnergy = fopen("freeEnergy.data","w");
  FILE *fUpc = fopen("upc.data","w");

  // Mean field approximation
  dE = ECC + EZZ - 2*ECZ;
  E0 = 2*n*(ECC + EZZ + 2*ECZ);
  T_c = 2*dE/BOLTZMANNeV;
  fprintf(valuesFile,"Phase transition temp\t%e\n", T_c);

  // Step through temperatures...
  for(T = Tstart; T <= Tstop; T += Tstep){
    freeEnergy_min = pow(10,100);   // approximation of Inf
    // ... and step through order parameter values ...
    for(P = Pstart; P <= Pstop; P += Pstep){
      E = E0 - 2*n*pow(P,2)*dE;
      freeEnergy = E - 2*n*BOLTZMANNeV*T*log(2) + \
      n*BOLTZMANNeV*T*((1 + P)*log(1 + P) + (1 - P)*log(1 - P));
      // ... to find order parameter that minimizes F for each T
      if(freeEnergy < freeEnergy_min){
        freeEnergy_min = freeEnergy;
        P_save = P;
        E_save = E;
      }
      // Save free energies at all different P and T ...
      fprintf(fFreeEnergy, "%e\t%e\t%e\n", P, T, freeEnergy);
    }
    
    // Saves the P that gives the lowest energy at temperature T.
    fprintf(energyFile,"%d \t %e\n", T, P_save);  
    
    // Calculating heat capacity
    if(prev_E_save == 0) { prev_E_save = E_save; }  // first time around
    if( E_save == prev_E_save) {
      stepsSinceLastIncrease++;
    } else {
      heatCapacity = (E_save - prev_E_save)/(Tstep*stepsSinceLastIncrease);
      prev_E_save = E_save;
      stepsSinceLastIncrease = 0;
    }
        
    // Saves E and P for lowest F, and also C, for each temperature
    fprintf(fUpc, "%e\t%e\t%e\t%e\n", T, E_save, P_save, heatCapacity);
  }
    
  return 0;
}
