#ifndef POLADJUST_H
#define POLADJUST_H
#include "../intervals/intervalar.h"
#include "../system/system.h"
#include "../utils/utils.h"

// alias for long long int
typedef long long int lli;


/*
 * Will generate a matrix of intervals where each point is a sum of x^(i*j)
 * and each independent term is a sum of y*x^(i)
 * @param k: degree of the polynomial
 * @param table: table of points
 * @param n: number of points
 * @return: matrix of intervals of size k+1
 */
IntervalMatrix_t *leastSquareMethod(IntervalPoint_t *table, lli k, lli n);


/*
 * [OPTMIZED] Will generate a matrix of intervals.
 * calculating only the first line and the last column.
 * Using the fact that the matrix is symmetrical and every value is a repetition of the first line or the last column.
 * @param table: table of points
 * @param k: degree of the polynomial
 * @param n: number of points
 * @return: matrix of intervals of size k+1
 */
OptIntervalMatrix_t *optLeastSquareMethod(OptIntervalPoint_t table, lli k, lli n);



/*
 * Will generate an array of N IntervalPoints_t
 * @param n: number of points
 * @return: array of IntervalPoints_t
 */
IntervalPoint_t *read_points(lli n);

/*
 * [OPTMIZED] Will fill a struct of arrays of intervals
 * @param n: number of points
 * @return: OptIntervalPoints_t struct
 */
OptIntervalPoint_t optRead_points(IntervalPoint_t *table ,lli n);

void print_matrix(IntervalMatrix_t *matrix);
void print_opt_matrix(OptIntervalMatrix_t *matrix);

#endif // POLADJUST_H