#include <stdio.h>
#include <string.h>
#include "debug.h"
#include "linalg.h"

void dst_eval (int n, double *D, double *E) {
    if (n<2 || !D || !E)
        _error("No element in D or E vectors?");
    int INFO = 0;
    double *Z = 0;
    double *WORK = (double *)malloc((2*n-2)*sizeof(double));
    dstev_ ((char *)&_CHR_N,&n,D,E,Z,&n,WORK,&INFO);
    free(WORK);
}

void dst_esys (int n, double *D, double *E, double **evec) {
    if (n<2 || !D || !E)
        _error("No element in D or E vectors?");
    int INFO = 0;
    double *WORK = (double *)malloc((2*n-2)*sizeof(double));
    dstev_ ((char *)&_CHR_V,&n,D,E,*evec,&n,WORK,&INFO);
    free(WORK);
}

void dsy_eval (int n, double **A, double *eval) {
    if (n<1 || !A)
        _error("No element in A matrix?");
    int INFO = 0;
    int LWORK = 3*n-1;
    double *VECA = (double *)malloc(n*n*sizeof(double));
    double *WORK = (double *)malloc(LWORK*sizeof(double));
    memcpy(VECA,*A,n*n*sizeof(double));
    dsyev_ ((char *)&_CHR_N,(char *)&_CHR_L,&n,VECA,&n,eval,WORK,&LWORK,&INFO);
    free(WORK);
    free(VECA);
}

void dsy_esys (int n, double **A, double *eval, double **evec) {
    if (n<1 || !A)
        _error("No element in A matrix?");
    int INFO = 0;
    int LWORK = 3*n-1;
    double *WORK = (double *)malloc(LWORK*sizeof(double));
    memcpy(*evec,*A,n*n*sizeof(double));
    dsyev_ ((char *)&_CHR_V,(char *)&_CHR_L,&n,*evec,&n,eval,WORK,&LWORK,&INFO);
    free(WORK);
}
