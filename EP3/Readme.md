# Relatório EP3

## Alunos

Inaiê Moscal Zambonin - GRR20210578

Vinicius Fontoura de Abreu - GRR20206873

***

## Organização e implementações

A implementação dos métodos de interpolação de Lagrange e Newton foram dividas em duas funções respectivamente, vamos falar sobre cada uma delas a seguir.

### Organização

Para facilitar a leitura do código e abstração, criamos a struct `point_t`:

```c
typedef struct {
    double x;
    double y;
} point_t;
```

Ela é usada para representar um valor `x` e um valor `y = f(x)` e será usada nos métodos de interpolação como um vetor de pontos.

#### Lagrange

A nossa implementação do método de Lagrange está na função `lagrange_method`:

```c
double lagrange_method(point_t *table, int n, double x)
{
    double result = 0.0;
    for (int i = 0; i < n; i++)
    {
        double term = table[i].y;
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                term *= (x - table[j].x) / (table[i].x - table[j].x);
            }
        }
        result += term;
    }
    return result;
}
```

Tentamos fazer a implementação em que o numerador é calculado apenas uma vez, porém tivemos dificuldades e optamos por deixá-lo de lado.

#### Newton

A nossa implementação do método de Newton está na função `newton_method`:

```c
double newton_method(point_t *table, int n, double x)
{
    double **divided_differences = calculate_divided_differences(table, n, x);

    // Calculate polynomial value
    double result = divided_differences[0][0];
    double term = 1.0;
    for (int j = 1; j < n; j++)
    {
        term *= (x - table[j - 1].x);
        result += divided_differences[j][j] * term;
    }

    // Free memory
    for (int i = 0; i < n; i++)
    {
        free(divided_differences[i]);
    }
    free(divided_differences);

    return result;
}
```

Optamos por não fazer a implementação do metodo de newton-gregory, visto que este é um caso particular do método de newton e provavelmente não cobrirá todos os casos de teste.

#### Cálculo das diferenças divididas

Para o cálculo das diferenças divididas, criamos a função `calculate_divided_differences`:

```c
double **calculate_divided_differences(point_t *table, int n, double x)
{
    double **divided_differences = malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
    {
        divided_differences[i] = malloc(n * sizeof(double));
    }

    for (int j = 0; j < n; j++)
    {
        for (int i = j; i < n; i++)
        {
            if (j == 0)
            {
                divided_differences[i][j] = table[i].y;
            }
            else
            {
                divided_differences[i][j] = (divided_differences[i][j - 1] - divided_differences[i - 1][j - 1]) / (table[i].x - table[i - j].x);
            }
        }
    }

    return divided_differences;
}
```

Optamos por não fazer a implementação do método de diferenças divididas recursivo, com o receio de que o método recursivo não fosse eficiente o suficiente para os casos de teste.

## Execução

Para executar o programa, existem duas opções:

1. executá-lo com os valores de entrada no terminal

```text
make all
./interpola <valor de x que será aproximado>
<valor N de pontos da tabela>
<valor x1 da tabela> <valor y1 da tabela>
<valor x2 da tabela> <valor y2 da tabela>
...
<valor xN da tabela> <valor yN da tabela>
```

2. executá-lo via script juntamente com o likwid

```text
chmod +x mflops.sh
./mflops.sh <valor de x que será aproximado>
```

O último irá mostrar a saída padrão do programa e a saída do likwid, que contém a quantidade de MFLOPS/s em média do programa.

## Testes

Buscamos testar o programa com diversos casos de teste na busca de resultados diferentes entre os dois métodos. Entretanto, não conseguimos encontrar nenhum caso em que os resultados fossem diferentes. Por isso, optamos por não colocar os casos de teste aqui.

## Conclusão

Ambos os métodos funcionam e não apresentaram nenhum erro durante nossos testes. O método de newton se demonstrou ser mais rápido cerca de 1ª ordem de grandeza para os casos de teste que usamos.