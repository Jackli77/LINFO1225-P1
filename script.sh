#!/bin/bash
RUNS=5
NTHREAD=8
echo "nb_coeurs,temps" >philo.csv
echo "producteur,consommateur,temps" >prodcons.csv
echo "writer,reader,temps" > read.csv
for ((i=1; i<RUNS; i++))
do
    for((n=1; n<=NTHREAD; n++))
    do
       	for((m= 1; m<=NTHREAD; m++))
	do
	   prodconsO=$(/usr/bin/time -f %e ./prodcons $n $m -s 2>&1)
	   echo $n,$m,${prodconsO} >>prodcons.csv  
	   readO=$(/usr/bin/time -f %e ./read $n $m -s 2>&1)
	   echo $n,$m,${readO} >>read.csv
	done
	philoO=$(/usr/bin/time -f %e ./philo $n -s 2>&1)
	echo $n,${philoO} >>philo.csv


	

	    
    done
    
done




 
