#include <stdio.h>
int mem = 1;
extern int counter;

void leave(void){
	asm(
	"movl $0, %%eax;"
	"xchgl %%eax,%0;"
	
	:"=r"(counter)
	:"r" (counter)
	);
	}
void enter(void){
	while(counter  != 1){
	asm(
	"movl %1 ,%%eax;"
	"xchgl %%eax,%0;"
	"movl %%eax,%1;"
	:"=r"(counter)
	:"r"(mem));
	{printf(" %d ",counter);}
		}
	return;
	}

