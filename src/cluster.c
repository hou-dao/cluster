#include <math.h>
#include "cluster.h"

double dist (int n, const double *x, const double *y) {
    double dist = 0;
    for (int i=0; i<n; ++i) {
        const double sub = x[i]-y[i];
        dist += sub*sub;
    }
    return sqrt(dist);
}

double dist2 (int n, const double *x, const double *y) {
    double dist = 0;
    for (int i=0; i<n; ++i) {
        const double sub = x[i]-y[i];
        dist += sub*sub;
    }
    return dist;
}
