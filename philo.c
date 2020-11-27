#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <unistd.h>

int USED = 1;
int FREE = 0;

int PHILOSOPHES ;


sem_t *baguette;


//fonction manger
void mange(int id){
	printf("mange");
	

	
	}
//le thread rentre dans philosophe avec un id	
 void* philosophe(void * arg){
	 	
int count = 0;
int *id = (int *) arg;



int left = *id;

int right = (left+1)% PHILOSOPHES;


while(count <100000){
	
	
	//si gaucher pour eviter les deadlock
	if(left<right){
		sem_wait(&baguette[left]);
		
		sem_wait(&baguette[right]);
		
		
		}
	else{
		sem_wait(&baguette[right]);
		
		sem_wait(&baguette[left]);
		
		
		}
	//les philosophes attendent les deux baguettes libre puis mangent 
	mange(*id);
	count ++;
	
	sem_post(&baguette[left]);
	sem_post(&baguette[right]);
	
	
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
	baguette = malloc(PHILOSOPHES*sizeof(sem_t));
	
	
	if(PHILOSOPHES == 1){
		for(int i = 0 ; i< 100000;i++){
			mange(1);}
			return 1 ;}
	
	
	for(int i= 0 ;i <PHILOSOPHES;i++){
	sem_init(&(baguette[i]),0,1);

	id[i] = i;
	
	}
	
	for(int i= 0;i<PHILOSOPHES;i++){
		
		pthread_create(&(phil[i]),NULL,&philosophe,&(id[i]));
		
		}
	
		
		
	for(int i = 0;i<PHILOSOPHES;i++){
		pthread_join(phil[i],NULL);
		
		}}
		
	
		
	
	
