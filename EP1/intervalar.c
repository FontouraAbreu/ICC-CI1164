#include "intervalar.h"
#include <fenv.h>

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
void read_expression(char *operations, float *floats)
{
    scanf("%f %c %f %c %f %c %f %c %f", &floats[0], &operations[0], &floats[1], &operations[1], &floats[2], &operations[2], &floats[3], &operations[3], &floats[4]);

    return;
}

Interval_t generate_interval(float x) {
    Interval_t interval;

    fesetround(FE_DOWNWARD);
    int current_direction = fegetround();

    interval.min = &x;
    fesetround(FE_UPWARD);
    current_direction = fegetround();
    interval.max = &x;
    
    return interval;
}


void print_expression(char *operations, float *floats)
{
    printf("%f %c %f %c %f %c %f %c %f\n", floats[0], operations[0], floats[1], operations[1], floats[2], operations[2], floats[3], operations[3], floats[4]);

    return;
}

float read_float()
{
    float num;
    scanf("%f", &num);
    return num;
}
