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

// void show_fe_current_rounding_direction(void)
// {
//     printf("current rounding direction:  ");
//     switch (fegetround()) {
//            case FE_TONEAREST:  printf ("FE_TONEAREST");  break;
//            case FE_DOWNWARD:   printf ("FE_DOWNWARD");   break;
//            case FE_UPWARD:     printf ("FE_UPWARD");     break;
//            case FE_TOWARDZERO: printf ("FE_TOWARDZERO"); break;
//            default:            printf ("unknown");
//     };
//     printf("\n");
// }

Interval_t *generate_intervals(Float_t *floats)
{
    Interval_t *intervals = malloc(sizeof(Interval_t) * 5);

    for (int i = 0; i < 5; i++)
    {
        printf("float: %1.12e\n", floats[i].f);
        double max = nextafterf(floats[i].f, INFINITY);
        printf("max: %1.12e\n", max);

        double min = nextafterf(floats[i].f, -INFINITY);
        printf("min: %1.12e\n", min);
        // intervals[i].min = nextafter(floats[i], -INFINITY);
        // intervals[i].min = nextafter(floats[i], INFINITY);

        printf("[%1.12e, %1.12e]\n", min, max);
    }

    return intervals;
}

// Interval_t select_operation(char operation, Interval_t X, Interval_t Y)
// {
//     Interval_t result;
//     switch (operation) {
//         case '+':
//             result = op_sum_interval(X, Y);
//             break;
//         case '-':
//             result = op_sub_interval(X, Y);
//             break;
//         case '*':
//             result = op_mul_interval(X, Y);
//             break;
//         case '/':
//             result = op_div_interval(X, Y);
//             break;
//         default:
//             printf("Invalid operation\n");
//             break;
//     }
//     return result;
// }

// void calculateResult(Interval_t *interv)

void print_expression(char *operations, Float_t *floats)
{
    printf("%1.12e %c %1.12e %c %1.12e %c %1.12e %c %1.12e\n", floats[0].f, operations[0], floats[1].f, operations[1], floats[2].f, operations[2], floats[3].f, operations[3], floats[4].f);

    return;
}

float read_float()
{
    float num;
    scanf("%f", &num);
    return num;
}
