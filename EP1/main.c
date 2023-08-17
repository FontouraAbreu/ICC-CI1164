#include "main.h"
#include "intervalar.h"

int main()
{
    char operations[4];
    Float_t floats[5];
    read_expression(operations, floats);

    Interval_t (*current_operation)(Interval_t, Interval_t);

    Interval_t *intervals = generate_intervals(floats);

    Interval_t current_result;

    // loop through the operations and store the resulting interval in current_result
    for (int i = 0; i < 4; i++)
    {
        current_operation = select_operation(operations[i]);
        printf("current_operation function pointer: %p\n", current_operation);
        current_result = current_operation(intervals[i], intervals[i + 1]);
        printf("\n");
    }

    print_expression(operations, floats);

    free(intervals);
    return 0;
}
