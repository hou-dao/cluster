#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "io.h"
#include "memory.h"
#include "cluster.h"

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

double kcenter (int nk, int nt, int nv, double **data, int *cents, int *assignment) {

    srand(time(NULL));
    int seed = 0;
    cents[0] = rand()%nt;

    double *VecDist = (double *)malloc(nt*sizeof(double));
    for (int i=0; i<nt; ++i) VecDist[i] = 1.e60;
    while (seed++ < nk) {
        double MaxDist = 0.0;
        for (int i=0; i<nt; ++i) {
            double Dist = dist(nv,data[i],data[cents[seed-1]]);
            if (Dist < VecDist[i]) {
                VecDist[i] = Dist;
                assignment[i] = seed-1;
            }
            if (MaxDist < VecDist[i]) {
                MaxDist = VecDist[i];
                cents[seed] = i;
            }
        }
    }

#ifdef _DEBUG
    if (seed != nk) printf("Error! inconsistent Seed NO\n");
#endif

    double MaxDist = 0;
    for (int i=0; i<nt; ++i)
        MaxDist = max(MaxDist,VecDist[i]);
    free(VecDist);
    return MaxDist;
}
