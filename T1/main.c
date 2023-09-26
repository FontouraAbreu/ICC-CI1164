#include "interpolators/interpola.h"
#include "utils/utils.h"
#include "PolinomialAdjust/adjust.h"

int main(int argc, char *argv[])
{
    // reading inputs
    int n, k;
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
    
    if (scanf("%d", &k) != 1)
    {
        fprintf(stderr, "Erro ao ler k\n");
        return 1;
    }


    point_t *table = read_points(&k);


    return 0;
}