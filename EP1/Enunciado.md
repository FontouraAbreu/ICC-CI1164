# Enunciado

A Análise Intervalar pode ser usada para computar operações básicas de forma rigorosa. A ideia é representar valores reais por intervalos de comprimento mínimo que contêm esses valores, ao invés de utilizar aproximações. Deste modo, operações sobre esses números resultam em intervalos que carregam os erros numéricos de forma explícita.

Seja x um valor real qualquer. A representação intervalar de x é dada por X = [m(x), M(x)], onde m(x) é o maior número de máquina menor ou igual a x e M(x) é o menor número de máquina maior ou igual a x.

Seja X = [a,b] e Y = [c,d]. As operações básicas intervalares são dadas por:

X + Y = [a+c, b+d]

X - Y = [a-d, b-c]

X \* Y = [a,b] \* [c,d]  =  [min{a*c,a*d,b*c,b*d}, max{a*c,a*d,b*c,b*d}]

X / Y = [a,b] * [1/d,1/c], se 0 não pertence ao intervalo Y

Para simplificar, considere que se 0 (zero)  pertence a Y, então X / Y =[-inf,+inf], para qualquer intervalo X.

É importante notar que os limitantes dos intervalos resultantes devem ser representados na máquina de forma rigorosa. Assim, na prática:

X + Y = [ m(a+c), M(b+d) ]

X - Y = [ m(a-d), M(b-c) ]

E assim por diante...

## Tarefa

Faça um programa que leia uma expressão no seguinte formato:

X1 O1 X2 O2 X3 O3 X4 O4 X5

Onde cada Xi é um número real e cada Oi é um caractere indicando uma operação básica: +, -, * e /.

O seu programa deve calcular, de forma rigorosa (i.e, usando a representação por intervalos e operações definidas anteriormente), a seguinte expressão matemática:

(((X1 O1 X2) O2 X3) O3 X4) O4 X5

Seu programa também deve informar o resultado [a,b] de cada operação e a precisão considerando 3 critérios (ver exemplo de execução abaixo):

    Erro absoluto: b-a
    Erro relativo: (b-a)/a
    ULPs: quantidade de ULPs entre as representações de a e b

OBS. : Dado um valor de entrada x, há diversas formas de calcular o intervalo [m(x), M(x)]. As funcionalidades nextafter() e fesetround() da linguagem C podem ser úteis, além do código FloatType.c apresentado na aula. Diferentes abordagens podem gerar intervalos distintos, e todas elas serão consideradas válidas neste exercício, desde que garantam que o valor x esteja contido no intervalo [m(x), M(x)] e que m(x) e M(x) estejam poucos ULPs de distância de x.

## Exemplo de execução

(Dados de saída impressos com "%1.8e")

<b> Entrada: </b>

2.347e-40 * 0.001 + 1.1e+10 - 0.75e-39 / 0.0

<b> Saída: </b>

1:

    [2.34699276e-40,2.34700678e-40] * [9.99999932e-04,1.00000005e-03] = [2.34016844e-43,2.35418143e-43]
    EA: 1.40129847e-45; ER: 5.98802418e-03; ULPs: 0

2:

    [2.34016844e-43,2.35418143e-43] + [1.09999995e+10,1.10000006e+10] = [1.09999995e+10,1.10000016e+10]
    EA: 2.04800000e+03; ER: 1.86181837e-07; ULPs: 1

3:

    [1.09999995e+10,1.10000016e+10] - [7.49998761e-40,7.50000162e-40] = [1.09999985e+10,1.10000016e+10]
    EA: 3.07200000e+03; ER: 2.79272769e-07; ULPs: 2

4:

    [1.09999985e+10,1.10000016e+10] / [0.00000000e+00,0.00000000e+00] = [-inf,inf]
    EA: inf; ER: -nan; ULPs: -16777217

## O que deve ser entregue

Este exercício deve ser feito em duplas (preferencialmente, a dupla deve continuar a mesma para todos os demais EPs e Trabalhos práticos da disciplina). Apenas um dos alunos deve entregar os códigos-fonte do programa (em linguagem C), makefile e arquivos de teste usados, além de um arquivo LEIAME contendo os nomes dos alunos e limitações do programa (por exemplo, casos que o programa não funciona). Todos estes itens devem ser compactados em um arquivo do tipo .tar , .tgz ou .zip .
