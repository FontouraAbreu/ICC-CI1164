#include "intervalar.h"

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
    return NULL;
}

void print_expression(char *operations, Float_t *floats)
{
    printf("%1.12e %c %1.12e %c %1.12e %c %1.12e %c %1.12e\n", floats[0].f, operations[0], floats[1].f, operations[1], floats[2].f, operations[2], floats[3].f, operations[3], floats[4].f);

    return;
}

Float_t absolute_error(Interval_t interval)
{
    Float_t result;

    result.f = fabs(interval.max.f - interval.min.f);

    return result;
}

Float_t relative_error(Interval_t interval)
{
    Float_t result;

    result.f = fabs(interval.max.f - interval.min.f) / fabs(interval.min.f);

    return result;
}

int how_many_ulps_between(Interval_t interval)
{
    int result;

    result = abs(interval.min.i - interval.max.i) - 1;

    if (result < 0)
    {
        return 0;
    }

    return result;
}

Interval_t op_sum_interval(Interval_t X, Interval_t Y)
{
    Interval_t result;

    result.min.f = X.min.f + Y.min.f;
    result.min.f = nextafterf(result.min.f, -INFINITY);
    result.max.f = X.max.f + Y.max.f;
    result.max.f = nextafterf(result.max.f, INFINITY);

    return result;
}

Interval_t op_sub_interval(Interval_t X, Interval_t Y)
{
    Interval_t result;

    result.min.f = X.min.f - Y.max.f;
    result.min.f = nextafterf(result.min.f, -INFINITY);
    result.max.f = X.max.f - Y.min.f;
    result.max.f = nextafterf(result.max.f, INFINITY);

    return result;
}

int zero_in_interval(Interval_t interval)
{
    Float_t zero;
    zero.f = 0.0;
    Interval_t intervalZero = generate_single_interval(&zero);
    if ((interval.min.f <= intervalZero.min.f && interval.max.f >= intervalZero.max.f) || (interval.min.f >= intervalZero.min.f && interval.max.f <= intervalZero.max.f))
    {
        return 1;
    }
    return 0;
}

Interval_t op_div_interval(Interval_t X, Interval_t Y)
{

    Interval_t result;

    // checking if 0.0 is in Y
    if (zero_in_interval(Y))
    {
        result.min.f = -INFINITY;
        result.max.f = INFINITY;

        return result;
    }
    result.min.f = 1.0f / Y.max.f;
    result.max.f = 1.0f / Y.min.f;

    result = op_mul_interval(X, result);

    return result;
}

Interval_t op_mul_interval(Interval_t X, Interval_t Y)
{
    Interval_t result;

    result.min.f = nextafterf(find_min(X, Y), -INFINITY);
    result.max.f = nextafterf(find_max(X, Y), INFINITY);

    return result;
}

Interval_t op_pow_interval(Interval_t x, int p)
{
    Interval_t y;
    int p_is_even = p % 2 == 0;
    if (p == 0)
    {
        y.min.f = 1.0;
        y.max.f = 1.0;
        return y;
    }
    else if (!p_is_even)
    {
        y.min.f = pow(x.min.f, p);
        y.min.f = nextafterf(y.min.f, -INFINITY);
        y.max.f = pow(x.max.f, p);
        y.max.f = nextafterf(y.max.f, INFINITY);
        return y;
    }
    else if ((p_is_even) && (x.min.f >= 0.0))
    {
        y.min.f = pow(x.min.f, p);
        y.min.f = nextafterf(y.min.f, -INFINITY);
        y.max.f = pow(x.max.f, p);
        y.max.f = nextafterf(y.max.f, INFINITY);
        return y;
    }
    else if (p_is_even && (x.max.f < 0.0))
    {
        y.min.f = pow(x.max.f, p);
        y.min.f = nextafterf(y.min.f, -INFINITY);
        y.max.f = pow(x.min.f, p);
        y.max.f = nextafterf(y.max.f, INFINITY);
        return y;
    }
    else if (p_is_even && (x.min.f < 0.0) && (x.max.f >= 0.0))
    {
        y.min.f = 0.0;
        y.max.f = fmax(pow(x.min.f, p), pow(x.max.f, p));
        y.max.f = nextafterf(y.max.f, INFINITY);
        return y;
    }

    return y;
}

float find_min(Interval_t X, Interval_t Y)
{
    Float_t min;

    Float_t a = X.min;
    Float_t b = X.max;
    Float_t c = Y.min;
    Float_t d = Y.max;

    float ac = a.f * c.f;
    float ad = a.f * d.f;
    float bc = b.f * c.f;
    float bd = b.f * d.f;

    min.f = ac;

    if (ad < min.f)
    {
        min.f = ad;
    }

    if (bc < min.f)
    {
        min.f = bc;
    }

    if (bd < min.f)
    {
        min.f = bd;
    }

    return min.f;
}

float find_max(Interval_t X, Interval_t Y)
{
    Float_t max;

    Float_t a = X.min;
    Float_t b = X.max;
    Float_t c = Y.min;
    Float_t d = Y.max;

    float ac = a.f * c.f;
    float ad = a.f * d.f;
    float bc = b.f * c.f;
    float bd = b.f * d.f;

    max.f = ac;

    if (ad > max.f)
    {
        max.f = ad;
    }

    if (bc > max.f)
    {
        max.f = bc;
    }

    if (bd > max.f)
    {
        max.f = bd;
    }

    return max.f;
}

int greater_than(Interval_t X, Interval_t Y)
{
    if (X.min.f > Y.min.f)
    {
        return 1;
    }
    return 0;
}

IntervalMatrix_t *generate_interval_matrix(int n, int m)
{
    IntervalMatrix_t *matrix = malloc(sizeof(IntervalMatrix_t));
    matrix->rows = n;
    matrix->cols = m;
    matrix->independent_terms = malloc(sizeof(Interval_t) * n);
    matrix->residual = malloc(sizeof(Interval_t) * n);
    matrix->data = malloc(sizeof(Interval_t *) * n);
    for (int i = 0; i < n; i++)
    {
        matrix->data[i] = malloc(sizeof(Interval_t) * m);
    }

    return matrix;
}

void free_intervalMatrix(IntervalMatrix_t *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix->independent_terms);
    free(matrix->residual);
    free(matrix);
}
