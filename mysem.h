#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
struct mysem{
	int lock;};
	
	void leave(struct mysem *a){
	
	int mem = 0;
	asm(
	"movl %0, %%eax;"
	"xchgl %%eax,%1;"
	"movl %%eax,%0;"
	:"=g"(a->lock),"=m"(mem)
	);
	}
	
	void enter(struct mysem *a){
	
	int mem = 1;
	
	while(mem == 1){
	
		while(a->lock == 1){}
	asm(
	"movl %2 ,%%eax;"
	"xchgl %%eax,%0;"
	"movl %%eax, %1;"
	: "=g"(a->lock),"=r"(mem)
	:"m"(mem));
	printf("block ");
	}
	
	printf("passed ");
	}
	
	void my_init(struct mysem *a){
	int *lok = (int *)malloc(sizeof(int));
	lok[0] = 0;
	a->lock = *lok;
	
	
	
	}
	
	void wait(struct mysem *a){
	
	enter(a);
	}
	
	void post(struct mysem *a){
	leave(a);
	}
	
