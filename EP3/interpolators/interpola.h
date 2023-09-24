#ifndef INTERPOLA_H
#define INTERPOLA_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../matrix/matrix.h"

typedef struct {
    double x;
    double y;
} point_t;


/*
* Will generate an aproximate function based on the table of points given using the newton interpolation method
* @param table: point*
* @param n: int
* @param x: double*
* @return g_x: the aproximated function
*/
double newton_method(point_t *table, int n, double x);

/*
* Will calculate the divided differences of the table of points given
* @param table: point_t *
* @param n: int
* @param x: double
* @return divided_differences: double **
*/
double **calculate_divided_differences(point_t *table, int n, double x);

/*
* Will generate an aproximate function based on the table of points given using the lagrange interpolation method
* @param table: point*
* @param n: int
* @param x: double*
* @return g_x: the aproximated function
*/
double lagrange_method(point_t *table, int n, double x);



/*
* Read from stdin a list of N points(point_t)
* @param n: int(the number of points to be read)
* @return x:  point_t *
*/
point_t *read_points(int n);

#endif // INTERPOLA_H