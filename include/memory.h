#ifndef MEMORY_H_
#define MEMORY_H_

int    *new_ivec(int n);
int    *zero_ivec(int n);
void    del_ivec(int *ivec);
void    nil_ivec(int n, int *ivec);
void    copy_ivec(int n, int *dest, int *ivec);

double *new_dvec(int n);
double *zero_dvec(int n);
void    del_dvec(double *dvec);
void    nil_dvec(int n, double *dvec);
void    copy_dvec(int n, double *dest, double *dvec);

int    **new_imat(int nx, int ny);
int    **zero_imat(int nx, int ny);
void     del_imat(int **imat);
void     nil_imat(int nx, int ny, int **imat);
void     copy_imat(int nx, int ny, int **dest, int **imat);

double **new_dmat(int nx, int ny);
double **zero_dmat(int nx, int ny);
void     del_dmat(double **dmat);
void     nil_dmat(int nx, int ny, double **dmat);
void     copy_dmat(int nx, int ny, double **dest, double **dmat);

int    ***new_icub(int nx, int ny, int nz);
int    ***zero_icub(int nx, int ny, int nz);
void      del_icub(int ***icub);
void      nil_icub(int nx, int ny, int nz, int ***icub);
void      copy_icub(int nx, int ny, int nz, int ***dest, int ***icub);

double ***new_dcub(int nx, int ny, int nz);
double ***zero_dcub(int nx, int ny, int nz);
void      del_dcub(double ***dcub);
void      nil_dcub(int nx, int ny, int nz, double ***dcub);
void      copy_dcub(int nx, int ny, int nz, double ***dest, double ***dcub);

#endif
