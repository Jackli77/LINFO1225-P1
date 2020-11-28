
#include "mysem.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
// initialisation des variables globales
struct mysem block,readmutex,readcount,writemutex,writecount;

int writercount;
int readercount;
int count1 = 0;
int count2 = 0;


//simulation ecriture et lecture
void ecrire(){
	
	
	//on incrémente le conteur d'écriture et lecture
	
	while(rand() > RAND_MAX/10000);
	count1++;
	}
void lecture(){


	
	
	while(rand() > RAND_MAX/10000);
	count2++;}
	

void reader(void* param)
{
	while(count2 < 2560){
	wait(&block);
	
	wait(&readmutex);
	wait(&readcount);
	readercount ++;
	if(readercount == 1){wait(&writemutex);}
	post(&readcount);
	post(&readmutex);
	post(&block);
	lecture();
	wait(&readcount);
	readercount --;
	if(readercount ==0){post(&writemutex);}
	post(&readcount);

    }
   
}

void writer(void* param)
{
	while(count1 < 640){
	wait(&writecount);
	writercount++;
	if(writercount == 1){wait(&readmutex);}
	post(&writecount);
	wait(&writemutex);
	ecrire();
	post(&writemutex);
	wait(&writecount);
	writercount --;
	if(writercount == 0){post(&readmutex);}
	post(&writecount);
    //On a fini d'écrire
    
    
    }
    
    
}

int main(int argc, char *argv[])
{
    int lecteurs = 2;
    int ecrivains = 2;
    
     //Specifie le nombre de threads demandés par l'utilisateur, le nombre de threads par défaut est 2 et 4.
   
    if (argc == 3){
        if (atoi(argv[1]) > 0) {
            lecteurs = atoi(argv[1]);
        }
        if (atoi(argv[2]) >= 0) {
            ecrivains = atoi(argv[2]);
        }
    }
	readercount = lecteurs;
	writercount = ecrivains;
	if(ecrivains == 0){
		for (int i = 0; i<2560;i++){
			lecture();}
		return 0;}
    my_init(&writecount,1);
    my_init(&writemutex,1);
    my_init(&readcount,1);
    my_init(&readmutex,1);
	my_init(&block,1);
	
    pthread_t writerthreads[ecrivains];
    pthread_t readerthreads[lecteurs];
    
			
   
   
	for(int i = 0; i<ecrivains; i++){
	pthread_create(&writerthreads[i],NULL, (void*)writer,NULL);}
	
  for(int i = 0; i<lecteurs; i++){
		pthread_create(&readerthreads[i],NULL, (void*)reader,NULL);
		}

	for(int i =0;i<ecrivains;i++)
		{
			
			pthread_join(writerthreads[i],NULL);
		}
  
    for(int i =0;i<lecteurs;i++)
    {
        
        pthread_join(readerthreads[i],NULL);
    }
    
	
 
}
