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

void lagrange_method();

#endif // INTERPOLA_H