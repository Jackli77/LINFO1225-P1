CFlags = -std=gnu99 -g -Wall -Werror
CC = gcc
philo: philo.c
	$(CC) $(CFlags) -o philo philo.c -lm -lpthread
myphilo: myphilo.c
	$(CC) $(CFlags) -o myphilo myphilo.c -lm -lpthread

prodcons: prodcons.c
	$(CC) $(CFlags) -o prodcons prodcons.c -lm -lpthread

myprodcons: myprodcons.c
	$(CC) $(CFlags) -o myprodcons myprodcons.c -lm -lpthread

read: lect_read.c
	$(CC) $(CFlags) -o read lect_read.c -lm -lpthread
myread : mylect_read.c
	$(CC) $(CFlags) -o myread mylect_read.c -lm -lpthread

tatas: tatas.c
	$(CC) $(CFlags) -o tatas tatas.c -lm -lpthread
tas: tas.c
	$(CC) $(CFlags) -o tas tas.c -lm -lpthread
test:
	make clean -s
	make all -s
	./script.sh
	python3 plot.py

all:
	make philo
	make prodcons
	make myprodcons
	make read
	make myphilo
	make myread
	make tatas
	make tas

clean:
	rm -f *.csv
	rm -f prodcons
	rm -f myprodcons
	rm -f philo
	rm -f myphilo
	rm -f myread
	rm -f read
	rm -f tatas
	rm -f tas

