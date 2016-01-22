#ifndef LINALG_H_
#define LINALG_H_

static const char _CHR_A = 'A';
static const char _CHR_B = 'B';
static const char _CHR_C = 'C';
static const char _CHR_D = 'D';
static const char _CHR_E = 'E';
static const char _CHR_F = 'F';
static const char _CHR_G = 'G';
static const char _CHR_H = 'H';
static const char _CHR_I = 'I';
static const char _CHR_J = 'J';
static const char _CHR_K = 'K';
static const char _CHR_L = 'L';
static const char _CHR_M = 'M';
static const char _CHR_N = 'N';
static const char _CHR_O = 'O';
static const char _CHR_P = 'P';
static const char _CHR_Q = 'Q';
static const char _CHR_R = 'R';
static const char _CHR_S = 'S';
static const char _CHR_T = 'T';
static const char _CHR_U = 'U';
static const char _CHR_V = 'V';
static const char _CHR_W = 'W';
static const char _CHR_X = 'X';
static const char _CHR_Y = 'Y';
static const char _CHR_Z = 'Z';

static const  int _INT_0  =  0;
static const  int _INT_P1 =  1;
static const  int _INT_M1 = -1;

static const double _DBL_0  =  0.0;
static const double _DBL_P1 =  1.0;
static const double _DBL_M1 = -1.0;


// ROUTINES FROM LAPACK & BLAS
// ---------------------------

void dgesv_ (int *N, int *NRHS, double *A, int *LDA, int *IPIV, double *B, int *LDB, int *INFO);

void dstev_ (char *JOBZ, int *N, double *D, double *E, double *Z, int *LDZ, double *WORK, int *INFO);

void dsyev_ (char *JOBZ, char *UPLO, int *N, double *A, int *LDA, double *W, double *WORK, int *LWORK, int *INFO);

// LU decomoposition of a general matrix
void dgetrf_(int *M, int *N, double *A, int *lda, int *IPIV, int *INFO);

// generate inverse of a matrix given its LU decomposition
void dgetri_(int *N, double *A, int *lda, int *IPIV, double *WORK, int *lwork, int *INFO);

void dscal_ (int *N, double *ALPHA, double *X, int *INCX);

void daxpy_ (int *N, double *ALPHA, double *X, int *INCX, double *Y, int *INCY);

void dgemv_ (char *TRANS, int *M, int *N, double *ALPHA, double *A, int *LDA, double *X, int *INCX, double *BETA, double *Y, int *INCY);

// vectors

int    sum_ivec (int n, int *vec);
double sum_dvec (int n, double *vec);

int    avg_ivec (int n, int *vec);
double avg_dvec (int n, double *vec);

void   abs_ivec (int n, int *vec);
void   abs_dvec (int n, double *vec);

int    max_ivec (int n, int *vec);
double max_dvec (int n, double *vec);

int    min_ivec (int n, int *vec);
double min_dvec (int n, double *vec);

double nrm_dvec (int n, double *vec);

double dot_dvec (int n, double *vec1, double *vec2);

// matrix vector multiply
void   mul_dgmv (int m, int n, double **mat, double *vec1, double *vec2);

// matrix matrix multiply
void   mul_dgmm (int m, int n, int k, double **mata, double **matb, double **matc);

// trace(A)

double trc_dmat (int n, double **mat);

// inverse(A)

void   inv_dmat (int n, double **mat);

//  linear solver

void   lsolve_dgesv (int n, double **mat, double *vec);

//  eigenvalue & eigenvector

void   dst_eval (int N, double *D, double *E);

void   dst_esys (int N, double *D, double *E, double **Evec);

void   dsy_eval (int N, double **A, double *Eval);

void   dsy_esys (int N, double **A, double *Eval, double **Evec);

#endif
