#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "debug.h"
#include "memory.h"

double **load_dmat (char fnam[], int *nrow, int *ncol, int *ntot) {
    FILE *fmat = fopen(fnam, "r");
    if (fmat == NULL) {
        _error("File %s not exist!",fnam);
    } else {
        int irow = 0, icol = 0, itot = 0;
        double temp = 0;
        char title[256];
        fgets(title,sizeof(title),fmat);
        fgets(title,sizeof(title),fmat);
        fscanf(fmat,"%d%d%d",nrow,ncol,ntot);
        double **mat = zero_dmat(*nrow,*ncol);
        while (fscanf(fmat,"%d%d%lf",&irow,&icol,&temp) != EOF) {
            if (irow>=*nrow || icol>=*ncol)
                _error("File %s overflow!", fnam);
            mat[irow-1][icol-1] = temp;
            ++itot;
        }
        if (itot != *ntot)
            _alert("Number of nonzero elements not consistent!\n");
        return mat;
    }
    fclose(fmat);
    return NULL;
}

/*
 * Show double dmat[nrow][ncol]
 * with elements in format of digit
 */
void show_dmat (char name[], char digit[], int nrow, int ncol, double **dmat) {
    printf("%s:\n", name);
    for (int i=0; i<nrow; ++i) {
        for (int j=0; j<ncol; ++j)
            printf(digit,dmat[i][j]);
        printf("\n");
    }
}

/*
 * Save double dmat[nrow][ncol]
 * with elements in format of digit
 */
void save_dmat (char name[], char digit[], int nrow, int ncol, double **dmat) {
    FILE *fnam = fopen(name,"w");
    for (int i=0; i<nrow; ++i) {
        for (int j=0; j<ncol; ++j)
            fprintf(fnam,digit,dmat[i][j]);
        fprintf(fnam,"\n");
    }
    fclose(fnam);
}

void save_ivec (char name[], int nvec, int *vec) {
    FILE *fnam = fopen(name,"w");
    for (int i=0; i<nvec; ++i) {
        fprintf(fnam,"%d\n",vec[i]);
    }
    fclose(fnam);
}
