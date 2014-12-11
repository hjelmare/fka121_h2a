
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ba_func.h"

#define PI 3.14159265
#define CU 0
#define ZN 1
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

double GetLongRangeOrder(int n, int latticeA[])
{
  int i, count = 0;

  for ( i = 0 ; i < n ; i++ ) {
    if( latticeA[i] == CU ) {
      count++;
    }
  }
  printf("count %d\n",count);
  return 2*((double) count / (double) n)-1;
}

double GetShortRangeOrder(int n, int latticeA[], int latticeB[], int neighboursToA[][8])
{
  int i,j, count = 0;
  double r;
  for (i=0; i<n; i++){
    for(j=0; j<8; j++){
      if((latticeA[i]==CU && latticeB[ neighboursToA[i][j] ]==ZN) || (latticeA[i]==ZN && latticeB[ neighboursToA[i][j] ]==CU)){
        count+=1;
      }
    }
  }

  r = (count - 4*n)/(4*n);
  return r;
}

double GetEnergy(int n, int latticeA[], int latticeB[], int neighboursToA[][8], int neighboursToB[][8])
{

  int i, j;
  double energy = 0;
  int myType, neighbourType;

  for ( i = 0 ; i < n ; i++) {
    myType = latticeA[i];
    for ( j = 0 ; j < 8 ; j++ ) {
      neighbourType = latticeB[ neighboursToA[i][j] ];

      if(myType == neighbourType) {
        if ( myType == CU ) {
          energy += ECC;
        } else {
          energy += EZZ;
        }
      } else {
        energy += ECZ;
      }

    }
  }

  for ( i = 0 ; i < n ; i++) {
    myType = latticeB[i];
    for ( j = 0 ; j < 8 ; j++ ) {
      neighbourType = latticeA[ neighboursToB[i][j] ];

      if(myType == neighbourType) {
        if ( myType == CU ) {
          energy += ECC;
        } else {
          energy += EZZ;
        }
      } else {
        energy += ECZ;
      }

    }
  }
  
  energy /= 2;

  return(energy);
}

// This is nothing below this function
void InitializeNeighbourMatrices(int n, int GA[][8], int GB[][8])
{
  int i;
  // Construct the neighbours OBS! in GA there are indexes to LatticeB and GB indexes in latticeA
  // ie. the neighbours to all particles in sublattice A are located in sublattice B.
  for(i=0; i<n; i++){
    // All inner points
    GA[i][0] = i;         GB[i][0] = i+111;
    GA[i][1] = i-1;       GB[i][1] = i+110;
    GA[i][2] = i-10;      GB[i][2] = i+101;
    GA[i][3] = i-11;      GB[i][3] = i+100;
    GA[i][4] = i-100;     GB[i][4] = i+11;
    GA[i][5] = i-101;     GB[i][5] = i+10;
    GA[i][6] = i-110;     GB[i][6] = i+1;
    GA[i][7] = i-111;     GB[i][7] = i;

    if(i<100){  // The bottom side
      GA[i][0] = i;          //GB[i][0] = i+111;
      GA[i][1] = i-1;        //GB[i][1] = i+110;
      GA[i][2] = i-10;        //GB[i][2] = i+101;
      GA[i][3] = i-11;        //GB[i][3] = i+100;
      GA[i][4] = i+n-100;     //GB[i][4] = i+11;
      GA[i][5] = i+n-101;     //GB[i][5] = i+10;
      GA[i][6] = i+n-110;     //GB[i][6] = i+1;
      GA[i][7] = i+n-111;     //GB[i][7] = i;
    }
        
    if(i%100<10){ // Front
      GA[i][0] = i;           //GB[i][0] = i+111;
      GA[i][1] = i-1;         //GB[i][1] = i+110;
      GA[i][2] = i+100-10;    //GB[i][2] = i+101;
      GA[i][3] = i+100-11;    //GB[i][3] = i+100;
      GA[i][4] = i-100;       //GB[i][4] = i+11;
      GA[i][5] = i-101;       //GB[i][5] = i+10;
      GA[i][6] = i-10;        //GB[i][6] = i+1;
      GA[i][7] = i-11;        //GB[i][7] = i;
    }

    // Next up, all the faces
    if((i%100) >= 90){ // Back
      /*GA[i][0] = i;*/         GB[i][0] = i-100+111;
      /*GA[i][1] = i-1;*/       GB[i][1] = i-100+110;
      /*GA[i][2] = i-10;*/      GB[i][2] = i+101;
      /*GA[i][3] = i-11;*/      GB[i][3] = i+100;
      /*GA[i][4] = i-100;*/     GB[i][4] = i-100+11;
      /*GA[i][5] = i-101;*/     GB[i][5] = i-100+10;
      /*GA[i][6] = i-110;*/     GB[i][6] = i+1;
      /*GA[i][7] = i-111;*/     GB[i][7] = i;
    }
    if((i+1)%10==0){ // Right
      /*GA[i][0] = i;*/         GB[i][0] = i+101;
      /*GA[i][1] = i-1;*/       GB[i][1] = i+110;
      /*GA[i][2] = i-10;*/      GB[i][2] = i+91;
      /*GA[i][3] = i-11;*/      GB[i][3] = i+100;
      /*GA[i][4] = i-100;*/     GB[i][4] = i+1;
      /*GA[i][5] = i-101;*/     GB[i][5] = i+10;
      /*GA[i][6] = i-110;*/     GB[i][6] = i-9;
      /*GA[i][7] = i-111;*/     GB[i][7] = i;
    }
    if(i%10==0){ // Left
      GA[i][0] = i;         //GB[i][0] = i+111;
      GA[i][1] = i+9;       //GB[i][1] = i+110;
      GA[i][2] = i-10;      //GB[i][2] = i+101;
      GA[i][3] = i-1;       //GB[i][3] = i+100;
      GA[i][4] = i-100;     //GB[i][4] = i+11;
      GA[i][5] = i-101+10;  //GB[i][5] = i+10;
      GA[i][6] = i-110;     //GB[i][6] = i+1;
      GA[i][7] = i-111+10;  //GB[i][7] = i;
    }
    if(i>(n-100)){ // Top
      /*GA[i][0] = i;*/         GB[i][0] = i+111-100;
      /*GA[i][1] = i-1;*/       GB[i][1] = i+110-100;
      /*GA[i][2] = i-10;*/      GB[i][2] = i+101-100;
      /*GA[i][3] = i-11;*/      GB[i][3] = i+100-100;
      /*GA[i][4] = i-100;*/     GB[i][4] = i+11;
      /*GA[i][5] = i-101;*/     GB[i][5] = i+10;
      /*GA[i][6] = i-110;*/     GB[i][6] = i+1;
      /*GA[i][7] = i-111;*/     GB[i][7] = i;
    }

    // Next up, edges between faces
    if(i<10){ //Främre undre raden 
      GA[i][0] = i;         //GB[i][0] = i+111;
      GA[i][1] = i-1;       //GB[i][1] = i+110;
      GA[i][2] = i+100-10;  //GB[i][2] = i+101;
      GA[i][3] = i+100-11;  //GB[i][3] = i+100;
      GA[i][4] = i+n-100;   //GB[i][4] = i+11;
      GA[i][5] = i+n-101;   //GB[i][5] = i+10;
      GA[i][6] = i+n-110+100;//GB[i][6] = i+1;
      GA[i][7] = i+n-111+100;//GB[i][7] = i;
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
    if(i%100 == 99){ // Bakre högra raden
      /*GA[i][0] = i;*/         GB[i][0] = i+111-110;
      /*GA[i][1] = i-1;*/       GB[i][1] = i+110-100;
      /*GA[i][2] = i-10;*/      GB[i][2] = i+101-10;
      /*GA[i][3] = i-11;*/      GB[i][3] = i+100;
      /*GA[i][4] = i-100;*/     GB[i][4] = i+11-110;
      /*GA[i][5] = i-101;*/     GB[i][5] = i+10-100;
      /*GA[i][6] = i-110;*/     GB[i][6] = i+1-10;
      /*GA[i][7] = i-111;*/     GB[i][7] = i;
    }
    if(i>=n-10){ //bakre övre raden
      /*GA[i][0] = i;*/         GB[i][0] = i-n-100+111;
      /*GA[i][1] = i-1;*/       GB[i][1] = i-n-100+110;
      /*GA[i][2] = i-10;*/      GB[i][2] = i-n+101;
      /*GA[i][3] = i-11;*/      GB[i][3] = i-n+100;
      /*GA[i][4] = i-100;*/     GB[i][4] = i+11-100;
      /*GA[i][5] = i-101;*/     GB[i][5] = i+10-100;
      /*GA[i][6] = i-110;*/     GB[i][6] = i+1;
      /*GA[i][7] = i-111;*/     GB[i][7] = i;
    }
    if(i>(n-100) && i%10==9){ // högra sidan övre raden
      /*GA[i][0] = i;*/         GB[i][0] = i-n-10+111;
      /*GA[i][1] = i-1;*/       GB[i][1] = i-n+110;
      /*GA[i][2] = i-10;*/      GB[i][2] = i-n-10+101;
      /*GA[i][3] = i-11;*/      GB[i][3] = i-n+100;
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
      GA[i][4] = i+n-100;   //GB[i][4] = i+11;
      GA[i][5] = i+n+10-101;//GB[i][5] = i+10;
      GA[i][6] = i+n-110;   //GB[i][6] = i+1;
      GA[i][7] = i+n+10-111;//GB[i][7] = i;
    }



    if(i == 99){ //Hörn - bakre, lägre högra
      /*GA[i][0] = i;*/         GB[i][0] = 100;
      /*GA[i][1] = i-1;*/       GB[i][1] = 109;
      /*GA[i][2] = i-10;*/      GB[i][2] = 190;
      /*GA[i][3] = i-11;*/      GB[i][3] = 199;
      /*GA[i][4] = i-100;*/     GB[i][4] = 0;
      /*GA[i][5] = i-101;*/     GB[i][5] = 9;
      /*GA[i][6] = i-110;*/     GB[i][6] = 90;
      /*GA[i][7] = i-111;*/     GB[i][7] = 99;
    }
                      
    if(i==0){ //Hörn- främfre, lägre vänstra      
      GA[i][0] = i;            //GB[i][0] = i+111;
      GA[i][1] = i-1+10;       //GB[i][1] = i+110;
      GA[i][2] = i-10+100;     //GB[i][2] = i+101;
      GA[i][3] = i-1+100;      //GB[i][3] = i+100;
      GA[i][4] = i-100+n;      //GB[i][4] = i+11;
      GA[i][5] = i-101+n+10;   //GB[i][5] = i+10;
      GA[i][6] = i+n-10;       //GB[i][6] = i+1;
      GA[i][7] = n-1;          //GB[i][7] = i;
    }
    if(i == 999){
      GB[i][0] = i-n-100-10+111; 
      GB[i][1] = i-n-100+110;
      GB[i][2] = i-n-10+101;
      GB[i][3] = i-n+100;
      GB[i][4] = i-100-10+11;
      GB[i][5] = i-100+10;
      GB[i][6] = i-10+1;
      GB[i][7] = i;
    }
  }

  return;
}

