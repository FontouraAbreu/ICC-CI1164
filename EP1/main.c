#include "main.h"
#include "intervalar.h"

int main()
{
    char operations[4];
    Float_t floats[5];
    read_expression(operations, floats);
    Interval_t *intervals = generate_intervals(floats);

    for (int i = 0; i < 4; i++)
    {
        }

    print_expression(operations, floats);

    free(intervals);
    return 0;
}
