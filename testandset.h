#include <stdio.h>
int lock = 0;
void leave(){
	int mem = 0;
	
	asm(
	"movl %0, %%eax;"
	"xchgl %%eax,%1;"
	"movl %%eax,%0;"
	:"=m"(lock),"=m" (mem)
	
	);
	
	
	}
	
void enter(){
	int mem = 1;
	while(mem == 1){
	asm(
	"movl %2 ,%%eax;"
	"xchgl %%eax,%0;"
	"movl %%eax, %1;"
	: "=m"(lock),"=m"(mem)
	:"m"(mem));
	
	}
	
	
	}
