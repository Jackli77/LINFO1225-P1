#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
// initialisation des variables globales
sem_t writeblock,rsem;
int readercount = 0;
int writercount = 0;
int data = 0;
int count1 = 0;
int count2 = 0;
pthread_mutex_t writecount,readecount;

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
	if(count1>=2560){return;}	
   sem_wait(&rsem);
    //augmentation du lecteur
    pthread_mutex_lock(&readecount);
    
    readercount++;
    
    if(readercount==1)
        sem_wait(&writeblock);
        
   pthread_mutex_unlock(&readecount);
   
    
    //lecture et libération du mutex
    lecture();
    
    pthread_mutex_lock(&readecount);
    readercount--;
    if(readercount==0)
    {
        sem_post(&writeblock);
    }
    //lecture est finie
    pthread_mutex_unlock(&readecount);
    }
   
}

void writer(void* param)
{
	while(count1 < 640){
	if(count1>=640){return;}
	pthread_mutex_lock(&writecount);
	writercount ++;
	if(writercount == 1){sem_wait(&rsem);}
	pthread_mutex_unlock(&writecount);
	sem_wait(&writeblock);
    ecrire();
    sem_post(&writeblock);
    pthread_mutex_lock(&writecount);
    writercount--;
    if(writercount == 0){sem_post(&rsem);}
    pthread_mutex_unlock(&writecount);
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
    sem_init(&rsem,0,1);
    pthread_t writerthreads[N];
    pthread_t readerthreads[M];
    if(N == 0){
		for (int i = 0; i<2560;i++){lecture();}
		return 0;}
    pthread_mutex_init(&readecount,NULL);
    pthread_mutex_init(&writecount,NULL);
    		for(int i = 0; i<N; i++){
	pthread_create(&writerthreads[i],NULL, (void*)writer,NULL);
	}
     for(int i = 0; i<M; i++){
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
