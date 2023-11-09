#ifndef POLADJUST_H
#define POLADJUST_H
#include "../intervals/intervalar.h"
#include "../system/system.h"
#include "../utils/utils.h"

// alias for long long int
typedef long long int lli;

/*
* Look up table for powers of x
*/
typedef struct {
    Interval_t *powers;
    lli size;
} PowerLookupTable_t;
/*
 * Will generate a matrix of intervals where each point is a sum of x^(i*j)
 * and each independent term is a sum of y*x^(i)
 * @param table: table of points
 * @param k: degree of the polynomial
 * @param n: number of points
 * @return: matrix of intervals of size k+1
 */
IntervalMatrix_t *leastSquareMethod(IntervalPoint_t *table, lli k, lli n);


/*
 * [OPTMIZED] Will generate a matrix of intervals where each point is a sum of x^(i*j)
 * and each independent term is a sum of y*x^(i) using a lookup table to avoid calculating the same power multiple times
 * @param table: table of points
 * @param k: degree of the polynomial
 * @param n: number of points
 * @return: matrix of intervals of size k+1
 */
OptIntervalMatrix_t *optLeastSquareMethod(OptIntervalPoint_t table, lli k, lli n);


/*
WIll calculate the lookup table for powers all k values of the table up to 2n-th-1 power
@param table: table of points
@param k: degree of the polynomial
@param n: number of points
@return: PowerLookupTable_t struct
*/
PowerLookupTable_t* calculatePowerLookupTable(OptIntervalPoint_t table, lli k ,lli n);

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

#endif // POLADJUST_H