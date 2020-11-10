#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


int PHILOSOPHES;


pthread_mutex_t *baguette;




void mange(int id){
	printf("Philosophe [%d] mange\n",id);
	for(int i = 0; i<2; i++){
		}
		
	}
	
 void* philosophe(void* arg){
int count = 0;
int *id = (int *) arg;
int left = *id;

int right = (left +1)% PHILOSOPHES;

while(count <10000){
	
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
	
	
	PHILOSOPHES = 4;
	if(argc == 2){
		if(atoi(argv[1])>0){
        		PHILOSOPHES = atoi(argv[1]);
		}
    	}
    
	pthread_t phil[PHILOSOPHES];
	baguette = malloc(PHILOSOPHES*sizeof(pthread_mutex_t));
	
	
	
	for(int i= 0 ;i <PHILOSOPHES;i++){
	pthread_mutex_init(&(baguette[i]),NULL);
	}
	
	

	for(int i=  0; i<PHILOSOPHES;i++){
		pthread_create(&(phil[i]),NULL,&philosophe,&baguette[i]);
		}
		
		
		
	for(int i = PHILOSOPHES-1 ; i>=0;i--){
		pthread_join(phil[i],NULL);
		
		}
		
	for(int i = 0;i< PHILOSOPHES;i++){
		pthread_mutex_destroy(&(baguette[i]));}
		
	
	
}
