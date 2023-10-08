# Relatório EP2

## Alunos

Inaiê Moscal Zambonin - GRR20210578

Vinicius Fontoura de Abreu - GRR20206873

***

## Organização e Implementações

### Organização

Para a implementação desse trabalho utilizamos 3 bibliotecas:

- matrix.h: Contendo as funções que lidam com criação, print, desalocação e cópia de matrizes. Além disso, contém a função que faz a troca de duas linhas da matriz. Além disso contém a estrutura de dados `matrix_t` que é usada ao longo do trabalho, ela tem a seguinte estrutura:

```c
typedef struct matrix
{
    int size;                  // matrix size
    double **data;             // pointer to an array of *double
    double *independent_terms; // pointer to an array of double
    double *residual;           // residual of the matrix
} matrix_t;
```

- system.h: Contendo as funções que lidam com a resolução de sistemas lineares, calculo de resíduo e encontrar o pivo de uma coluna.

- utils.h: Provida pelo professor, contém funções que geram o timestamp.

Além disso, criamos um arquivo main.c que contém a função main e faz chamada das funções das bibliotecas acima.

### Implementações

Vamos falar sobre a implementação das 3 funções principais do trabalho: `partial_pivot_system_solver`, `partial_pivot_system_solver_no_multiplier` e `alternative_system_solver`:

#### partial_pivot_system_solver

Soluciona o sistema usando a técnica de pivoteamento parcial e o multiplicador para zerar os elementos abaixo do pivo.

A função implementada é:

```c
matrix_t *partial_pivoting_system_solver(matrix_t *A)
{
    // copying the matrix A to a new matrix x
    matrix_t *x = copy_matrix(A);
    int n = x->size;
    // for each row
    for (int i = 0; i < n; i++)
    {
        // find the pivot
        int pivot = find_partial_pivot(x, i, i);
        // swap rows if necessary
        if (pivot != i)
            swap_rows(x, i, pivot);

        // for each column
        for (int j = i + 1; j < n; j++)
        {
            // calculate the multiplier
            double m = x->data[j][i] / x->data[i][i];
            x->data[j][i] = 0.0;
            // for each element in the row
            for (int k = i + 1; k < n; k++)
                // calculate the new value
                x->data[j][k] -= m * x->data[i][k];
            // calculate the new independent term
            x->independent_terms[j] -= m * x->independent_terms[i];
        }
    }

    return x;
}
```

Para a função que encontra um pivô: uma melhor opção, quando se trata de precisão, seria utilizar o pivoteamento total(procurando pelo maior elemento em toda a matriz e não só na coluna), entretanto perderiamos performance.

#### partial_pivot_system_solver_no_multiplier

Soluciona o sistema usando a técnica de pivoteamento parcial e sem o multiplicador para zerar os elementos abaixo do pivo.

A função implementada é:

```c
matrix_t *partial_pivoting_system_solver_no_multiplier(matrix_t *A)
{
    // copying the matrix A to a new matrix x
    matrix_t *x = copy_matrix(A);
    int n = x->size;
    // for each row
    for (int i = 0; i < n; i++)
    {
        // find the pivot
        int pivot = find_partial_pivot(x, i, i);
        // swap rows if necessary
        if (pivot != i)
            swap_rows(x, i, pivot);

        // for each column
        for (int j = i + 1; j < n; j++)
        {
            // for each element in the row
            for (int k = i + 1; k < n; k++)
                // calculate the new value
                x->data[j][k] = x->data[j][k] * x->data[i][i] - x->data[i][k] * x->data[j][i];
            // calculate the new independent term
            x->independent_terms[j] = x->independent_terms[j] * x->data[i][i] - x->independent_terms[i] * x->data[j][i];
        }
    }

    return x;
}
```

A escolha de não utilizar o multiplicador gera resíduos menores, deixando assim os resultados mais estáveis. Entretanto algumas operações com Ponto Flutuante a mais são necessárias para se chegar ao resultado.

#### alternative_system_solver

Soluciona o sistema usando a técnica alternativa descrita no enunciado do trabalho.

A função implementada é:

```c
matrix_t *alternative_system_solver(matrix_t *A)
{
    matrix_t *x = copy_matrix(A);
    int n = x->size;

    // for each row
    for (int i = 0; i < n; i++)
    {
        // for each column
        for (int j = i; j < n; j++)
        {
            // divide every element in the row by the pivot
            double divider = x->data[i][i];
            for (int k = i; k < n; k++)
                x->data[i][k] /= divider;
            x->independent_terms[i] /= divider;
        }
        // loop through the next rows
        // and use the multiplier of that row to update it
        for (int k = i + 1; k < n; k++)
        {
            double m = x->data[k][i];
            for (int l = i; l < n; l++)
                x->data[k][l] -= m * x->data[i][l];
            x->independent_terms[k] -= m * x->independent_terms[i];
        }
    }
    return x;
}
```

A princípio, essa técnica parece ser a mais simples de ser implementada, entretanto, ela gera resíduos maiores que as outras técnicas, deixando assim os resultados menos estáveis.

#### Calculo do Resíduo

Para o calculo do resíduo, utilizamos a seguinte função:

```c
void show_residual(matrix_t *A, double *results) {
    int n = A->size;
    double *b = A->independent_terms;
    // r = Ax - b
    double *r = malloc(sizeof(double) * n);
    double *Ax = malloc(sizeof(double) * n);
    double *residual = malloc(sizeof(double) * n);
    // for each row
    for (int i = 0; i < n; i++)
    {
        double sum = 0.0;
        // for each column
        for (int j = 0; j < n; j++)
            // calculate the sum of the products
            sum += A->data[i][j] * results[j];
        // calculate the value of Ax
        Ax[i] = sum;
        // calculate the value of r
        r[i] =Ax[i] - b[i];
        // calculate the value of the residual
        residual[i] = fabs(r[i] / b[i]);
    }

    printf("residual vector:\n");
    for (int i = 0; i < n; i++)
        printf("%1.8e\n", residual[i]);
}
```

Preferimos gerar os vetores intermediários `Ax` e `r` para facilitar o entendimento do código.
Além de permitir o uso desses vetores para outros fins nos próximos trabalhos.

***

## Resultados

Alguns dos sistemas de teste gerados pelo professor tiveram resultados inesperados, vamos falar sobre eles:

### Sistema 2

O segundo sistema:

```text
4
 0 -1  4 -1 1
-1  4 -1  0 6
 4 -1  0 -1 3
-1  0 -1  4 12
```

resultou na matriz:

```text
-nan -nan -nan -nan 	| -nan
-nan -nan -nan -nan 	| -nan
-nan -nan -nan -nan 	| -nan
-nan -nan -nan -nan 	| -nan
```

Apenas para o método alternativo. Equanto isso, os outros dois métodos geraram resultados numéricos esperados.

Acreditamos que isso tenha acontecido devido aos zeros na diagonal principal da matriz, que fazem com que a divisão por zero aconteça.

### Sistema 7 e 13

O sétimo e décimo-terceiro sistemas:

```text
3
5 1 1 6
3 4 1 13
3 3 6 0

3
5 1 1 5
3 4 1 6
3 3 6 0
```

Resultaram em soluções iguais para todos os métodos. Porém, para todos os métodos, o resíduo foi `nan` ou `inf` para a última linha. Acreditamos que isso tenha acontecido pois no calculo do resíduo também existem divisões e as matrizes tem um `zero` como termo independente.

### Sistema 23

O vigésimo-terceiro sistema:

```text
17
-3  0  0  1  3  0  0  0  0  0  0  0  0  0  0  0  0  0
-3  0 -1  0 -3  0  0  0  0  0  0  0  0  0  0  0  0  0
 0 -1  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0
 0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  10
 0  0  0 -1  0  0  0  1  0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0 -1  0  0  0  0  0  0  0  0  0  0  0
 0  0  0  0 -3 -1  0  0  3  1  0  0  0  0  0  0  0  0
 0  0  0  0  3  0  1  0  3  0  0  0  0  0  0  0  0  15
 0  0  0  0  0  0  0 -1 -3  0  0  1  3  0  0  0  0  0
 0  0  0  0  0  0  0  0 -3  0 -1  0 -3  0  0  0  0  0
 0  0  0  0  0  0  0  0  0 -1  0  0  0  1  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0 -1  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0  0  0  0  0 -1 -3  0  0
 0  0  0  0  0  0  0  0  0  0  0  0 -3 -1  0  0  1  0
 0  0  0  0  0  0  0  0  0  0  0  0  3  0  1  0  0  10
 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 -3 -1  0
```

Gera resultados numéricos apenas para o método de pivoteamento percial com multiplicador. Os outros dois métodos geram resultados `-nan`. Não soubemos identificar o motivo disso.

## Conclusão

A partir dos testes realizados, todos os métodos implementados geraram resultados numéricos esperados para a maioria dos sistemas. Entretanto, alguns sistemas geraram resultados inesperados, como o sistema 2, 7, 13 e 23. De toda forma, para todas as matrizes testadas, pelo menos um dos métodos gerou resultados numéricos esperados.

Acreditamos que o mais estável seja o método de pivoteamento que para todos os sistemas gerou resultados numéricos esperados.