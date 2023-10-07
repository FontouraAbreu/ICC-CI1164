# Relatório T1

Trabalho sobre a implementação do método dos mínimos quadrados utilizando representação intervalar.

## Alunos

Inaiê Moscal Zambonin - GRR20210578

Vinicius Fontoura de Abreu - GRR20206873

***

## Organização e implementações

Vamos falar sobre a organização de código e implementações de cada um dos métodos utilizados no T1.

### Organização

Foram criadas **4 bibliotecas** para a implementação do T1, sendo elas:

- `intervalar.h`: Biblioteca que contém a estrutura de dados `Interval_t`, `IntervalPoint_t` e `IntervalMatrix_t` e as funções que operam sobre elas.

- `system.h`: Biblioteca que contém as funções que **resolvem sistemas lineares**, utilizando o **método de gauss com pivoteamento parcial**.

- `utils.h`: Biblioteca que contém a estrutura de dados `Float_t` para a **representação de números de ponto flutuante** e funções auxiliares providas pelo professor.

- `adjust.h`: Biblioteca que contém as funções que **leem os pontos de entrada** e **geram a matriz de coeficientes** utilizando o **método dos mínimos quadrados**.

### Implementações

#### Alteração nas estruturas de dados

As 3 primeiras bibliotecas citadas acima, são as mesmas utilizadas no trabalho anterior(EP3), com a adaptação para a representação intervalar. Onde a estrutura de dados `IntervalMatrix_t` foi criada para representar matrizes de intervalos.

```c
typedef struct
{
    int rows;
    int cols;
    Interval_t **data;
    Interval_t *independent_terms;
    Interval_t *residual;
} IntervalMatrix_t;
```

#### Leitura dos pontos de entrada

A função `read_points` foi alterada para ler os pontos de entrada e armazená-los em uma matriz de intervalos.

A estrutura de dados `IntervalPoint_t` foi criada para representar um ponto de entrada.

```c
typedef struct
{
    Interval_t x;
    Interval_t y;
} IntervalPoint_t;
```

Pretendemos alterá-la para uma estrutura de arrays, para o T2, buscando uma melhor performance.

#### Método dos mínimos quadrados

A função `leastSquareMethod` foi criada para gerar a matriz de coeficientes utilizando o método dos mínimos quadrados.

```c
IntervalMatrix_t *leastSquareMethod(IntervalPoint_t *table, int k, int n)
{
    // Allocate memory for matrices A
    IntervalMatrix_t *A = generate_interval_matrix(n + 1, n + 1);
    Interval_t zero_interval, sum;
    zero_interval.min.f = 0.0;
    zero_interval.max.f = 0.0;

    // Fill in entries of matrices A
    for (int i = 0; i <= n; i++)
    {
        // fill in entries of matrix A (sum of x^(i+j))
        for (int j = 0; j <= n; j++)
        {
            sum = zero_interval;
            // A->data[i][j] = sum of x^(i+j)
            for (int l = 0; l < k; l++)
                sum = op_sum_interval(sum, op_pow_interval(table[l].x, i + j));
            A->data[i][j] = sum;
        }

        // fill in independent terms of matrix A (sum of y*x^i)
        sum = zero_interval;
        for (int j = 0; j < k; j++)
        {
            sum = op_sum_interval(sum, op_mul_interval(table[j].y, op_pow_interval(table[j].x, i)));
        }
        A->independent_terms[i] = sum;
    }

    return A;
}
```

Pretendemos otimizar o calculo das potências, utilizando uma lookup table e utilizando a simetria da matriz de coeficientes.

#### Outras implementações

As outras implementações foram as mesmas do EP3, com a adaptação para a representação intervalar.

## Pretenções de otimização

- Utilizar apenas um array de uma dimensão para representar uma matriz, utilizando o método de acesso `A[i][j] = A[i * cols + j]`.

- Utilizar uma lookup table para o cálculo das potências.

- Utilizar a simetria da matriz de coeficientes para otimizar o cálculo das potências.

Com certeza, existem outras formas de otimizar o código, mas essas são as que pensamos até o momento.

## Execução

Para executar o programa, basta executar o comando `make` na pasta raiz do projeto. O programa será compilado. Para executá-lo, basta executar o comando `./ajustePol`.

### Likwid

Para executar o programa com o likwid, basta executar o comando `python3 likwid.py ./ajustePol` na pasta raiz do projeto.

O script irá executar o programa com o likwid e mostrar os resultados para os grupos de eventos `ENERGY` e `FLOPS_DP`.

## Testes

Fizemos os testes providos pelo professor, para verificar se o programa estava funcionando corretamente. Além disso, fizemos alguns testes mais extremos com os seguintes pontos de entrada:

```text
6
31
0.20962329513800415 0.32103559371896706
0.6131323049810377 0.918137740789918
0.608165303013919 0.3098551247951381
0.3735144949408742 0.4548301839521741
0.744978287554653 0.5161088667814487
0.2582598106672772 0.35092922573611174
0.7823612937406137 0.3106468223607546
0.11443269972721537 0.049570856184998235
0.12836790854071978 0.5063847929413453
0.2461150046685171 0.7591740656941147
0.28131852326978235 0.6772607153105762
0.5379334091972491 0.3616151068643507
0.8442234533998361 0.5883162262791657
0.8240739758144261 0.40847491477480136
0.7898180101336502 0.887689263795403
0.08296630771324365 0.16828505117083914
0.5630478390400733 0.8391377981002687
0.8400192971622874 0.7732844512807029
0.6242640939414611 0.9805765245479552
0.32237585504028 0.27191484500233154
0.6076066893873581 0.014321653911738674
0.673042349498256 0.5065083865635649
0.15417585790921273 0.28166969592022917
0.6193730573057138 0.2581075257443316
0.7357504878299498 0.9859846247208713
0.3248663754127571 0.4118135819309694
0.011624436850523168 0.6306553742349383
0.19003920951009623 0.06111694039415905
0.8842374268463261 0.30318468211109706
0.7264739218040499 0.341246854393085
0.25681333796958283 0.7619842605580063
```

e outro teste com 1000 pontos de entrada, o qual não iremos colocar aqui, pois é muito grande.

## Conclusão

Dado que nos testes feitos, o resíduo foi mínimo, com no máximo 1 ordem de grandeza a mais que o erro de arredondamento, podemos concluir que o programa está funcionando corretamente.
