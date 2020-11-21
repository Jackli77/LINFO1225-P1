#include <stdio.h>
int block =1;
int counter = 0;

void leave(void){
	asm(
	"decl %%eax;"
	"xchgl %%eax,%0;"
	:"=r"(counter)
	:"r" (counter)
	:"%eax");
	}
	
void enter(void){
	asm(
	"movl %1, %%eax;"
	"xchgl %%eax,%0;"
	:"=r"(counter)
	:"r"(block));
	if(block  == 0){
		//action
		leave();}
	else{enter();}
	}

