CFLAGS= -g --debug -Wall -O3 -mavx -march=native
CC=gcc

all: ajustePol

# regras de ligacao
ajustePol: main.o ajustePol.o utils.o interval.o floatType.o system.o
	$(CC) $(CFLAGS) main.o ajustePol.o utils.o interval.o floatType.o system.o -lm -o ajustePol

# regras de compilacao
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

ajustePol.o: PolinomialAdjust/adjust.c PolinomialAdjust/adjust.h
	$(CC) $(CFLAGS) -c PolinomialAdjust/adjust.c -o ajustePol.o

utils.o: utils/utils.c utils/utils.h
	$(CC) $(CFLAGS) -c utils/utils.c -o utils.o

interval.o: intervals/intervalar.c intervals/intervalar.h
	$(CC) $(CFLAGS) -c intervals/intervalar.c -o interval.o

floatType.o: floatType/FloatType.c floatType/FloatType.h
	$(CC) $(CFLAGS) -c floatType/FloatType.c -o floatType.o

system.o: system/system.c system/system.h
	$(CC) $(CFLAGS) -c system/system.c -o system.o
	
run: ajustePol
	./ajustePol

clean:
	rm -f *.o ajustePol

purge: clean
	rm -f ajustePol