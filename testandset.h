#include <stdio.h>
int mem;
int counter = 0;

void leave(void){
	asm(
	"movl $0, %%eax;"
	"xchgl %%eax,%0;"
	
	:"=r"(counter)
	:"r" (counter)
	);
	}
	
void enter(void){
	
	printf("%d ",counter);
	asm(
	"movl $1 ,%%eax;"
	"xchgl %%eax,%0;"
	"movl %%eax,%1;"
	:"=r"(counter)
	:"r"(mem));
	printf("%d ",counter);
	
	if(counter  == 1 && mem == 0){
		//action
		return;}
	else{enter();}
	}

