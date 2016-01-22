#include <math.h>
#include <stdlib.h>
#include "linalg.h"

int    sum_ivec (int n, int *x) {
    int _sum = 0;
    while (n--)
        _sum += *x++;
    return _sum;
}

double sum_dvec (int n, double *x) {
    double _sum = 0;
    while (n--)
        _sum += *x++;
    return _sum;
}

double avg_dvec (int n, double *x) {
    return sum_dvec(n,x)/(double)n;
}

void   abs_ivec (int n, int *x) {
    for (int i=0; i<n; ++i)
        x[i] = abs(x[i]);
}

void   abs_dvec (int n, double *x) {
    for (int i=0; i<n; ++i)
        x[i] = fabs(x[i]);
}

int    max_ivec (int n, int *x) {
    int *ptr = x;
    if (n == 1)
        return *ptr;
    else {
        for (int i=1; i<n; ++i) {
            if (x[i] > *ptr)
                ptr = &x[i];
        }
    }
    return *ptr;
}

double max_dvec (int n, double *x) {
    double *ptr = x;
    if (n == 1)
        return *ptr;
    else {
        for (int i=1; i<n; ++i) {
            if (x[i] > *ptr)
                ptr = &x[i];
        }
    }
    return *ptr;
}

int    min_ivec (int n, int *x) {
    int *ptr = x;
    if (n == 1)
        return *ptr;
    else {
        for (int i=1; i<n; ++i) {
            if (x[i] < *ptr)
                ptr = &x[i];
        }
    }
    return *ptr;
}
    
double min_dvec (int n, double *x) {
    double *ptr = x;
    if (n == 1)
        return *ptr;
    else {
        for (int i=1; i<n; ++i) {
            if (x[i] < *ptr)
                ptr = &x[i];
        }
    }
    return *ptr;
}

double nrm_dvec (int n, double *x) {
    double _sum = 0;
    for (int i=0; i<n; ++i)
        _sum += x[i]*x[i];
    return sqrt(_sum);
}

double dot_dvec (int n, double *x1, double *x2) {
    double _sum = 0;
    for (int i=0; i<n; ++i)
        _sum += (*x1++)*(*x2++);
    return _sum;
}

double trc_dmat (int n, double **a) {
    double _sum = 0;
    while (n--)
        _sum += a[n][n];
    return _sum;
}

void   mul_dgmv (int m, int n, double **a, double *x, double *y) {
    for (int i=0; i<m; ++i) {
        double tmp = 0;
        for (int j=0; j<n; ++j)
            tmp += a[i][j]*x[j];
        y[i] = tmp;
    }
}

void   mul_dgmm (int m, int n, int k, double **a, double **b, double **c) {
    for (int i=0; i<m; ++i) {
    for (int j=0; j<n; ++j) {
        double tmp = 0;
        for (int l=0; l<k; ++l)
            tmp += a[i][l]*b[l][j];
        c[i][j] = tmp;
    }
    }
}
