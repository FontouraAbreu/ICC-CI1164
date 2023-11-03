#ifndef INTERVALAR_H
#define INTERVALAR_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "../utils/utils.h"

typedef long long int lli;


/*
Atributos
@param min;
@param max;


@brief
Seja x um valor real qualquer.
A representação intervalar de x é dada por X = [min(x), max(x)],
onde min(x) é o maior número de máquina menor ou igual a x
e max(x) é o menor número de máquina maior ou igual a x.
*/
typedef struct
{
    Float_t min;
    Float_t max;
} Interval_t;

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

/*
* Optimized version of IntervalPoint_t
* An array of x and y coordinates
* where x[i] is the x Interval_t of the i-th point
*/
typedef struct {
    Interval_t *x;
    Interval_t *y;
} OptIntervalPoint_t;

/*
    *   Interval Matrix structure:
    *   rows: number of rows
    *   cols: number of columns
    *   data: matrix of intervals
    *   independent_terms: independent terms of the system
    *   residual: residual of the system
*/
typedef struct
{
    lli rows;
    lli cols;
    Interval_t **data;
    Interval_t *independent_terms;
    Interval_t *residual;
} IntervalMatrix_t;

/*
* Optmized version of IntervalMatrix_t
* access the matrix as a single array
* data[i][j] = data[i * cols + j]
*/
typedef struct
{
    /* data */
    lli rows;
    lli cols;
    Interval_t *data;
    Interval_t *independent_terms;
    Interval_t *residual;
} OptIntervalMatrix_t;


// Seja X = [a,b] e Y = [c,d]. As operações básicas intervalares são dadas por:

/*
Seja X = [a,b] e Y = [c,d]
X + Y = [a+c, b+d]
*/
Interval_t op_sum_interval(Interval_t X, Interval_t Y);

/*
Seja X = [a,b] e Y = [c,d]
X - Y = [a-d, b-c]
*/
Interval_t op_sub_interval(Interval_t X, Interval_t Y);

/*
Seja X = [a,b] e Y = [c,d]
X * Y = [a,b] * [c,d]  =  [min{a*c,a*d,b*c,b*d}, max{a*c,a*d,b*c,b*d}]
*/
Interval_t op_mul_interval(Interval_t X, Interval_t Y);

/*
 *  Seja X = [a,b]
 *  X^p = [1,1] se p = 0
 *        [a^p,b^p] se p é impar
 *        [a^p,b^p] se p é par E a >= 0
 *        [b^p,a^p] se p é par E b < 0
 *        [0, max{a^p,b^p}] se p é par E a < 0 <= b
 *  @return: X^p (Interval_t)
 */
Interval_t op_pow_interval(Interval_t x, lli n);

/*
Seja X = [a,b] e Y = [c,d]
Will find min{a*c,a*d,b*c,b*d}
*/
double find_min(Interval_t X, Interval_t Y);

/*
Seja X = [a,b] e Y = [c,d]
Will find max{a*c,a*d,b*c,b*d}
*/
double find_max(Interval_t X, Interval_t Y);

/*
Seja X = [a,b] e Y = [c,d]
Will return 1 if X > Y, 0 otherwise
@return: 1 if X > Y, 0 otherwise
*/
lli greater_than(Interval_t X, Interval_t Y);

/*
Seja X = [a,b] e Y = [c,d]
X / Y = [a,b] * [1/d,1/c], se 0 não pertence ao intervalo Y
*/
Interval_t op_div_interval(Interval_t X, Interval_t Y);

// Auxiliar functions

/*
Will loop through the array of floats and generate the intervals for each one of them.

@param floats: the array of *Float_t to be converted to intervals
*/
Interval_t *generate_intervals(Float_t *floats);

/*
Will generate a single interval for a given Float_t.

@param number: the Float_t to be converted to an interval
*/
Interval_t generate_single_interval(Float_t *number);

IntervalMatrix_t *generate_interval_matrix(lli n, lli m);

void free_intervalMatrix(IntervalMatrix_t *matrix);
#endif