#include "utils/utils.h"
#include "PolinomialAdjust/adjust.h"
#include "system/system.h"
#include "likwid.h"

int main(int argc, char *argv[])
{
    LIKWID_MARKER_INIT;

    // reading inputs
    int n, k;
    double time1, time2;
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


    time1 = timestamp();
    LIKWID_MARKER_START("LEAST_SQUARE_METHOD");
    IntervalPoint_t *table = read_points(k);
    IntervalMatrix_t *coefficients_matrix = leastSquareMethod(table, k, n);
    LIKWID_MARKER_STOP("LEAST_SQUARE_METHOD");
    time1 = timestamp()- time1;

    time2 = timestamp();
    LIKWID_MARKER_START("SYSTEM_SOLVER");
    IntervalMatrix_t *triangular_matrix = partial_pivoting_system_solver(coefficients_matrix);
    Interval_t *solution = retrossubs(triangular_matrix);
    LIKWID_MARKER_STOP("SYSTEM_SOLVER");
    time2 = timestamp() - time2;

    Interval_t *residual = show_residual(coefficients_matrix, solution, table, k);

    // printing the solution
    for (int i = 0; i <= n; i++)
        printf("[%1.8e, %1.8e] ", solution[i].min.f, solution[i].max.f);
    printf("\n");
    // printing the residual
    for (int i = 0; i < k; i++)
        printf("[%1.8e, %1.8e] ", residual[i].min.f, residual[i].max.f);
    printf("\n");

    printf("%1.8e\n", time1);
    printf("%1.8e\n", time2);

    LIKWID_MARKER_CLOSE;
    return 0;
}