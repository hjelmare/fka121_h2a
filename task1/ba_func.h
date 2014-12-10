#ifndef _ba_func
#define _ba_func

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void InitializeSystem(int N, double CnParticles[][8], double ZnParticles[][8]);
double getEnergy(int N, double CnParticles[][8], double ZnParticles[][8]);

#endif
