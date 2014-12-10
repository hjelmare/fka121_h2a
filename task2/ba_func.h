#ifndef _BA_FUNC
#define _BA_FUNC


void InitializeSystem(int N, int latticeA[], int latticeB[]);
double GetEnergy(int N, int latticeA[], int latticeB[], int neighboursToA[][8], int neighboursToB[][8]);

#endif
