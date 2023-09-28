#ifndef INTERVALAR_H
#define INTERVALAR_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "../floatType/FloatType.h"

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
Seja X = [a,b] e Y = [c,d]
Will find min{a*c,a*d,b*c,b*d}
*/
float find_min(Interval_t X, Interval_t Y);

/*
Seja X = [a,b] e Y = [c,d]
Will find max{a*c,a*d,b*c,b*d}
*/
float find_max(Interval_t X, Interval_t Y);

/*
Seja X = [a,b] e Y = [c,d]
X / Y = [a,b] * [1/d,1/c], se 0 não pertence ao intervalo Y
*/
Interval_t op_div_interval(Interval_t X, Interval_t Y);

// Auxiliar functions

/*
This function is used to select the operation to be performed.

For example:
if char == '+', then select_operation = op_sum_interval
if char == '-', then select_operation = op_sub_interval
...

@param char: the operation to be performed. It can be [+,-,*,/]

*/
// float (*operation)(char);
Interval_t (*select_operation(char operation))(Interval_t, Interval_t);

Float_t absolute_error(Interval_t interval);

Float_t relative_error(Interval_t interval);

int how_many_ulps_between(Interval_t interval);

/*
This function will read from stdin the expression to be calculated.

the expression must be in this format:

X1 O1 X2 O2 X3 O3 X4 O4 X5

where Xi is an interval and Oi is an operation [+,-,*,/]

For example:

2.347e-40 * 0.001 + 1.1e+10 - 0.75e-39 / 0.0

@param expressions: a pointer to and array of chars that will store the expression
@param intervals: a pointer to an array of intervals that will store the intervals
*/
void read_expression(char *operations, Float_t *floats);
void print_expression(char *operations, Float_t *floats);

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

#endif