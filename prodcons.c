#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#define N 8
/*Ce fichier résout le problème des producteurs consomateurs pour un prodcteur qui génère un nombre aléatoire et un consommateur qui attend une durée aléatoire*/


void producer(void){
    int item;
    while(true){
        item = rand();
        sem_wait(&empty); // attente d'une place libre
        pthread_mutex_lock(&mutex);// section critique
        insert_item();
        pthread_mutex_unlock(&mutex);    
        sem_post(&full); // une place remplie en plus  
    }
}

void consumer(void){
    int item;
    while(true) {
        sem_wait(&full); // attente d'une place remplie
        pthread_mutex_lock(&mutex);// section critique
        item=remove(item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // une place libre en plus
        }
    }

int main(int argc, char *argv[]){
    //Specifie le nombre de threads demandés par l'utilisateur, le nombre de threads par défaut est 2.
    int Nprod = 2;
    int Ncons = 2;
    int buffer[N];
    if(atoi(argv[1])>0){
        Nprod = atoi(argv[1]);
    }
    if(atoi(argv[2])>0){
        Ncons = atoi(argv[2]);
    }
    pthread_t thread_id;
    pthread_create(&thread_id,NULL,produce,NULL);
    pthread_mutex_t mutex;
    sem_t empty;
    sem_t full;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0 , N);  // buffer vide
    sem_init(&full, 0 , 0);
    return 0;
}
