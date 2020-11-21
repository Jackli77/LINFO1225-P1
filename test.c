#include "testandset.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
int N;

void section_crit(void){
	int mem = 1;
	int count = 0;
	while(count < 6400/N){
	mem = enter(mem);
	while(rand() > RAND_MAX/1000){}
	mem = leave(mem);
	count ++;}
	}
int main(void){
	N = 1;
	pthread_t threads[N];
	for(int i = 0; i<N; i++){
		pthread_create(&threads[i],NULL,(void *) section_crit,NULL);
		}
	for(int i = 0; i<N; i++){
		pthread_join(threads[i],NULL);
		}
	}
