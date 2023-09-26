#ifndef POLADJUST_H
#define POLADJUST_H
#include "../intervals/intervalar.h"

typedef struct
{
    double x;
    double y;
} point_t;

typedef struct
{
    int size;
    Interval_t **data;
    Interval_t *independent_terms;
    Interval_t *residual;
} IntervalMatrix_t;

double MinimumSquareMethod(point_t *table, int k, int n);

IntervalMatrix_t *createIntervalMatrix(int n);

#endif // POLADJUST_H