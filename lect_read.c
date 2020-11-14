#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
sem_t mutex,writeblock;
int readercount = 0;
int data = 0;
int count1 = 0;
int count2 = 0;

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
    readercount++;
    if(readercount==1)
        sem_wait(&writeblock);
    sem_post(&mutex);
    lecture();
    sem_wait(&mutex);
    readercount--;
    if(readercount==0)
    {
        sem_post(&writeblock);
    }
    sem_post(&mutex);}
   
}

void writer(void* param)
{
	while(count1 < 640){
   
    sem_wait(&writeblock);
    ecrire();
    sem_post(&writeblock);}
    
    
}

int main()
{
    int N = 2;
    int M = 4;
    
    if(strcmp(argv[1],"-N")==0){
        if(atoi(argv[2])>0){
            N = atoi(argv[2]);
        }
        if(atoi(argv[3])>0){
            M = atoi(argv[3]);
        }
    }
    sem_init(&mutex,0,1);
    sem_init(&writeblock,0,1);
    pthread_t writerthreads[M];
    pthread_t readerthreads[N];
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
