#include "utils/utils.h"
#include "PolinomialAdjust/adjust.h"
#include "system/system.h"

int main(int argc, char *argv[])
{
    // reading inputs
    int n, k;

    if (scanf("%d", &n) != 1)
    {
        fprintf(stderr, "Erro ao ler n\n");
        return 1;
    }

    if (scanf("%d", &k) != 1)
    {
        fprintf(stderr, "Erro ao ler k\n");
        return 1;
    }

    IntervalPoint_t *table = read_points(k);
    IntervalMatrix_t *coefficients_matrix = leastSquareMethod(table, k, n);
    IntervalMatrix_t *triangular_matrix = partial_pivoting_system_solver(coefficients_matrix);
    Interval_t *solution = retrossubs(triangular_matrix);
    Interval_t *residual = show_residual(coefficients_matrix, solution, table, k);

    // printing the solution
    for (int i = 0; i <= n; i++)
        printf("[%1.8e, %1.8e] ", solution[i].min.f, solution[i].max.f);
    printf("\n");
    // printing the residual
    for (int i = 0; i < k; i++)
        printf("[%1.8e, %1.8e] ", residual[i].min.f, residual[i].max.f);
    printf("\n");

    return 0;
}