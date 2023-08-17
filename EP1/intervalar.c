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

void show_fe_current_rounding_direction(void)
{
    printf("current rounding direction:  ");
    switch (fegetround()) {
           case FE_TONEAREST:  printf ("FE_TONEAREST");  break;
           case FE_DOWNWARD:   printf ("FE_DOWNWARD");   break;
           case FE_UPWARD:     printf ("FE_UPWARD");     break;
           case FE_TOWARDZERO: printf ("FE_TOWARDZERO"); break;
           default:            printf ("unknown");
    };
    printf("\n");
}


Interval_t* generate_intervals(float * floats) {
    Interval_t *intervals = malloc(sizeof(Interval_t)*5);
    // show_fe_current_rounding_direction();

    for (int i = 0; i < 5; i++) {

        fesetround(FE_DOWNWARD);
        show_fe_current_rounding_direction();
        intervals[i].min = &floats[i];
        printf("%1.12e \n   ", floats[i]);

        fesetround(FE_UPWARD);

        show_fe_current_rounding_direction();
        intervals[i].max = &floats[i];
        // printf("%1.12e \n   ", floats[i]);

        printf("[%1.12e, %1.12e]\n", *intervals[i].min, *intervals[i].max);

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


void print_expression(char *operations, float *floats)
{
    printf("%1.12e %c %1.12e %c %1.12e %c %1.12e %c %1.12e\n", floats[0], operations[0], floats[1], operations[1], floats[2], operations[2], floats[3], operations[3], floats[4]);

    return;
}

float read_float()
{
    float num;
    scanf("%f", &num);
    return num;
}
