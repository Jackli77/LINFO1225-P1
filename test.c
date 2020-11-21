#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
int N;
int lock = 0;
int leave(int mem){
	asm(
	"movl $0, %%eax;"
	"xchgl %%eax,%1;"
	"movl %%eax,%0;"
	:"=r"(lock), "=r"(mem)
	);
	printf("lock %d mem %d",lock,mem);
	return mem;
	}
	
int enter(int mem){
	while(mem == 1){
	asm(
	"movl $1 ,%%eax;"
	"xchgl %%eax,%0;"
	"movl %%eax,%1;"
	:"=r"(lock), "=r"(mem)
	:"r"(mem));
	}
	return mem;
	}
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
	N = 10;
	pthread_t threads[N];
	for(int i = 0; i<N; i++){
		pthread_create(&threads[i],NULL,(void *) section_crit,NULL);
		}
	for(int i = 0; i<N; i++){
		pthread_join(threads[i],NULL);
		}
	}
