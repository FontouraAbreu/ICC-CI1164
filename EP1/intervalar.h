#ifndef INTERVALAR_H
#define INTERVALAR_H

#include "FloatType.h"

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
} Intervalo_t;

// Seja X = [a,b] e Y = [c,d]. As operações básicas intervalares são dadas por:

/*
Seja X = [a,b] e Y = [c,d]
X + Y = [a+c, b+d]
*/
Float_t op_sum_interval(Intervalo_t X, Intervalo_t Y);

/*
Seja X = [a,b] e Y = [c,d]
X - Y = [a-d, b-c]
*/
Float_t op_sub_interval(Intervalo_t X, Intervalo_t Y);

/*
Seja X = [a,b] e Y = [c,d]
X * Y = [a,b] * [c,d]  =  [min{a*c,a*d,b*c,b*d}, max{a*c,a*d,b*c,b*d}]
*/
Float_t op_mul_interval(Intervalo_t X, Intervalo_t Y);

/*
Seja X = [a,b] e Y = [c,d]
X / Y = [a,b] * [1/d,1/c], se 0 não pertence ao intervalo Y
*/
Float_t op_div_interval(Intervalo_t X, Intervalo_t Y);

// Auxiliar functions

/*
This function is used to select the operation to be performed.

For example:
if char == '+', then select_operation = op_sum_interval
if char == '-', then select_operation = op_sub_interval
...

@param char: the operation to be performed. It can be [+,-,*,/]

*/
Float_t (*select_operation)(char);

Float_t absolute_error(Intervalo_t X, Intervalo_t Y);

Float_t relative_error(Intervalo_t X, Intervalo_t Y);

uint ulps_error(Intervalo_t X, Intervalo_t Y);

#endif