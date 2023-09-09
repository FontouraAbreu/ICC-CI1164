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