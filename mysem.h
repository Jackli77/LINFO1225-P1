#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
struct mysem{
	int *buff;};
int len;
	void leave(struct mysem *a){
	for(int i = 0; i<len;i++){
	int mem = 0;
	asm(
	"movl %0, %%eax;"
	"xchgl %%eax,%1;"
	"movl %%eax,%0;"
	:"=r"(a->buff[i]),"=m"(mem)
	);}
	}
	
	void enter(struct mysem *a){
	for(int i = 0; i< len;i++){
	int mem = 1;
	
	while(mem == 1){
	
		while(a->buff[i] == 1){}
	asm(
	"movl %2 ,%%eax;"
	"xchgl %%eax,%0;"
	"movl %%eax, %1;"
	: "=m"(a->buff[i]),"=r"(mem)
	:"m"(mem));
	
	}}
	
	

	}
	
	void my_init(struct mysem *a,int N){
	len =N;
	a->buff = (int *)malloc(N*sizeof(int));
	int *lok = (int *)malloc(sizeof(int));
	lok[0] = 0;
	for(int i = 0; i<N; i++){
	a->buff[i] = *lok;}
	
	
	
	}
	
	void wait(struct mysem *a){
	
	enter(a);
	}
	
	void post(struct mysem *a){
	leave(a);
	}
	
