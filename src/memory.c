#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"

int *new_ivec(int n) {
    int *p = (int *)malloc(sizeof(int)*n);
    return p;
}

int *zero_ivec(int n) {
    int *p = (int *)calloc(n,sizeof(int));
    return p;
}

void del_ivec(int *p) {
    free(p);
    p = NULL;
}

void nil_ivec(int n, int *p) {
    memset(p,0,sizeof(int)*n);
}

void copy_ivec(int n, int *dest, int *p) {
    memcpy(dest,p,n*sizeof(int));
}

double *new_dvec(int n) {
    double *p = (double *)malloc(sizeof(double)*n);
    return p;
}

double *zero_dvec(int n) {
    double *p = (double *)calloc(n,sizeof(double));
    return p;
}

void del_dvec(double *p) {
    free(p);
    p = NULL;
}

void nil_dvec(int n, double *p) {
    memset(p,0,sizeof(double)*n);
}

void copy_dvec(int n, double *dest, double *p) {
    memcpy(dest,p,n*sizeof(double));
}

int **new_imat(int nx, int ny) {
    int **p = (int **)malloc(sizeof(int *)*nx);
    p[0] = (int *)malloc(sizeof(int)*nx*ny);
    for (int i=0; i<nx; ++i)
        p[i] = p[0]+ny*i;
    return p;
}

int **zero_imat(int nx, int ny) {
    int **p = (int **)malloc(sizeof(int *)*nx);
    p[0] = (int *)calloc(nx*ny,sizeof(int));
    for (int i=0; i<nx; ++i)
        p[i] = p[0]+ny*i;
    return p;
}

void del_imat(int **p) {
    free(p[0]);
    free(p);
    p = NULL;
} 

void nil_imat(int nx, int ny, int **p) {
    memset(*p,0,sizeof(int)*nx*ny);
}

void copy_imat(int nx, int ny, int **dest, int **p) {
    memcpy(*dest,*p,nx*ny*sizeof(int));
}

double **new_dmat(int nx, int ny) {
    double **p = (double **)malloc(sizeof(double *)*nx);
    p[0] = (double *)malloc(sizeof(double)*nx*ny);
    for (int i=0; i<nx; ++i)
        p[i] = p[0]+ny*i;
    return p;
}

double **zero_dmat(int nx, int ny) {
    double **p = (double **)malloc(sizeof(double *)*nx);
    p[0] = (double *)calloc(nx*ny,sizeof(double));
    for (int i=0; i<nx; ++i)
        p[i] = p[0]+ny*i;
    return p;
}

void del_dmat(double **p) {
    free(p[0]);
    free(p);
    p = NULL;
}

void nil_dmat(int nx, int ny, double **p) {
    memset(*p,0,sizeof(double)*nx*ny);
}

void copy_dmat(int nx, int ny, double **dest, double **p) {
    memcpy(*dest,*p,nx*ny*sizeof(double));
}

int ***new_icub(int nx, int ny, int nz) {
    int ***p = (int ***)malloc(sizeof(int **)*nz);
    p[0] = (int **)malloc(sizeof(int *)*nz*nx);
    p[0][0] = (int *)malloc(sizeof(int)*nz*nx*ny);
    for (int i=0; i<nz; ++i) {
        p[i] = p[0]+nx*i;
        for (int j=0; j<nx; ++j)
            p[i][j] = p[0][0]+ny*(nx*i+j);
    }
    return p;
}

int ***zero_icub(int nx, int ny, int nz) {
    int ***p = (int ***)malloc(sizeof(int **)*nz);
    p[0] = (int **)malloc(sizeof(int *)*nz*nx);
    p[0][0] = (int *)calloc(nx*ny*nz,sizeof(int));
    for (int i=0; i<nz; ++i) {
        p[i] = p[0]+nx*i;
        for (int j=0; j<nx; ++j)
            p[i][j] = p[0][0]+ny*(nx*i+j);
    }
    return p;
}

void del_icub(int ***p) {
    free(p[0][0]);
    free(p[0]);
    free(p);
    p = NULL;
}

void nil_icub(int nx, int ny, int nz, int ***p) {
    memset(**p,0,sizeof(int)*nx*ny*nz);
}

void copy_icub(int nx, int ny, int nz, int ***dest, int ***p) {
    memcpy(**dest,**p,nx*ny*nz*sizeof(int));
}

double ***new_dcub(int nx, int ny, int nz) {
    double ***p = (double ***)malloc(sizeof(double **)*nz);
    p[0] = (double **)malloc(sizeof(double *)*nz*nx);
    p[0][0] = (double *)malloc(sizeof(double)*nz*nx*ny);
    for (int i=0; i<nz; ++i) {
        p[i] = p[0]+nx*i;
        for (int j=0; j<nx; ++j)
            p[i][j] = p[0][0]+ny*(nx*i+j);
    }
    return p;
}

double ***zero_dcub(int nx, int ny, int nz) {
    double ***p = (double ***)malloc(sizeof(double **)*nz);
    p[0] = (double **)malloc(sizeof(double *)*nz*nx);
    p[0][0] = (double *)calloc(nx*ny*nz,sizeof(double));
    for (int i=0; i<nz; ++i) {
        p[i] = p[0]+nx*i;
        for (int j=0; j<nx; ++j)
            p[i][j] = p[0][0]+ny*(nx*i+j);
    }
    return p;
}

void del_dcub(double ***p) {
    free(p[0][0]);
    free(p[0]);
    free(p);
    p = NULL;
} 

void nil_dcub(int nx, int ny, int nz, double ***p) {
    memset(**p,0,sizeof(double)*nx*ny*nz);
}

void copy_dcub(int nx, int ny, int nz, double ***dest, double ***p) {
    memcpy(**dest,**p,nx*ny*nz*sizeof(double));
}
