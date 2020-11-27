#!/bin/bash
RUNS=5
NTHREAD=$(nproc)

echo "nb_coeurs,temps" >philo.csv
echo "nbcoeurs,temps" >prodcons.csv
echo "nbcoeurs,temps" > read.csv
echo "nbcoeurs,temps" > test.csv

for ((i=1; i<RUNS; i++))
do
    
    for((n=1; n<=NTHREAD*2; n++))
    do
	 make clean -s 
	 make all -s
	if (( $n % 2 == 0))
	then
	   
	    prodconsO=$(/usr/bin/time -f %e ./prodcons $n $n -s 2>&1)
	    echo $n,${prodconsO} >>prodcons.csv
	     readO=$(/usr/bin/time -f %e ./read $n $n -s 2>&1)
	     echo $n,${readO} >>read.csv
	else
	    prodconsO=$(/usr/bin/time -f %e ./prodcons $n $n+1 -s 2>&1)
	    echo $n,${prodconsO} >>prodcons.csv
	    readO=$(/usr/bin/time -f %e ./read $n+1 $n -s 2>&1)
	    echo $n,${readO} >>read.csv
	fi
	philoO=$(/usr/bin/time -f %e ./philo $n -s 2>&1)
	echo $n,${philoO} >>philo.csv
	testO=$(/usr/bin/time -f %e ./test $n -s 2>&1)
	echo $n,${testO} >>test.csv


	

	    
    done
    
done
