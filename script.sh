#!/bin/bash
RUNS=5
NTHREAD=8
echo "nb_coeurs,temps" >script.csv
for ((i=1; i<RUNS; i++))
do
    for((n=1; n<=NTHREAD; n++))
    do
	make clean -s 2> /dev/null
	output=$(/usr/bin/time -f %e ./philo $n -s 2>&1)
	echo $n,${output} >>script.csv
    done
    
done




 
