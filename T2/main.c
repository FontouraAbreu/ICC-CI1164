#include "utils/utils.h"
#include "PolinomialAdjust/adjust.h"
#include "system/system.h"
#ifdef LIKWID_PERFMON
#include "likwid.h"
#endif

int main(int argc, char *argv[])
{
#ifdef LIKWID_PERFMON
    LIKWID_MARKER_INIT;
#endif

    // reading inputs
    lli n, k;
    double timeLS_non_optmized, timeSS_non_optmized, timeLS_optmized, timeSS_optmized, timeResidual, timeResidual_optmized;
    if (scanf("%lld", &n) != 1)
    {
        fprintf(stderr, "Erro ao ler n\n");
        return 1;
    }

    if (scanf("%lld", &k) != 1)
    {
        fprintf(stderr, "Erro ao ler k\n");
        return 1;
    }

    // NON OPTMIZED VERSION
    timeLS_non_optmized = timestamp();
#ifdef LIKWID_PERFMON
    LIKWID_MARKER_START("LEAST_SQUARE_METHOD");
#endif
    IntervalPoint_t *table = read_points(k);
    IntervalMatrix_t *coefficients_matrix = leastSquareMethod(table, k, n);
#ifdef LIKWID_PERFMON
    LIKWID_MARKER_STOP("LEAST_SQUARE_METHOD");
#endif
    timeLS_non_optmized = timestamp() - timeLS_non_optmized;

    timeSS_non_optmized = timestamp();
#ifdef LIKWID_PERFMON
    LIKWID_MARKER_START("SYSTEM_SOLVER");
#endif
    IntervalMatrix_t *triangular_matrix = partial_pivoting_system_solver(coefficients_matrix);
    Interval_t *solution = retrossubs(triangular_matrix);
#ifdef LIKWID_PERFMON
    LIKWID_MARKER_STOP("SYSTEM_SOLVER");
#endif
    timeSS_non_optmized = timestamp() - timeSS_non_optmized;


    timeResidual = timestamp();
#ifdef LIKWID_PERFMON
    LIKWID_MARKER_START("RESIDUAL");
#endif
    Interval_t *residual = show_residual(coefficients_matrix, solution, table, k);
#ifdef LIKWID_PERFMON
    LIKWID_MARKER_STOP("RESIDUAL");
#endif
    timeResidual = timestamp() - timeResidual;

    // OPTMIZED VERSION
    timeLS_optmized = timestamp();
#ifdef LIKWID_PERFMON
    LIKWID_MARKER_START("LEAST_SQUARE_METHOD_OPTMIZED");
#endif
    OptIntervalPoint_t optTable = optRead_points(table, k);
    OptIntervalMatrix_t *optCoefficients_matrix = optLeastSquareMethod(optTable, k, n);
#ifdef LIKWID_PERFMON
    LIKWID_MARKER_STOP("LEAST_SQUARE_METHOD_OPTMIZED");
#endif
    timeLS_optmized = timestamp() - timeLS_optmized;

    timeSS_optmized = timestamp();
#ifdef LIKWID_PERFMON
    LIKWID_MARKER_START("SYSTEM_SOLVER_OPTMIZED");
#endif

    OptIntervalMatrix_t *optTriangular_matrix = optPartial_pivoting_system_solver(optCoefficients_matrix);
    Interval_t *optSolution = op_retrossubs(optTriangular_matrix);
#ifdef LIKWID_PERFMON
    LIKWID_MARKER_STOP("SYSTEM_SOLVER_OPTMIZED");
#endif
    timeSS_optmized = timestamp() - timeSS_optmized;

    timeResidual_optmized = timestamp();
#ifdef LIKWID_PERFMON
    LIKWID_MARKER_START("RESIDUAL_OPTMIZED");
#endif
    Interval_t *optResidual = op_show_residual(optCoefficients_matrix, optSolution, optTable, k);
#ifdef LIKWID_PERFMON
    LIKWID_MARKER_STOP("RESIDUAL_OPTMIZED");
#endif
    timeResidual_optmized = timestamp() - timeResidual_optmized;
    // avoiding compiling warnings
    if (optResidual && residual) {
        //do nothing
        
                
    }

    // printing results
    //printf("Least Square Method:\n");
    printf("%1.8e\n", timeLS_non_optmized);
    printf("%1.8e\n", timeLS_optmized);
    //printf("System Solver:\n");
    printf("%1.8e\n", timeSS_non_optmized);
    printf("%1.8e\n", timeSS_optmized);
    //printf("Residual:\n");
    printf("%1.8e\n", timeResidual);
    printf("%1.8e\n", timeResidual_optmized);

#ifdef LIKWID_PERFMON
    LIKWID_MARKER_CLOSE;
#endif
    return 0;
}