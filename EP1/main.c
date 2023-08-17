#include "main.h"
#include "intervalar.h"


int main()
{
    char operations[4];
    Float_t floats[5];
    read_expression(operations, floats);
    print_expression(operations, floats);
    Interval_t *interval = generate_intervals(floats);
    // printf("[%1.8e, %1.8e]\n", *interval->min, *interval->max);
    print_expression(operations, floats);

    free(interval);
    return 0;
}
