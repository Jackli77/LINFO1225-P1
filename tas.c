
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
	
	int count = 0;
	
	while(count < 6400/N){
	enter();
	
	while(rand() > RAND_MAX/10000){}
	leave();
	count ++;}
	}
int main(int argc, char *argv[]){
	N = 1;
	if(argc == 2){
		if(atoi(argv[1])>0){
        		N = atoi(argv[1]);
		}
    	}
  
	pthread_t threads[N];
	for(int i = 0; i<N; i++){
		pthread_create(&threads[i],NULL,(void *) section_crit,NULL);
		}
	for(int i = 0; i<N; i++){
		pthread_join(threads[i],NULL);
		}
	}
