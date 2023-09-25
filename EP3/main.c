#include "interpolators/interpola.h"
#include "utils/utils.h"

int main(int argc, char *argv[])
{
    int n;
    if (argc != 2)
    {
        fprintf(stderr, "O programa precisa de 1 argumento posicional 'x' que será aproximado\n");
        return 1;
    }

    if (scanf("%d", &n) != 1)
    {
        fprintf(stderr, "Erro ao ler n\n");
        return 1;
    }

    double x = strtod(argv[1], NULL);

    point_t *table = read_points(n);
    if (x < table[0].x || x > table[n - 1].x)
    {
        fprintf(stderr, "x fora do intervalo de pontos\n");
        return 1;
    }

    double tempo1, tempo2;

    tempo1 = timestamp();
    double Lx = lagrange_method(table, n, x);
    printf("\nP_%d(%1.8e)_L = %1.8e\n", n - 1, x, Lx);
    tempo1 = timestamp() - tempo1;

    tempo2 = timestamp();
    double Nx = newton_method(table, n, x);
    printf("P_%d(%1.8e)_N = %1.8e\n", n - 1, x, Nx);
    tempo2 = timestamp() - tempo2;

    printf("%1.8e\n", tempo1);
    printf("%1.8e\n", tempo2);
    return 0;
}