#include <stdio.h>
int block =1;
int counter = 0;
int enter(void){
	
	__asm__ __volatile(
	"movl %1, %%eax;"
	"xchgl %%eax,%0;"
	"testl %%eax, %%eax;"
	"jnz enter;"
	"ret;"
	:"=r"(counter)
	:"r"(block)
	: "%eax");
	return 0;}
int leave(void){
	__asm__ __volatile(
	"decl %%eax;"
	"xchgl %%eax,%0;"
	"ret;"
	:"=r"(counter)
	:"r" (counter)
	:"%eax");
	return 0;
	}
