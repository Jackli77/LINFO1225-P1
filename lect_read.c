#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
sem_t mutex,writeblock;
int readercount = 0;
int writercount = 0;
int data = 0;
int count1 = 0;
int count2 = 0;
pthread_mutex_t rcounter,wcounter;


void ecrire(){
	printf("écriture\n");
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
    sem_wait(&mutex);
    pthread_mutex_lock(&rcounter);
    
    readercount++;
    
    if(readercount==1)
        sem_wait(&writeblock);
        
   pthread_mutex_unlock(&rcounter);
    sem_post(&mutex);
    lecture();
    sem_wait(&mutex);
    pthread_mutex_lock(&rcounter);
    readercount--;
    if(readercount==0)
    {
        sem_post(&writeblock);
    }
    pthread_mutex_unlock(&rcounter);
    sem_post(&mutex);}
   
}

void writer(void* param)
{
	while(count1 < 640){
   pthread_mutex_lock(&wcounter);
   writercount++;
   if(writercount ==1){sem_wait(&mutex);}
   pthread_mutex_unlock(&wcounter);
    sem_wait(&writeblock);
    ecrire();
    sem_post(&writeblock);
    pthread_mutex_lock(&wcounter);
    writercount --;
    if(writercount == 0){sem_post(&mutex);}
    pthread_mutex_unlock(&wcounter);
    
    }
    
    
}

int main(int argc, char *argv[])
{
    int N = 2;
    int M = 4;
    
     //Specifie le nombre de threads demandés par l'utilisateur, le nombre de threads par défaut est 2.
   
    if (argc == 3){
        if (atoi(argv[1]) > 0) {
            N = atoi(argv[1]);
        }
        if (atoi(argv[2]) > 0) {
            M = atoi(argv[2]);
        }
    }
    sem_init(&mutex,0,1);
    sem_init(&writeblock,0,1);
    pthread_t writerthreads[M];
    pthread_t readerthreads[N];
    pthread_mutex_init(&rcounter,NULL);
    pthread_mutex_init(&wcounter,NULL);
    for(int i = 0; i<M; i++){
	pthread_create(&writerthreads[i],NULL, (void*)writer,NULL);
	}
     for(int i = 0; i<N; i++){
		pthread_create(&readerthreads[i],NULL, (void*)reader,NULL);
		}
	
  
	for(int i =0;i<M;i++)
		{
			
			pthread_join(writerthreads[i],NULL);
		}
    for(int i =0;i<N;i++)
    {
        
        pthread_join(readerthreads[i],NULL);
    }
 
}
