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
        printf("%d\n", i + 1);

        current_operation = select_operation(operations[i]);
        printf("[%1.8e,%1.8e] %c [%1.8e,%1.8e] = ", intervals[i].min.f, intervals[i].max.f, operations[i], intervals[i + 1].min.f, intervals[i + 1].max.f);

        current_result = current_operation(intervals[i], intervals[i + 1]);
        printf("[%1.8e,%1.8e]\n", current_result.min.f, current_result.max.f);

        printf("EA: %1.8e; ", absolute_error(current_result).f);
        printf("ER: %1.8e; ", relative_error(current_result).f);
        printf("ULPs: %d\n", how_many_ulps_between(current_result));

        intervals[i + 1] = current_result;

        printf("\n");
    }

    free(intervals);
    return 0;
}
