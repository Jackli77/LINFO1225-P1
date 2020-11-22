#include <stdio.h>
#include "tatas.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>

int leave(int * lock,int * mem){
	asm(
	"movl (%0), %%eax;"
	"xchgl %%eax,(%1);"
	"movl %%eax,(%0);"
	:"=g"(lock),"=m" (mem)
	);
	return *mem;
	}
	
int enter(int * lock,int * mem){
	while(*mem == 1){
		while(*lock == 1){}
	asm(
	"movl (%2) ,%%eax;"
	"xchgl %%eax,(%0);"
	"movl %%eax, (%1);"
	: "=g"(lock),"=m"(mem)
	:"m"(mem));
	printf("block ");
	}
	printf("passed ");
	return *mem;
	}
	
int * mysem_open(){
	int *lock = (int *)malloc(sizeof(int));
	*lock = 0;
	return lock;
	}
	
int * mysem_init(){
	int *mem = (int *) malloc(sizeof(int));
	*mem = 1;
	return mem;
	}
	
int mysem_wait(int *lock,int *mem){
	*mem = enter(*mem);
	return 0;
	}
	
int mysem_post(int *lock,int *mem){
	*mem = leave(*mem);
	return 0;
	}
void free(int* mem){
	mem = NULL;}
	
int mysem_destroy(int *lock,int *mem){
	free(mem);
	return 0;
	}

int mysem_close(int *lock){
	free(lock);
	return 0;
	}
