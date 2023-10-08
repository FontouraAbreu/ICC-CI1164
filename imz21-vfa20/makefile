CFLAGS= -g -Wall -O3 -mavx -march=native
CC=gcc

all: perfEG

# regras de ligacao
perfEG: main.o matrix.o system.o utils.o
	$(CC) $(CFLAGS) matrix.o main.o system.o utils.o -lm -o perfEG

# regras de compilacao
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

system.o: system/system.c system/system.h
	$(CC) $(CFLAGS) -c system/system.c -o system.o

matrix.o: matrix/matrix.c matrix/matrix.h
	$(CC) $(CFLAGS) -c matrix/matrix.c -o matrix.o

utils.o: utils/utils.c utils/utils.h
	$(CC) $(CFLAGS) -c utils/utils.c -o utils.o


run: perfEG
	./perfEG

clean:
	rm -f *.o perfEG

purge: clean
	rm -f perfEG