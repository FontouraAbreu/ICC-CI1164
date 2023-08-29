CFLAGS = -Wall -g -O1
CC = gcc
# regras de ligação
all: main

main: intervalar.o main.o
	$(CC) -o main intervalar.o main.o -lm

# regras de compilação
intervalar.o: intervalar.c intervalar.h 
	$(CC) $(CFLAGS) -c intervalar.c -o intervalar.o
	
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o




# regra para limpar os diretórios
run: main
	./main

clean:
	rm -f *.o main

purge: clean
	rm -f main

