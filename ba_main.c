
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
  }
  // Construct the neighbours OBS! in GA there are indexes to LatticeB and GB indexes in latticeA
  // ie. the neighbours to all particles in sublattice A are located in sublattice B.
  for(i=0; i<N; i++){
 /*     if(i==0){ //Kant- främfre, lägre vänstra
        
        GA[i][0] = i;            GB[i][0] = i+111;
        GA[i][1] = i-1+10;       GB[i][1] = i+110;
        GA[i][2] = i-10+100;     GB[i][2] = i+101;
        GA[i][3] = 10;           GB[i][3] = i+100;
        GA[i][4] = i-100+N;      GB[i][4] = i+11;
        GA[i][5] = i-101+N-100;  GB[i][5] = i+10;
        GA[i][6] = i+N-10;       GB[i][6] = i+1;
        GA[i][7] = N;            GB[i][7] = i;
      }else{ if(i == 99){ //Kant - bakre, lägre högra
          GA[i][0] = i;         GB[i][0] = 101;
          GA[i][1] = i-1;       GB[i][1] = 9;
          GA[i][2] = i-10;      GB[i][2] = 109;
          GA[i][3] = i-11;      GB[i][3] = 199;
          GA[i][4] = i-100;     GB[i][4] = N-100;
          GA[i][5] = i-101;     GB[i][5] = N-91;
          GA[i][6] = i-110;     GB[i][6] = N-9-1;
          GA[i][7] = i-111;     GB[i][7] = 99;
        }else{ if(i==N-1){ //Kant - bakre, övre högra
            GA[i][0] = i;         GB[i][0] = 0;
            GA[i][1] = i-1;       GB[i][1] = N-1-100;
            GA[i][2] = i-10;      GB[i][2] = 9;
            GA[i][3] = i-11;      GB[i][3] = 99;
            GA[i][4] = i-100;     GB[i][4] = N-100;
            GA[i][5] = i-101;     GB[i][5] = N-100+9;
            GA[i][6] = i-110;     GB[i][6] = N-9;
            GA[i][7] = i-111;     GB[i][7] = N-1;

          }else{ if(i<100){  //the "floor" boundary condition. (100 particles to the next lvl)
              GA[i][0] = i;           GB[i][0] = i+111;
              GA[i][1] = i-1;         GB[i][1] = i+110;
              GA[i][2] = i-10;        GB[i][2] = i+101;
              GA[i][3] = i-11;        GB[i][3] = i+100;
              GA[i][4] = N+i-100;     GB[i][4] = i+11;
              GA[i][5] = N+i-101;     GB[i][5] = i+10;
              GA[i][6] = N+i-110;     GB[i][6] = i+1;
              GA[i][7] = N+i-111;     GB[i][7] = i;
        
            }else{ if((i+1)%100<10){ // Främre sidan
                GA[i][0] = i;           GB[i][0] = i+111;
                GA[i][1] = i-1;         GB[i][1] = i+110;
                GA[i][2] = i+100-10;    GB[i][2] = i+101;
                GA[i][3] = i+100-11;    GB[i][3] = i+100;
                GA[i][4] = i-100;       GB[i][4] = i+11;
                GA[i][5] = i-101;       GB[i][5] = i+10;
                GA[i][6] = i-10;        GB[i][6] = i+1;
                GA[i][7] = i-11;        GB[i][7] = i;
              }else{ if((i+1+10)%100<10){ //Bortre sidan
                  GA[i][0] = i;         GB[i][0] = i+211;
                  GA[i][1] = i-1;       GB[i][1] = i+110;
                  GA[i][2] = i-10;      GB[i][2] = i+101;
                  GA[i][3] = i-11;      GB[i][3] = i+100;
                  GA[i][4] = i-100;     GB[i][4] = i+111;
                  GA[i][5] = i-101;     GB[i][5] = i+110;
                  GA[i][6] = i-110;     GB[i][6] = i+1;
                  GA[i][7] = i-111;     GB[i][7] = i;
         
                }else{ if((i+1)%10==0){ //Högra sidan
                    GA[i][0] = i;         GB[i][0] = i+101;
                    GA[i][1] = i-1;       GB[i][1] = i+110;
                    GA[i][2] = i-10;      GB[i][2] = i+91;
                    GA[i][3] = i-11;      GB[i][3] = i+100;
                    GA[i][4] = i-100;     GB[i][4] = i+1;
                    GA[i][5] = i-101;     GB[i][5] = i+10;
                    GA[i][6] = i-110;     GB[i][6] = i-9;
                    GA[i][7] = i-111;     GB[i][7] = i;
         
                  }else{ if((i-1)%10==0){ //Västra sidan
                      GA[i][0] = i;         GB[i][0] = i+111;
                      GA[i][1] = i+9;       GB[i][1] = i+110;
                      GA[i][2] = i-10;      GB[i][2] = i+101;
                      GA[i][3] = i-1;       GB[i][3] = i+100;
                      GA[i][4] = i-100;     GB[i][4] = i+11;
                      GA[i][5] = i-101+10;  GB[i][5] = i+10;
                      GA[i][6] = i-110;     GB[i][6] = i+1;
                      GA[i][7] = i-111+10;  GB[i][7] = i;
         
                   }else{ if(i>(N-100)){ // Övre sidan
                        GA[i][0] = i;         GB[i][0] = i+111-100;
                        GA[i][1] = i-1;       GB[i][1] = i+110-100;
                        GA[i][2] = i-10;      GB[i][2] = i+101-100;
                        GA[i][3] = i-11;      GB[i][3] = i+100-100;
                        GA[i][4] = i-100;     GB[i][4] = i+11;
                        GA[i][5] = i-101;     GB[i][5] = i+10;
                        GA[i][6] = i-110;     GB[i][6] = i+1;
                        GA[i][7] = i-111;     GB[i][7] = i;
         
                    }else{ */ //The neighbours to particles that's not affected by the boudary.
                          GA[i][0] = i;         GB[i][0] = i+111;
                          GA[i][1] = i-1;       GB[i][1] = i+110;
                          GA[i][2] = i-10;      GB[i][2] = i+101;
                          GA[i][3] = i-11;      GB[i][3] = i+100;
                          GA[i][4] = i-100;     GB[i][4] = i+11;
                          GA[i][5] = i-101;     GB[i][5] = i+10;
                          GA[i][6] = i-110;     GB[i][6] = i+1;
                          GA[i][7] = i-111;     GB[i][7] = i;
    /*                   }
                    }
                  }
                }
              }
            }
          }
        }
      } */
  }

  for(i=0; i<N; i++){
    for(j=0; j<8; j++){
      fprintf(neighbourAFile, "%e\t", GA[i][j]);
      fprintf(neighbourBFile, "%e\t", GB[i][j]);
    }
    fprintf(neighbourAFile,"\n");
    fprintf(neighbourBFile, "\n");
  }


/* -------------------------------------------------------------------------------------------------------------------------
  randZn = (int) ( ( (double) rand() / (double) RAND_MAX ) * N);
  randCu = (int) ( ( (double) rand() / (double) RAND_MAX ) * N);

  for ( i = 0 ; i < 8 ; i++) {
    if( CuParticles[randCu][i] == ZN ) {
      nZnChanges++;
    }
    if( ZnParticles[randZn][i] == CU ) {
      nCuChanges++;
    }
  }
  printf("znChanges %d\n", nZnChanges); 
  i = 0;
  while ( nZnChanges > 0 ) {
    if ( ZnParticles[(int) i / (int) 8][i%8] == CU ) {
      nZnChanges--;
      ZnParticles[(int) i / (int) 8][i%8] = ZN;
    }
    i++;
    if ( (int) i / (int) 8 == randZn ) {
      i += 8;
    }
    if ( i > 8*N ) {
      i = 0;
    }
    printf("zn %d\n",i);
  }

  i = 0;
  while ( nCuChanges > 0 ) {
    if ( CuParticles[(int) i / (int) 8][i%8] == ZN ) {
      nCuChanges--;
      CuParticles[(int) i / (int) 8][i%8] = CU;
    }
    i++;
    if ( (int) i / (int) 8 == randCu ) {
      i += 8;
    }
    if ( i > 8*N ) {
      i = 0;
    }
  }
  
  for ( i = 0 ; i < 8 ; i++ ) {
    temporaryStorage[i] = CuParticles[randCu][i];
    CuParticles[randCu][i] = ZnParticles[randZn][i];
    ZnParticles[randZn][i] = temporaryStorage[i];
  } -------------------------------------------------------------------------------------------------------------------------
*/ 

  printf("Done!\n");



  return 0;
}
