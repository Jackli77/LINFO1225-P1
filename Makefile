CFlags = -std=c99 -g -Wall -Werror
CC = gcc
philo: philo.c
	$(CC) $(CFlags) -o philo philo.c -lm -lpthread

prodcons: prodcons.c
	$(CC) $(CFlags) -o prodcons prodcons.c -lm -lpthread

all: philo.c prodcons.c
	make philo
	make prodcons

clean:
	rm -f *.xml
	rm -f fact
	rm -f test
