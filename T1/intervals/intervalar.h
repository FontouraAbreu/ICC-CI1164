#ifndef INTERVALAR_H
#define INTERVALAR_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "../utils/utils.h"

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

typedef struct
{
    int rows;
    int cols;
    Interval_t **data;
    Interval_t *independent_terms;
    Interval_t *residual;
} IntervalMatrix_t;

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
Interval_t op_pow_interval(Interval_t x, int n);

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
int greater_than(Interval_t X, Interval_t Y);

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
Will loop through the array of floats and generate the intervals for each one of them.

@param floats: the array of *Float_t to be converted to intervals
*/
Interval_t *generate_intervals(Float_t *floats);

/*
Will generate a single interval for a given Float_t.

@param number: the Float_t to be converted to an interval
*/
Interval_t generate_single_interval(Float_t *number);

IntervalMatrix_t *generate_interval_matrix(int n, int m);

void free_intervalMatrix(IntervalMatrix_t *matrix);
#endif