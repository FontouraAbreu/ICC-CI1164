#include "utils/utils.h"
#include "PolinomialAdjust/adjust.h"
#include "system/system.h"
#include "likwid.h"

int main(int argc, char *argv[])
{
    LIKWID_MARKER_INIT;

    // reading inputs
    lli n, k;
    double timeLS_non_optmized, timeSS_non_optmized, timeLS_optmized, timeSS_optmized;
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


    timeLS_non_optmized = timestamp();
    LIKWID_MARKER_START("LEAST_SQUARE_METHOD");
    IntervalPoint_t *table = read_points(k);
    IntervalMatrix_t *coefficients_matrix = leastSquareMethod(table, k, n);
    LIKWID_MARKER_STOP("LEAST_SQUARE_METHOD");
    timeLS_non_optmized = timestamp()- timeLS_non_optmized;

    timeLS_optmized = timestamp();
    LIKWID_MARKER_START("LEAST_SQUARE_METHOD_OPTMIZED");
    OptIntervalPoint_t optTable = optRead_points(k);
    OptIntervalMatrix_t *optCoefficients_matrix = optLeastSquareMethod(optTable, k, n);
    LIKWID_MARKER_STOP("LEAST_SQUARE_METHOD_OPTMIZED");
    timeLS_optmized = timestamp() - timeLS_optmized;

    timeSS_non_optmized = timestamp();
    LIKWID_MARKER_START("SYSTEM_SOLVER");
    IntervalMatrix_t *triangular_matrix = partial_pivoting_system_solver(coefficients_matrix);
    Interval_t *solution = retrossubs(triangular_matrix);
    LIKWID_MARKER_STOP("SYSTEM_SOLVER");
    timeSS_non_optmized = timestamp() - timeSS_non_optmized;

    Interval_t *residual = show_residual(coefficients_matrix, solution, table, k);

    // printing the solution
    for (int i = 0; i <= n; i++)
        printf("[%1.8e, %1.8e] ", solution[i].min.f, solution[i].max.f);
    printf("\n");
    // printing the residual
    for (int i = 0; i < k; i++)
        printf("[%1.8e, %1.8e] ", residual[i].min.f, residual[i].max.f);
    printf("\n");

    printf("%1.8e\n", timeLS_non_optmized);
    printf("%1.8e\n", timeSS_non_optmized);

    LIKWID_MARKER_CLOSE;
    return 0;
}