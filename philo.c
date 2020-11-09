#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#define PHILOSOPHES 3

pthread_t phil[PHILOSOPHES];
pthread_mutex_t baguette[PHILOSOPHES];

void mange(int id){
	printf("Philosophe [%d] mange\n",id);
	for(int i = 0; i<rand(); i++){
		}
	}
void* philosophe(void* arg){
	int *id = (int *) arg;
	int left = *id;
	int right = (left +1)% PHILOSOPHES;
	while(true){
		if(left<right){
			pthread_mutex_lock(&baguette[left]);
			pthread_mutex_lock(&baguette[right]);
			mange(*id);
			}
		else{
			pthread_mutex_lock(&baguette[right]);
			pthread_mutex_lock(&baguette[left]);
			mange(*id);
			}
		
		pthread_mutex_unlock(&baguette[left]);
		pthread_mutex_unlock(&baguette[right]);
			
		}
		return (NULL);
	}
int main (int argc, char *argv[]){
	pthread_t phil[PHILOSOPHES];
	
	for(int i= 0 ;i <PHILOSOPHES;i++){
	pthread_mutex_init( &baguette[i],NULL);
	}

	for(int i=  0; i<PHILOSOPHES;i++){
		pthread_create(&(phil[i]),NULL,&philosophe,NULL);
		}
		
		
	for(int i = PHILOSOPHES-1 ; i>=0;i--){
		pthread_join(phil[i],NULL);
		}
	for(int i = 0;i< PHILOSOPHES;i++){
		pthread_mutex_destroy(&baguette[i]);}
		
	
	
}
