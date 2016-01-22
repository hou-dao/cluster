#include <stdio.h>
#include <stdlib.h>
#include "linalg.h"

void lsolve_dgesv (int n, double **a, double *b) {

    int nrhs = 1;
    int lda = n;
    int ldb = n;
    int info = 0;
    int *ipiv = (int *)malloc(n*sizeof(int));
    double *at = (double *)malloc(n*n*sizeof(double));
    for (int i=0; i<n; ++i)
    for (int j=0; j<n; ++j)
        at[i*n+j] = a[j][i];
    dgesv_(&n,&nrhs,at,&lda,ipiv,b,&ldb,&info);
    if (info != 0) {
        printf("Failed in %s\n",__func__);
    }
    free(at);
    at = 0;
    free(ipiv);
    ipiv = 0;
}
