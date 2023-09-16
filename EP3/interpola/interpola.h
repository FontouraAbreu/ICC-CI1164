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

void lagrange_method(point_t *table, int n, double x);

#endif // INTERPOLA_H