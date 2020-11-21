#include <stdio.h>

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
	:"=r"(counter));
	printf("%d ",counter);
	
	if(counter  == 1){
		//action
		return;}
	else{printf("full");
		enter();}
	}

