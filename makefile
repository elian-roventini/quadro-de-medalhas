main: main.o lista.o
	gcc -o main main.o lista.o
main.o: main.c lista.h
	gcc -c main.c
lista.o: lista.c heapsort.c lista.h
	gcc -c lista.c