#ifndef POLADJUST_H
#define POLADJUST_H
#include "../intervals/intervalar.h"
#include "../system/system.h"
#include "../utils/utils.h"

/*
 * Will generate a matrix of intervals where each point is a sum of x^(i*j)
 * and each independent term is a sum of y*x^(i)
 * @param table: table of points
 * @param k: degree of the polynomial
 * @param n: number of points
 * @return: matrix of intervals of size k+1
 */
IntervalMatrix_t *leastSquareMethod(IntervalPoint_t *table, int k, int n);

/*
 * Will generate an array of N IntervalPoints_t
 * @param n: number of points
 * @return: array of IntervalPoints_t
 */
IntervalPoint_t *read_points(int n);

#endif // POLADJUST_H