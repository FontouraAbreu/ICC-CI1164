#ifndef INTERPOLA_H
#define INTERPOLA_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} point_t;

void newton_method();


/*
* Will generate an aproximate function based on the table of points given using the lagrange interpolation method
* @param table: point*
* @param n: int
* @param x: double*
* @return g_x: the aproximated function
*/
double *lagrange_method(point_t *table, int n, float x);

float calculate_numerator(point_t *table, int n, float x);

/*
* Read from stdin a list of N points(point_t)
* @param n: int(the number of points to be read)
* @return x:  point_t *
*/
point_t *read_points(int n);

#endif // INTERPOLA_H