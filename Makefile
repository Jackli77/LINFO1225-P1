CFlags = -std=c99 -g -Wall -Werror
CC = gcc
philo: philo.c
	$(CC) $(CFlags) -o philo.o philo.c -lm -lpthread

prodcons: prodcons.c
	$(CC) $(CFlags) -o prodcons.o prodcons.c -lm -lpthread

all: philo.c prodcons.c
	make philo
	make prodcons

clean:
	rm -f philo.o
	rm -f prodcons.o
