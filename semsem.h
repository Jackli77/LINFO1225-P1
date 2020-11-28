#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
struct mysem{
	int lock;};
	
	void leave(struct mysem *a,int mem){
	asm(
	"movl %0, %%eax;"
	"xchgl %%eax,%1;"
	"movl %%eax,%0;"
	:"=g"(a->lock),"=m"(mem)
	);
	}
	
	int enter(struct mysem *a){
	
	int mem = 0;
	
	while(mem == 0){
	
		while(a->lock == 0){}
	asm(
	"movl %2 ,%%eax;"
	"xchgl %%eax,%0;"
	"movl %%eax, %1;"
	: "=g"(a->lock),"=r"(mem)
	:"m"(mem));
	printf("passed ");
	}
	printf("passed ");
	return mem;
	}
	
	void my_init(struct mysem *a,int lokk){
	a->lock = lokk;
	fprintf(stdout,"%d",a->lock);
	fflush(stdout);
	}
	
	
	void wait(struct mysem*a){
		int mem = enter(a);
		mem--;
		leave(a,mem);
	}
	void post(struct mysem*a){
		int mem = enter(a);
		mem++;
		leave(a,mem);
	}
