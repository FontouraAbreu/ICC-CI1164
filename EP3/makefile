CFLAGS= -g -Wall -O3 -mavx -march=native
CC=gcc

all: interpola

# regras de ligacao
interpola: main.o interpola.o utils.o
	$(CC) $(CFLAGS) main.o interpola.o utils.o -lm -o interpola

# regras de compilacao
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

interpola.o: interpolators/interpola.c interpolators/interpola.h
	$(CC) $(CFLAGS) -c interpolators/interpola.c -o interpola.o

utils.o: utils/utils.c utils/utils.h
	$(CC) $(CFLAGS) -c utils/utils.c -o utils.o
	
run: interpola
	./interpola

clean:
	rm -f *.o interpola

purge: clean
	rm -f interpola