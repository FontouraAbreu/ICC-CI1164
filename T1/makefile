CFLAGS= -g -Wall -O3 -mavx -march=native
CC=gcc

all: ajustePol

# regras de ligacao
ajustePol: main.o ajustePol.o utils.o floatType.o
	$(CC) $(CFLAGS) main.o ajustePol.o utils.o floatType.o -lm -o ajustePol

# regras de compilacao
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

ajustePol.o: PolinomialAdjust/adjust.c PolinomialAdjust/adjust.h
	$(CC) $(CFLAGS) -c PolinomialAdjust/adjust.c -o ajustePol.o

utils.o: utils/utils.c utils/utils.h
	$(CC) $(CFLAGS) -c utils/utils.c -o utils.o

floatType.o: floatType/floatType.c floatType/floatType.h
	$(CC) $(CFLAGS) -c floatType/floatType.c -o floatType.o
	
run: ajustePol
	./ajustePol

clean:
	rm -f *.o ajustePol

purge: clean
	rm -f ajustePol