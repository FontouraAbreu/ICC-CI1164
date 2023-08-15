#include "main.h"
#include "intervalar.h"


int main()
{
    char operations[4];
    float floats[5];
    read_expression(operations, floats);
    print_expression(operations, floats);
    Interval_t interval = generate_interval(floats[0]);
    printf("[%f, %f]\n", *interval.min, *interval.max);
    // print_expression(operations, floats);

    return 0;
}
