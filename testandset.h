#include <stdio.h>
int block;
int counter = 0;

void leave(void){
	asm(
	"decl %%eax;"
	"xchgl %%eax,%0;"
	"movl %%eax , %1"
	:"=r"(counter)
	:"r" (counter)
	);
	}
	
void enter(void){
	asm(
	"movl %1 ,%%eax;"
	"xchgl %%eax,%0;"
	"movl %%eax, %1;"
	:"=r"(counter)
	:"r"(block));
	
	if(block  == 0){
		//action
		return;}
	else{printf("full");
		enter();}
	}

