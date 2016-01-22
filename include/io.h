#ifndef IO_H_
#define IO_H_

double **load_dmat(char filename[], int *nrow, int *ncol, int *ntot);

void show_dmat(char dmatname[], char format[], int nrow, int ncol, double **dmat);

void save_dmat(char dmatname[], char format[], int nrow, int ncol, double **dmat);

void save_ivec(char ivecname[], int nvec, int *vec);

#endif
