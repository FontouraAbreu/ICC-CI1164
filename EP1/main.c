#include "intervalar.h"

int main()
{
    char operations[4];
    Float_t floats[5];
    read_expression(operations, floats);
    print_expression(operations, floats);

    return 0;
}