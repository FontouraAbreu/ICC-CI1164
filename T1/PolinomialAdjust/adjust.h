#ifndef POLADJUST_H
#define POLADJUST_H
#include "../intervals/intervalar.h"
#include "../system/system.h"

/*
*   Point structure:
*   x: interval_t of x coordinate
*   y: interval_t of y coordinate
*   BETTER OF AS TWO ARRAYS OF INTERVALS
*/
typedef struct 
{
    Interval_t x;
    Interval_t y;
} IntervalPoint_t;


Interval_t *leastSquareMethod(IntervalPoint_t *table, int k, int n);

IntervalMatrix_t *createIntervalMatrix(int n);

IntervalPoint_t *read_points(int n);

#endif // POLADJUST_H