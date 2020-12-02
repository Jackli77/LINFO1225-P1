
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "semsem.h"
#include <unistd.h>



int PHILOSOPHES ;


struct csem *baguette;
struct csem table;


//fonction manger
void mange(int id){
	
	

	
	}
//le thread rentre dans philosophe avec un id	
 void* philosophe(void * arg){
	 	
int count = 0;
int *id = (int *) arg;



int left = *id;

int right = (left+1)% PHILOSOPHES;


while(count <1000000){
	
	
	//si gaucher pour eviter les deadlock
	if(left<right){
		wait(&baguette[left]);
		wait(&baguette[right]);
		
		
		}
	else{
		wait(&baguette[right]);
		
		wait(&baguette[left]);
		
		
		}
	//les philosophes attendent les deux baguettes libre puis mangent 
	mange(*id);
	count ++;
	
	post(&baguette[left]);
	post(&baguette[right]);
	
	
	
	}
	return (NULL);
}

int main (int argc, char *argv[]){
	PHILOSOPHES = 8;
	if(argc == 2){
		if(atoi(argv[1])>0){
        		PHILOSOPHES = atoi(argv[1]);
		}
    	}
	
	
    
	pthread_t phil[PHILOSOPHES];
	int id[PHILOSOPHES];
	baguette = malloc(PHILOSOPHES*sizeof(struct csem));
	
	
	if(PHILOSOPHES == 1){
		for(int i = 0 ; i< 1000000;i++){
			mange(1);}
			return 1 ;}
	
	c_init(&table,PHILOSOPHES-1);
	for(int i= 0 ;i <PHILOSOPHES;i++){
		
	c_init(&(baguette[i]),1);

	id[i] = i;
	
	}
	
	for(int i= 0;i<PHILOSOPHES;i++){
		
		pthread_create(&(phil[i]),NULL,&philosophe,&(id[i]));
		
		}
	
		
		
	for(int i = 0;i<PHILOSOPHES;i++){
		pthread_join(phil[i],NULL);
		
		}}
		
	
		
	
	
