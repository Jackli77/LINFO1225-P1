CFlags = -std=gnu99 -g -Wall -Werror
CC = gcc
philo: philo.c
	$(CC) $(CFlags) -o philo philo.c -lm -lpthread

prodcons: prodcons.c
	$(CC) $(CFlags) -o prodcons prodcons.c -lm -lpthread
	
read: lect_read.c
	$(CC) $(CFlags) -o read lect_read.c -lm -lpthread

test: test.c
	$(CC) $(CFlags) -o test test.c -lm -lpthread

all: philo.c prodcons.c
	make philo
	make prodcons
	make read
	make test

clean:
	rm -f *.o
	rm -f *.csv
	rm -f prodcons
	rm -f philo
	rm -f read

