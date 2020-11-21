#include <stdio.h>
int lock = 0;
int leave(int mem){
	
	asm(
	"movl %0, %%eax;"
	"xchgl %%eax,%1;"
	"movl %%eax,%0;"
	:"=g"(lock),"=m" (mem)
	
	);
	
	
	return mem;
	}
	
int enter(int mem){
	while(mem == 1){
	asm(
	"movl %2 ,%%eax;"
	"xchgl %%eax,%0;"
	"movl %%eax, %1;"
	: "=g"(lock),"=m"(mem)
	:"m"(mem));
	printf("block ");
	
	}
	printf("passed ");
	return mem;
	}
