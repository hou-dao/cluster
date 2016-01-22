#ifdef _MPI
#include "mpi.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "io.h"
#include "memory.h"
#include "cluster.h"

int main (int argc, char *argv[]) {

    int _size = 1;
    int _rank = 0;
#ifdef _MPI
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&_size);
    MPI_Comm_rank(MPI_COMM_WORLD,&_rank);
#endif

    if (_rank == 0)
        printf("Number of processors %d\n",_size);
    printf("Start on processor %d\n",_rank);

    clock_t tic = 0, toc = 0;

    if (_rank == 0) tic = clock();

    int  nk = 0, nt = 0, nc = 0, nv = 0, ns = 0;
    char fileconf[256], filecent[256], fileasgn[256];
    FILE *fini = fopen("input","r");
    fscanf(fini,"%d%d%d%d%d%s%s%s",&nk,&nt,&nc,&nv,&ns,fileconf,filecent,fileasgn);
    fclose(fini);

    double **data = new_dmat(nt,nv);
    int *assignment = new_ivec(nt);
    int *cents = new_ivec(nk);
    int *assignment_bak = new_ivec(nt);
    int *cents_bak = new_ivec(nk);

    FILE *fconf = fopen(fileconf,"r");
    double dtmp = 0;
    for (int i=0; i<nt; ++i) {
    for (int c=0; c<nc; ++c) {
        fscanf(fconf,"%lf",&dtmp);
        if (c < nv) data[i][c] = dtmp;
    }
    }
    fclose(fconf);

    double minsumdist = 1.e60;
    while (ns--) {
        printf("sample count down: %d\n", ns);
        double sumdist = kmeans (1,nk,nt,nv,data,cents,assignment);
    //  double sumdist = kcenter (nk,nt,nv,data,cents,assignment);
        if (sumdist < minsumdist) {
            memcpy(cents_bak,cents,nk*sizeof(int));
            memcpy(assignment_bak,assignment,nt*sizeof(int));
        }
    }

#ifdef _MPI

    MPI_Barrier(MPI_COMM_WORLD);

    int minsumrank = 0;
    struct {double dist; int rank;} in_dist_rank, out_dist_rank;
    in_dist_rank.dist = minsumdist;
    in_dist_rank.rank = _rank;

    MPI_Reduce(&in_dist_rank, &out_dist_rank, 1, MPI_DOUBLE_INT, MPI_MINLOC, 0, MPI_COMM_WORLD); 
    if (_rank == 0) { 
        minsumdist = out_dist_rank.dist;
        minsumrank = out_dist_rank.rank; 
    } 

    MPI_Bcast(&minsumrank, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // printf("rank=%d, minsumrank=%d\n",_rank,minsumrank);
    if (minsumrank == _rank) {
        save_ivec(filecent,nk,cents_bak);
        save_ivec(fileasgn,nt,assignment_bak);
    }
#else
    save_ivec(filecent,nk,cents_bak);
    save_ivec(fileasgn,nt,assignment_bak);
#endif

    del_ivec(cents_bak);
    del_ivec(assignment_bak);
    del_ivec(cents);
    del_ivec(assignment);
    del_dmat(data);

    if (_rank == 0) {
        toc = clock();
        printf("cputime: %16.6e seconds\n",(double)(toc-tic)/CLOCKS_PER_SEC);
    }

#ifdef _MPI
    MPI_Finalize();
#endif

    return 0;
}
