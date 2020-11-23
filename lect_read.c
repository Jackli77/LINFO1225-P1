#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
// initialisation des variables globales
sem_t writeblock;
int readercount = 0;
int writercount = 0;
int data = 0;
int count1 = 0;
int count2 = 0;
pthread_mutex_t mutex;

//simulation ecriture et lecture
void ecrire(){
	printf("écriture\n");
	//on incrémente le conteur d'écriture et lecture
	count1++;
	while(rand() > RAND_MAX/10000);
	}
void lecture(){
	printf("lecture\n");
	count2++;
	while(rand() > RAND_MAX/10000);}

void reader(void* param)
{
	while(count2 < 2560){	
   
    //augmentation du lecteur
    pthread_mutex_lock(&mutex);
    
    readercount++;
    
    if(readercount==1)
        sem_wait(&writeblock);
        
   pthread_mutex_unlock(&mutex);
   
    
    //lecture et libération du mutex
    lecture();
    
    pthread_mutex_lock(&mutex);
    readercount--;
    if(readercount==0)
    {
        sem_post(&writeblock);
    }
    //lecture est finie
    pthread_mutex_unlock(&mutex);
    }
   
}

void writer(void* param)
{
	while(count1 < 640){
	sem_wait(&writeblock);
    ecrire();
    sem_post(&writeblock);
    //On a fini d'écrire
    
    
    }
    
    
}

int main(int argc, char *argv[])
{
    int N = 2;
    int M = 4;
    
     //Specifie le nombre de threads demandés par l'utilisateur, le nombre de threads par défaut est 2 et 4.
   
    if (argc == 3){
        if (atoi(argv[1]) > 0) {
            N = atoi(argv[1]);
        }
        if (atoi(argv[2]) > 0) {
            M = atoi(argv[2]);
        }
    }
   
    sem_init(&writeblock,0,1);
    pthread_t writerthreads[M];
    pthread_t readerthreads[N];
    pthread_mutex_init(&mutex,NULL);
     for(int i = 0; i<N; i++){
		pthread_create(&readerthreads[i],NULL, (void*)reader,NULL);
		}
		for(int i = 0; i<M; i++){
	pthread_create(&writerthreads[i],NULL, (void*)writer,NULL);
	}
	
  
    for(int i =0;i<N;i++)
    {
        
        pthread_join(readerthreads[i],NULL);
    }
    
	for(int i =0;i<M;i++)
		{
			
			pthread_join(writerthreads[i],NULL);
		}
 
}
