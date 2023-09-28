#include "utils/utils.h"
#include "PolinomialAdjust/adjust.h"

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
    
    //printing points
    for (int i = 0; i < k; i++)
    {
        printf("x: [%1.8e, %1.8e]; y: [%1.8e, %1.8e]\n", table[i].x.min.f, table[i].x.max.f, table[i].y.min.f, table[i].y.max.f);
    }


    return 0;
}