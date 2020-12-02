#!/bin/bash
RUNS=5
NTHREAD=$(nproc)
make clean -s 
make all -s
echo "nb_coeurs,temps" >philo.csv
echo "nb_coeurs,temps" >myphilo.csv
echo "nb_coeurs,temps" >read.csv
echo "nb_coeurs,temps" >myread.csv
echo "nb_coeurs,temps" >prodcons.csv
echo "nb_coeurs,temps" >myprodcons.csv
echo "nb_coeurs,temps" >tas.csv
echo "nb_coeurs,temps" >tatas.csv
for ((i=1; i<=RUNS; i++))
do
  
    for((n=1; n<=NTHREAD*2; n++))
    do
	up=$(((${n}-${n}%2)/2))
	down=(n-n%2)/2
	echo $up
	philoO=$(/usr/bin/time -f %e ./philo ${n} -s 2>&1)
	echo ${n},${philoO} >>philo.csv
	myphiloO=$(/usr/bin/time -f %e ./myphilo ${n} -s 2>&1)
	echo ${n},${myphiloO} >>myphilo.csv
	readO=$(/usr/bin/time -f %e ./read $up $down -s 2>&1)
	echo ${n},${readO} >>read.csv
	myreado=$(/usr/bin/time -f %e ./myread $up $down -s 2>&1)
	echo ${n},${myreado} >>myread.csv
	prodo=$(/usr/bin/time -f %e ./prodcons $up $down -s 2>&1)
	echo ${n},${prodo} >>prodcons.csv
	myprodo=$(/usr/bin/time -f %e ./myprodcons $up $down -s 2>&1)
	echo ${n},${myprodo} >>myprodcons.csv
	taso=$(/usr/bin/time -f %e ./tas ${n} -s 2>&1)
	echo ${n},${taso} >>tas.csv
	tataso=$(/usr/bin/time -f %e ./tatas ${n} -s 2>&1)
	echo ${n},${tataso} >>tatas.csv
    done
   
    
done
