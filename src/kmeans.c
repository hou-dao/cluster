#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "io.h"
#include "memory.h"
#include "cluster.h"

#define EPS (1.e-10)
#define min(a,b) ((a)<(b)?(a):(b))

double kmeans (int ini_seed, int nk, int nt, int nv, double **data, int *cents, int *assignment) {

    srand(time(NULL));
    if (ini_seed == 0) { // standard kmeans
        int *sign = (int *)calloc(nt,sizeof(int));
        for (int k=0; k<nk; ++k) {
            int random = rand()%nt;
            while (sign[random] == 1)
                random = rand()%nt;
            cents[k] = random;
            sign[random] = 1;
        }
        free(sign);
        sign = NULL;
    } else { // kmeans++
        int seed = 1;
        cents[0] = rand()%nt;
        // printf("Initial centers!\n");
        // printf("seed %7d: %7d\n",0,cents[0]);
        double *VecDist2 = (double *)malloc(nt*sizeof(double));
        for (int i=0; i<nt; ++i) 
            VecDist2[i] = 1.e60;
        while (seed < nk) {
            double SumDist2 = 0;
            for (int i=0; i<nt; ++i) {
                double Dist2 = dist2(nv,data[i],data[cents[seed-1]]);
                VecDist2[i] = min(Dist2,VecDist2[i]);
                SumDist2 += VecDist2[i];
            }
            double random = (double)rand()/RAND_MAX;
            double cumprob = 0;
            for (int i=0; i<nt; ++i) {
                double prob = cumprob+VecDist2[i]/SumDist2;
                if (random>=cumprob && random<prob) {
                    cents[seed] = i;
                    break;
                } else
                    cumprob = prob;
            }
            // printf("seed %7d: %7d\n",seed,cents[seed]);
            ++seed;
        }
        free(VecDist2);
        VecDist2 = NULL;
#ifdef _DEBUG
    if (seed != nk) printf("Error! Inconsistent number of centers!\n");
#endif
    }

    // allocate
    int **kmemb = (int **)malloc(nk*sizeof(int *));
    kmemb[0] = (int *)calloc(nt,sizeof(int));
    int *ksize = (int *)malloc(nk*sizeof(int));
    int *kiter = (int *)malloc(nk*sizeof(int));
    double *VDist2 = (double *)malloc(nt*sizeof(double));

    double MinOverallSum = 1.e60;

    // timeit
    clock_t tic1, tic2;
    double cumt1 = 0.0, cumt2 = 0.0;
    // loop
    int MaxIter = 100;
    while (MaxIter--) {
        tic1 = clock();
        memset(ksize,0,nk*sizeof(int));
        for (int i=0; i<nt; ++i) {
            VDist2[i] = 1.e60;
            assignment[i] = -1;
        }
        // assign to k centers
        for (int k=0; k<nk; ++k) {
            int j = cents[k];
            for (int i=0; i<nt; ++i) {
                double Dist = dist2(nv,data[i],data[j]);
                if (Dist < VDist2[i]) {
                    if (assignment[i] < 0) 
                        ksize[k] += 1;
                    else {
                        ksize[assignment[i]] -= 1;
                        ksize[k] += 1;
                    }
                    assignment[i] = k;
                    VDist2[i] = Dist;
                }
            }
        }

        tic2 = clock();
        cumt1 += (double)(tic2-tic1)/CLOCKS_PER_SEC;

        // find all IDs in every center 
        for (int k=1; k<nk; ++k)
            kmemb[k] = kmemb[k-1]+ksize[k-1];
        memset(kiter,0,nk*sizeof(int));
        for (int i=0; i<nt; ++i) {
            int k = assignment[i];
            kmemb[k][kiter[k]] = i;
            kiter[k] += 1;
        }

#ifdef _DEBUG
        for (int k=0; k<nk; ++k) {
            if (kiter[k] != ksize[k])
                printf("Error! Inconsistent!\n");
        }
#endif

        tic1 = clock();
        // renew centers
        double OverallSum = 0;
        for (int k=0; k<nk; ++k) {
            double MinSumDist = 1.e60;
            for (int ki=0; ki<ksize[k]; ++ki) {
                int i = kmemb[k][ki];
                double SumDist = 0.0;
                for (int kj=0; kj<ksize[k]; ++kj) {
                    int j = kmemb[k][kj];
                    if (i != j)
                        SumDist += dist2(nv,data[i],data[j]);
                }
                if (SumDist < MinSumDist) {
                    MinSumDist = SumDist;
                    cents[k] = i;
                }
            }
            OverallSum += MinSumDist;
        }
        tic2 = clock();
        cumt2 += (double)(tic2-tic1)/CLOCKS_PER_SEC;

        if (fabs(OverallSum-MinOverallSum) < EPS)
            break;
        MinOverallSum = min(OverallSum,MinOverallSum);

        printf("Update centers: iteration %d\n",100-MaxIter);
        // for (int i=0; i<nt; ++i)
        //     printf("%d\n",cents[i]);
    }
    printf("%16.6e %16.6e\n",cumt1,cumt2);
    free(VDist2);
    free(kiter);
    free(ksize);
    free(kmemb[0]);
    free(kmemb);
    return MinOverallSum;
}
