#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
// initialisation des variables globales
sem_t block,readmutex,readcount,writemutex,writecount;
int writercount = 0;
int readercount = 0;
int count1 = 0;
int count2 = 0;


//simulation ecriture et lecture
void ecrire(){
	printf("écrire   ");
	//on incrémente le conteur d'écriture et lecture
	count1++;
	while(rand() > RAND_MAX/10000);
	}
void lecture(){
	printf("lire    ");
	count2++;
	while(rand() > RAND_MAX/10000);}

void reader(void* param)
{
	while(count2 < 2560){
	sem_wait(&block);
	sem_wait(&readmutex);
	sem_wait(&readcount);
	readercount ++;
	if(readercount == 1){sem_wait(&writemutex);}
	sem_post(&readcount);
	sem_post(&readmutex);
	sem_post(&block);
	ecrire();
	sem_wait(&readcount);
	readercount --;
	if(readercount ==0){sem_post(&writemutex);}
	sem_post(&readcount);

    }
   
}

void writer(void* param)
{
	while(count1 < 640){
	sem_wait(&writecount);
	writercount++;
	if(writercount == 1){sem_wait(&readmutex);}
	sem_post(&writecount);
	sem_wait(&writemutex);
	ecrire();
	sem_post(&writemutex);
	sem_wait(&writecount);
	writercount --;
	if(writercount == 0){sem_post(&readmutex);}
	sem_post(&writecount);
    //On a fini d'écrire
    
    
    }
    
    
}

int main(int argc, char *argv[])
{
    int lecteurs = 2;
    int ecrivains = 4;
    
     //Specifie le nombre de threads demandés par l'utilisateur, le nombre de threads par défaut est 2 et 4.
   
    if (argc == 3){
        if (atoi(argv[1]) > 0) {
            lecteurs = atoi(argv[1]);
        }
        if (atoi(argv[2]) > 0) {
            ecrivains = atoi(argv[2]);
        }
    }
   
    sem_init(&writecount,0,1);
    sem_init(&writemutex,0,1);
    sem_init(&readcount,0,1);
    sem_init(&readmutex,0,1);
    pthread_t writerthreads[ecrivains];
    pthread_t readerthreads[lecteurs];
    if(ecrivains == 0){
		for (int i = 0; i<2560;i++){lecture();}
		return 0;}
			
     for(int i = 0; i<lecteurs; i++){
		pthread_create(&readerthreads[i],NULL, (void*)reader,NULL);
		}
   
    		for(int i = 0; i<ecrivains; i++){
	pthread_create(&writerthreads[i],NULL, (void*)writer,NULL);}


	for(int i =0;i<ecrivains;i++)
		{
			
			pthread_join(writerthreads[i],NULL);
		}
  
    for(int i =0;i<lecteurs;i++)
    {
        
        pthread_join(readerthreads[i],NULL);
    }
    
	
 
}
