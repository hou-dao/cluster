#ifndef CLUSTER_H_
#define CLUSTER_H_

double dist  (int nv, const double *x, const double *y);
double dist2 (int nv, const double *x, const double *y);
double kmeans  (int ini_seed, int nk, int nt, int nv, double **data, int *cents, int *assignment);
double kcenter (int nk, int nt, int nv, double **data, int *cents, int *assignment);

#endif
