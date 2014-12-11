#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ba_func.h"

#define PI 3.14159265

#define BOLTZMANN 1.3806488*pow(10,-23)
#define BOLTZMANNeV 8.61734*pow(10,-5)

#define ECC -0.436  // bond energies in eV
#define EZZ -0.113
#define ECZ -0.294

int main()
{ 
  double Pstep = 0.05;
  int Tstep = 1;
  int Tstart = 250;
  int Tstop = 1200;
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

  int i,j,k;
  int storeNbr;  //a variable that changes value in each loop (Task 1).
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
  fprintf(valuesFile,"%e\tphase transition temperature - OBS! Should be ~468 C\n", T_c);

  storeNbr = 0;
  for(T=Tstart; T<Tstop; T+=Tstep){
      freeEnergy_min = pow(10,100);
      P_save = 2;
      E_save = 0;
    for(P =- 1; P<1; P += Pstep){ //Går från -1 till 1 och stegar med Pstep storlek.
      E = E0 - 2*n*pow(P,2)*dE;
      freeEnergy = E - 2*n*BOLTZMANNeV*log(2) + n*BOLTZMANNeV*T*((1 + P)*log(1 + P) + (1 - P)*log(1 - P));
      if(freeEnergy < freeEnergy_min){
        freeEnergy_min = freeEnergy;
        P_save = P;
        E_save = E;
      }
   //   if(T % (Tstop/10) == 0){
        fprintf(p_TFile, "%e\t%e\t%d\n", P, freeEnergy, T); //Saves the energys as function of T & P 
    //  }
    }
    fprintf(UFile, "%d\t%e\n", T, E_save); //Saves energy-U as function of temperature.
    
    // Calculating heatcapacity
    if(storeNbr < 2){
      heatCapacityTemporary[storeNbr] = E_save; 
      storeNbr += 1;
    }else{
      heatCapacity = (E_save - heatCapacityTemporary[0])/(2*Tstep);
      fprintf(CFile, "%d \t %e \n", T, heatCapacity);
        
      heatCapacityTemporary[0] = heatCapacityTemporary[1];
      heatCapacityTemporary[1] = E_save;
    }
    fprintf(energyFile,"%d \t %e\n", T, P_save);  // Saves the P that gives the lowest energy at temperature T.
  }
    
printf("OBS! VI FÅR FORTFARANDE FEL PÅ DEN BERÄKNADE FASÖVERGÅNGSTEMPERATUREN SOM SPARAS I values.data!!!!!!!!!!!!!!!!!!\n");
  return 0;
}
