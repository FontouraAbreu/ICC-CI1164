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
    scanf("%f %c %f %c %f %c %f %c %f", &floats[0].f, &operations[0], &floats[1].f, &operations[1], &floats[2].f, &operations[2], &floats[3].f, &operations[3], &floats[4].f);

    return;
}

Interval_t *generate_intervals(Float_t *floats)
{
    Interval_t *intervals = malloc(sizeof(Interval_t) * 5);

    for (int i = 0; i < 5; i++)
    {

        intervals[i] = generate_single_interval(&floats[i]);
    }

    return intervals;
}

Interval_t generate_single_interval(Float_t *number)
{
    Interval_t interval;

    interval.min.f = nextafterf(number->f, -INFINITY);
    interval.max.f = nextafterf(number->f, INFINITY);

    return interval;
}

Interval_t (*select_operation(char operation))(Interval_t, Interval_t)
{
    switch (operation)
    {
    case '+':
        return op_sum_interval;
        break;
    case '-':
        return op_sub_interval;
        break;
    case '*':
        return op_mul_interval;
        break;
    case '/':
        return op_div_interval;
        break;
    default:
        printf("Invalid operation\n");
        break;
    }
}

void print_expression(char *operations, Float_t *floats)
{
    printf("%1.12e %c %1.12e %c %1.12e %c %1.12e %c %1.12e\n", floats[0].f, operations[0], floats[1].f, operations[1], floats[2].f, operations[2], floats[3].f, operations[3], floats[4].f);

    return;
}

Interval_t op_sum_interval(Interval_t X, Interval_t Y)
{
    printf("[%1.8e, %1.8e] + [%1.8e, %1.8e] = ", X.min.f, X.max.f, Y.min.f, Y.max.f);

    Interval_t result;

    printf("\n");
    return Y;
}

Interval_t op_sub_interval(Interval_t X, Interval_t Y)
{
    printf("[%1.8e, %1.8e] - [%1.8e, %1.8e] = ", X.min.f, X.max.f, Y.min.f, Y.max.f);

    Interval_t result;
    printf("\n");

    return Y;
}

Interval_t op_div_interval(Interval_t X, Interval_t Y)
{
    printf("[%1.8e, %1.8e] / [%1.8e, %1.8e] = ", X.min.f, X.max.f, Y.min.f, Y.max.f);

    Interval_t result;
    printf("\n");

    return Y;
}

Interval_t op_mul_interval(Interval_t X, Interval_t Y)
{
    printf("[%1.8e, %1.8e] * [%1.8e, %1.8e] = ", X.min.f, X.max.f, Y.min.f, Y.max.f);

    Interval_t result;
    printf("\n");

    return Y;
}