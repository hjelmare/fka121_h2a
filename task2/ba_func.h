#ifndef _BA_FUNC
#define _BA_FUNC


void InitializeSystem(int n, int latticeA[], int latticeB[]);
double GetEnergy(int n, int latticeA[], int latticeB[], int neighboursToA[][8], int neighboursToB[][8]);
void InitializeNeighbourMatrices(int n, int GA[][8], int GB[][8]);

#endif
