CFLAGS = -Wno-implicit-function-declaration -Wall -g

CC = gcc

all: main

main: main.o
	$(CC) $(CFLAGS) main.o -o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean: 
	rm main.o main
