#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
struct mysem{
	int buff;};
	void leave(struct mysem *a){
	int mem = 1;
	asm(
	"movl %0, %%eax;"
	"xchgl %%eax,%1;"
	"movl %%eax,%0;"
	:"=r"(a->buff),"=m"(mem)
	);
	}
	
	void enter(struct mysem *a){
	int mem = 0;
	
	while(mem == 0){
	
		while(a->buff == 0){}
	asm(
	"movl %2 ,%%eax;"
	"xchgl %%eax,%0;"
	"movl %%eax, %1;"
	: "=m"(a->buff),"=r"(mem)
	:"m"(mem));
	
	}
	}
	
	void my_init(struct mysem *a,int N){
	a->buff = N;
	}
	
	void mywait(struct mysem *a){
	
	enter(a);
	}
	
	void mypost(struct mysem *a){
	leave(a);
	}
	
