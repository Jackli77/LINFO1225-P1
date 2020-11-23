#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


int PHILOSOPHES ;


static pthread_mutex_t *baguette;




void mange(int id){
	
	
	}
	
 void* philosophe(void * arg){
	 	
int count = 0;
int *id = (int *) arg;



int left = *id;

int right = (left+1)% PHILOSOPHES;

while(count <10000000){
	
	
	
	if(left<right){
		pthread_mutex_lock(&baguette[left]);
		pthread_mutex_lock(&baguette[right]);
		
		}
	else{
		pthread_mutex_lock(&baguette[right]);
		pthread_mutex_lock(&baguette[left]);
		
		}
	
	mange(*id);
	count ++;
	pthread_mutex_unlock(&baguette[left]);
	pthread_mutex_unlock(&baguette[right]);
	
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
	baguette = malloc(PHILOSOPHES*sizeof(pthread_mutex_t));
	#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include<semaphore.h>
int USED = 1;
int FREE = 0;

int PHILOSOPHES ;


static pthread_mutex_t *baguette;

sem_t *bag;


void mange(int id){
	
	printf("le philosophe %d mange \n",id);
	
	}
	
 void* philosophe(void * arg){
	 	
int count = 0;
int *id = (int *) arg;



int left = *id;

int right = (left+1)% PHILOSOPHES;
sem_post(&bag[right]);
sem_post(&bag[left]);

while(count <10000000){
	
	
	
	if(left<right){
		sem_wait(&bag[left]);
		pthread_mutex_lock(&baguette[left]);
		sem_wait(&bag[right]);
		pthread_mutex_lock(&baguette[right]);
		
		}
	else{
		sem_wait(&bag[right]);
		pthread_mutex_lock(&baguette[right]);
		sem_wait(&bag[left]);
		pthread_mutex_lock(&baguette[left]);
		
		}
	
	mange(*id);
	count ++;
	pthread_mutex_unlock(&baguette[left]);
	sem_post(&bag[left]);
	pthread_mutex_unlock(&baguette[right]);
	sem_post(&bag[right]);
	
	
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
	bag = malloc(PHILOSOPHES*sizeof(sem_t));
	baguette = malloc(PHILOSOPHES*sizeof(pthread_mutex_t));
	
	if(PHILOSOPHES == 1){
		for(int i = 0 ; i< 10000000;i++){
			mange(1);}
			return 1 ;}
	
	
	for(int i= 0 ;i <PHILOSOPHES;i++){
	pthread_mutex_init(&(baguette[i]),NULL);
	sem_init(&bag[i],0,0);
	id[i] = i;
	
	}
	
	for(int i= 0;i<PHILOSOPHES;i++){
		
		pthread_create(&(phil[i]),NULL,&philosophe,&(id[i]));
		
		}
	
		
		
	for(int i = 0;i<PHILOSOPHES;i++){
		pthread_join(phil[i],NULL);
		
		}
		
	for(int i = 0;i< PHILOSOPHES;i++){
		pthread_mutex_destroy(&(baguette[i]));}
		
	
	
}

	if(PHILOSOPHES == 1){
		for(int i = 0 ; i< 10000000;i++){
			mange(1);}
			return 1 ;}
	
	
	for(int i= 0 ;i <PHILOSOPHES;i++){
	pthread_mutex_init(&(baguette[i]),NULL);
	id[i] = i;
	}
	
	for(int i= 0;i<PHILOSOPHES;i++){
		
		pthread_create(&(phil[i]),NULL,&philosophe,&(id[i]));
		
		}
	
		
		
	for(int i = 0;i<PHILOSOPHES;i++){
		pthread_join(phil[i],NULL);
		
		}
		
	for(int i = 0;i< PHILOSOPHES;i++){
		pthread_mutex_destroy(&(baguette[i]));}
		
	
	
}
