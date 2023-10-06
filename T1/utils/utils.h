#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

typedef union
{
    __int64_t i;
    double f;
    struct
    {                             // Bitfields for exploration (64 bits = sign|exponent|mantissa)
        __uint64_t mantissa : 52; // primeiros 52 bits (da direita para a esquerda)
        __uint32_t exponent : 11; // próximos 11 bits
        __uint32_t sign : 1;      // proximo bit (ou seja, o bit mais a esquerda)
    } parts;
} Float_t;

// Valor absoluto de um número. Alternativa ao uso da função 'fabs()'
#define ABS(num) ((num) < 0.0 ? -(num) : (num))

// real_t: tipo usado para representar valores em ponto flutuante
typedef double real_t;

// int_t: tipo usado para representar valores em inteiros
typedef __int64_t int_t;

// string_t: tipo usado para representar ponteiros para char/strings
typedef char *string_t;

// rtime_t: tipo usado para representar valores de tempo em ponto flutuante
typedef double rtime_t;

// Número máximo de dígitos em um número
#define numDigits(n) 6 // ( (int) log10(n) + 1 )

// Macro para verificar se valor 'n' é potência de 2 ou não
#define isPot2(n) (n && !(n & (n - 1)))

// Funções
rtime_t timestamp(void);
string_t markerName(string_t baseName, int n);

#endif // __UTILS_H__
