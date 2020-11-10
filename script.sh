#!/bin/bash
RUNS=5
NTHREAD=8
echo "nb_coeurs,temps"
for ((i=1; i<RUNS; i++))
do
    for((n=1; n<=NTHREAD; n++))
    do
	make clean -s 2> /dev/null
	gcc -lpthread philo.c -o philo
	output=$(/usr/bin/time -f %e ./philo $n -s 2>&1 > shell.csv)
	echo $n,$output
    done
    
done





 
