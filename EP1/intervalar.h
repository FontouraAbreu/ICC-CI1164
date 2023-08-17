#ifndef INTERVALAR_H
#define INTERVALAR_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

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
    float *min;
    float *max;
} Interval_t;

Interval_t* generate_intervals(float * floats);

void copy_value(float *source, float *destination);

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
Interval_t select_operation(char operation, Interval_t X, Interval_t Y);

float absolute_error(Interval_t X, Interval_t Y);

float relative_error(Interval_t X, Interval_t Y);

uint8_t ulps_error(Interval_t X, Interval_t Y);


void read_expression(char *operations, float *floats);
void print_expression(char *operations, float *floats);

#endif