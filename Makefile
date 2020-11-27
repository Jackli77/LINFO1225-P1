CFlags = -std=gnu99 -g -Wall -Werror
CC = gcc
philo: philo.c
	$(CC) $(CFlags) -o philo philo.c -lm -lpthread
myphilo: myphilo.c
	$(CC) $(CFlags) -o myphilo myphilo.c -lm -lpthread

prodcons: prodcons.c
	$(CC) $(CFlags) -o prodcons prodcons.c -lm -lpthread

read: lect_read.c
	$(CC) $(CFlags) -o read lect_read.c -lm -lpthread
myread : mylect_read.c
	$(CC) $(CFlags) -o read mylect_read.c -lm -lpthread

tatas: tatas.c
	$(CC) $(CFlags) -o tatas tatas.c -lm -lpthread

all: philo.c prodcons.c
	make philo
	make prodcons
	make read
	make myphilo
	make myread
	make tatas

clean:
	rm -f *.o
	rm -f prodcons
	rm -f philo
	rm -f myphilo
	rm -f myread
	rm -f read
	rm -f tatas
