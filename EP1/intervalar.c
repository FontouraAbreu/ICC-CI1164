#include "intervalar.h"

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
void read_expression(char *operations, Float_t *floats)
{
    scanf("%e", floats[0]);
    for (int i = 0; i < 4; i++)
    {
        scanf("%c", operations[i]);
        scanf("%e", floats[i + 1]);
    }

    return;
}

void print_expression(char *operations, Float_t *floats)
{
    printf("%1.8e", floats[0]);
    for (int i = 0; i < 4; i++)
    {
        printf("%c", operations[i]);
        printf("%1.8e", floats[i + 1]);
    }

    return;
}

Float_t read_float_t()
{
    Float_t num;
    scanf("%f", &num.f);
    return num;
}

void main()
{
}