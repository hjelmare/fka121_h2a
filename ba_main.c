
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


 // Task 1, not realy related to computations in part 2-----------------------------------
 // Mean field approximation
  dE = E_CuCu + E_ZnZn - 2*E_CuZn;
  E0 = 2*N*(E_CuCu + E_ZnZn + 2*E_CuZn);
  T_c = 2*dE/BOLTZMANNeV;
  fprintf(valuesFile,"%e\tphase transition temperature - OBS! Should be ~468 C\n", T_c);

  storeNbr = 0;
  for(T=Tstart; T<Tstop; T+=Tstep){
      freeEnergy_min = pow(10,100);
      P_save = 2;
      E_save = 0;
    for(P =- 1; P<1; P += Pstep){ //Går från -1 till 1 och stegar med Pstep storlek.
      E = E0 - 2*N*pow(P,2)*dE;
      freeEnergy = E - 2*N*BOLTZMANNeV*log(2) + N*BOLTZMANNeV*T*((1 + P)*log(1 + P) + (1 - P)*log(1 - P));
      if(freeEnergy < freeEnergy_min){
        freeEnergy_min = freeEnergy;
        P_save = P;
        E_save = E;
      }
      fprintf(p_TFile, "%e\t%e\t%e\n", P, freeEnergy_min, T); //Saves the energys as function of T & P 
    }
    fprintf(UFile, "%e\t%e\n", T, E_save); //Saves energy-U as function of temperature.
    
    // Calculating heatcapacity
    if(storeNbr < 2){
      heatCapacityTemporary[storeNbr] = E_save; 
      storeNbr += 1;
    }else{
      heatCapacity = (E_save - heatCapacityTemporary[0])/(2*Tstep);
      fprintf(CFile, "%e \t %e \n", T, heatCapacity);
        
      heatCapacityTemporary[0] = heatCapacityTemporary[1];
      heatCapacityTemporary[1] = E_save;
    }
    fprintf(energyFile,"%e \t %e\n", T, P_save);  // Saves the P that gives the lowest energy at temperature T.
  }
    
 // Task 1 end --------------------------------------------------------------------------
 // -------------------------------------------------------------------------------------
 // -------------------------------------------------------------------------------------
 // Task 2 start ------------------------------------------------------------------------
 
  //Initialization (so far we only construct a perfectly ordered structure)
  InitializeSystem(N, CuParticles, ZnParticles); 
 
 
 
 
 // Task 2 end -------------------------------------------------------------------------
 // ------------------------------------------------------------------------------------
printf("OBS! VI FÅR FORTFARANDE FEL PÅ DEN BERÄKNADE FASTRANSMORMATIONS-TEMPERATUREN SOM SPARAS I values.data!!!!!!!!!!!!!!!!!!\n");
  return 0;
}
