
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
//  N = 4;

  // variables that depend on earlier set variables:
  double CuParticles[N][8], ZnParticles[N][8];
  double temporaryStorage[8];
  double latticeA[N], latticeB[N];
  double GA[N][8], GB[N][8];

  int i,j,k;
  double P, T;
  int randZn, randCu;
  int nZnChanges, nCuChanges;

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
  FILE *neighbourAFile;
  neighbourAFile = fopen("granneA.data","w");
  FILE *neighbourBFile;
  neighbourBFile = fopen("granneB.data","w");

  srand(time(NULL));

  //Initialization (so far we only construct a perfectly ordered structure)
  for(i=0; i<N; i++){
      latticeA[i]= 0;
      latticeB[i]=1;
      for(j = 0; j<8; j++){
        GA[i][j] = 0;
        GB[i][j] = 0;
      }
  }
  // Construct the neighbours OBS! in GA there are indexes to LatticeB and GB indexes in latticeA
  // ie. the neighbours to all particles in sublattice A are located in sublattice B.
  for(i=0; i<N; i++){
   //Behandlar alla inre punkter
   GA[i][0] = i;         GB[i][0] = i+111;
   GA[i][1] = i-1;       GB[i][1] = i+110;
   GA[i][2] = i-10;      GB[i][2] = i+101;
   GA[i][3] = i-11;      GB[i][3] = i+100;
   GA[i][4] = i-100;     GB[i][4] = i+11;
   GA[i][5] = i-101;     GB[i][5] = i+10;
   GA[i][6] = i-110;     GB[i][6] = i+1;
   GA[i][7] = i-111;     GB[i][7] = i;

   if(i<100){  //the "floor" boundary condition. (100 particles to the next lvl)
     GA[i][0] = i;          //GB[i][0] = i+111;
     GA[i][1] = i-1;        //GB[i][1] = i+110;
     GA[i][2] = i-10;        //GB[i][2] = i+101;
     GA[i][3] = i-11;        //GB[i][3] = i+100;
     GA[i][4] = i+N-100;     //GB[i][4] = i+11;
     GA[i][5] = i+N-101;     //GB[i][5] = i+10;
     GA[i][6] = i+N-110;     //GB[i][6] = i+1;
     GA[i][7] = i+N-111;     //GB[i][7] = i;
   }
        
   if((i+1)%100<10){ // Främre sidan
     GA[i][0] = i;           //GB[i][0] = i+111;
     GA[i][1] = i-1;         //GB[i][1] = i+110;
     GA[i][2] = i+100-10;    //GB[i][2] = i+101;
     GA[i][3] = i+100-11;    //GB[i][3] = i+100; //KLAR
     GA[i][4] = i-100;       //GB[i][4] = i+11;
     GA[i][5] = i-101;       //GB[i][5] = i+10;
     GA[i][6] = i-10;        //GB[i][6] = i+1;
     GA[i][7] = i-11;        //GB[i][7] = i;
   }
    
   if((i%100) >= 90){ //Bortre sidan
     /*GA[i][0] = i;*/         GB[i][0] = i-100+111;
     /*GA[i][1] = i-1;*/       GB[i][1] = i-100+110;
     /*GA[i][2] = i-10;*/      GB[i][2] = i+101;
     /*GA[i][3] = i-11;*/      GB[i][3] = i+100;
     /*GA[i][4] = i-100;*/     GB[i][4] = i-100+11;
     /*GA[i][5] = i-101;*/     GB[i][5] = i-100+10;
     /*GA[i][6] = i-110;*/     GB[i][6] = i+1;
     /*GA[i][7] = i-111;*/     GB[i][7] = i;
   }
         
   if((i+1)%10==0){ //Högra sidan
     /*GA[i][0] = i;*/         GB[i][0] = i+101;
     /*GA[i][1] = i-1;*/       GB[i][1] = i+110;
     /*GA[i][2] = i-10;*/      GB[i][2] = i+91;
     /*GA[i][3] = i-11;*/      GB[i][3] = i+100;
     /*GA[i][4] = i-100;*/     GB[i][4] = i+1;
     /*GA[i][5] = i-101;*/     GB[i][5] = i+10;
     /*GA[i][6] = i-110;*/     GB[i][6] = i-9;
     /*GA[i][7] = i-111;*/     GB[i][7] = i;
   }
         
   if(i%10==0){ //Vänstra sidan
     GA[i][0] = i;         //GB[i][0] = i+111;
     GA[i][1] = i+9;       //GB[i][1] = i+110;
     GA[i][2] = i-10;      //GB[i][2] = i+101;
     GA[i][3] = i-1;       //GB[i][3] = i+100;
     GA[i][4] = i-100;     //GB[i][4] = i+11;
     GA[i][5] = i-101+10;  //GB[i][5] = i+10;
     GA[i][6] = i-110;     //GB[i][6] = i+1;
     GA[i][7] = i-111+10;  //GB[i][7] = i;
   }
         
   if(i>(N-100)){ // Övre sidan
     /*GA[i][0] = i;*/         GB[i][0] = i+111-100;
     /*GA[i][1] = i-1;*/       GB[i][1] = i+110-100;
     /*GA[i][2] = i-10;*/      GB[i][2] = i+101-100;
     /*GA[i][3] = i-11;*/      GB[i][3] = i+100-100;
     /*GA[i][4] = i-100;*/     GB[i][4] = i+11;
     /*GA[i][5] = i-101;*/     GB[i][5] = i+10;
     /*GA[i][6] = i-110;*/     GB[i][6] = i+1;
     /*GA[i][7] = i-111;*/     GB[i][7] = i;
   }


    if(i<10){ //Främre undre raden 
     GA[i][0] = i;         //GB[i][0] = i+111;
     GA[i][1] = i-1;       //GB[i][1] = i+110;
     GA[i][2] = i+100-10;  //GB[i][2] = i+101;
     GA[i][3] = i+100-11;  //GB[i][3] = i+100;
     GA[i][4] = i+N-100;   //GB[i][4] = i+11;
     GA[i][5] = i+N-101;   //GB[i][5] = i+10;
     GA[i][6] = i+N-110+100;//GB[i][6] = i+1;
     GA[i][7] = i+N-111+100;//GB[i][7] = i;
    }

    if(i%100 == 0){ //Främre vänstra raden
      GA[i][0] = i;         GB[i][0] = i+111;
      GA[i][1] = i+10-1;    GB[i][1] = i+110;
      GA[i][2] = i+100-10;  GB[i][2] = i+101;
      GA[i][3] = i-11+110;   GB[i][3] = i+100; // +110?? stämmer detta? på [7] också?
      GA[i][4] = i-100;     GB[i][4] = i+11;
      GA[i][5] = i+10-101;  GB[i][5] = i+10;
      GA[i][6] = i+100-110; GB[i][6] = i+1;
      GA[i][7] = i-111+110;  GB[i][7] = i; //?
    }
    if((i)%100 == 99){ // Bakre högra raden
      /*GA[i][0] = i;*/         GB[i][0] = i+111-110;
      /*GA[i][1] = i-1;*/       GB[i][1] = i+110-100;
      /*GA[i][2] = i-10;*/      GB[i][2] = i+101-10;
      /*GA[i][3] = i-11;*/      GB[i][3] = i+100;
      /*GA[i][4] = i-100;*/     GB[i][4] = i+11-110;
      /*GA[i][5] = i-101;*/     GB[i][5] = i+10-100;
      /*GA[i][6] = i-110;*/     GB[i][6] = i+1-10;
      /*GA[i][7] = i-111;*/     GB[i][7] = i;
    }
    if(i>=N-10){ //bakre övre raden
      /*GA[i][0] = i;*/         GB[i][0] = i-N-100+111;
      /*GA[i][1] = i-1;*/       GB[i][1] = i-N-100+110;
      /*GA[i][2] = i-10;*/      GB[i][2] = i-N+101;
      /*GA[i][3] = i-11;*/      GB[i][3] = i-N+100;
      /*GA[i][4] = i-100;*/     GB[i][4] = i+11-100;
      /*GA[i][5] = i-101;*/     GB[i][5] = i+10-100;
      /*GA[i][6] = i-110;*/     GB[i][6] = i+1;
      /*GA[i][7] = i-111;*/     GB[i][7] = i;
    }
    if(i>(N-100) && i%10==9){ // högra sidan övre raden
      /*GA[i][0] = i;*/         GB[i][0] = i-N-10+111;
      /*GA[i][1] = i-1;*/       GB[i][1] = i-N+110;
      /*GA[i][2] = i-10;*/      GB[i][2] = i-N-10+101;
      /*GA[i][3] = i-11;*/      GB[i][3] = i-N+100;
      /*GA[i][4] = i-100;*/     GB[i][4] = i-10+11;
      /*GA[i][5] = i-101;*/     GB[i][5] = i+10;
      /*GA[i][6] = i-110;*/     GB[i][6] = i-10+1;
      /*GA[i][7] = i-111;*/     GB[i][7] = i;
    }
    if(i<100 && i%10 == 0){ // vänstra sidan botten-raden
      GA[i][0] = i;         //GB[i][0] = i+111;
      GA[i][1] = i+10-1;    //GB[i][1] = i+110;
      GA[i][2] = i-10;      //GB[i][2] = i+101;
      GA[i][3] = i+10-11;   //GB[i][3] = i+100;
      GA[i][4] = i+N-100;   //GB[i][4] = i+11;
      GA[i][5] = i+N+10-101;//GB[i][5] = i+10;
      GA[i][6] = i+N-110;   //GB[i][6] = i+1;
      GA[i][7] = i+N+10-111;//GB[i][7] = i;
    }



    if(i == 99){ //Hörn - bakre, lägre högra
      /*GA[i][0] = i;*/         GB[i][0] = 101;
      /*GA[i][1] = i-1;*/       GB[i][1] = 9;
      /*GA[i][2] = i-10;*/      GB[i][2] = 109;
      /*GA[i][3] = i-11;*/      GB[i][3] = 199;
      /*GA[i][4] = i-100;*/     GB[i][4] = N-100;
      /*GA[i][5] = i-101;*/     GB[i][5] = N-91;
      /*GA[i][6] = i-110;*/     GB[i][6] = N-9-1;
      /*GA[i][7] = i-111;*/     GB[i][7] = 99;
    }
                      
    if(i==0){ //Hörn- främfre, lägre vänstra      
      GA[i][0] = i;            //GB[i][0] = i+111;
      GA[i][1] = i-1+10;       //GB[i][1] = i+110;
      GA[i][2] = i-10+100;     //GB[i][2] = i+101;
      GA[i][3] = i-1+100;      //GB[i][3] = i+100;
      GA[i][4] = i-100+N;      //GB[i][4] = i+11;
      GA[i][5] = i-101+N+10;   //GB[i][5] = i+10;
      GA[i][6] = i+N-10;       //GB[i][6] = i+1;
      GA[i][7] = N-1;          //GB[i][7] = i;
    }
  }

  for(i=0; i<N; i++){
    for(j=0; j<8; j++){
      fprintf(neighbourAFile, "%e\t", GA[i][j]);
      fprintf(neighbourBFile, "%e\t", GB[i][j]);
    }
    fprintf(neighbourAFile,"\n");
    fprintf(neighbourBFile, "\n");
  }

  printf("Done!\n");



  return 0;
}
