#!/bin/bash
RUNS=5
NTHREAD=8
echo "nb_coeurs,temps" >script.csv
for ((i=1; i<RUNS; i++))
do
    for((n=1; n<=NTHREAD; n++))
    do
	output=$(/usr/bin/time -f %e ./prodcons.o $n $n -s 2>&1)
	echo $n,${output} >>script.csv
    done
    
done




 
