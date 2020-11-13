#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include<string.h>
#define N 8
/*Ce fichier résout le problème des producteurs consommateurs pour un producteur qui génère un nombre aléatoire et un consommateur qui attend quelques cycles*/
sem_t mutex;
int buffer[N];
for(int i = 0; i<N; i++){
buffer[i] = NULL;
}

void insert_item() {
    for (int i = 0; i < N; i++) {
        if (buffer[i] == NULL) {
            buffer[i] = rand();
            return;
        }
    }
}

void remove() {
    for(int i = 0; i < N; i++){
        if(buffer[i] != NULL){
            int temp = buffer[i];
            buffer[i] = NULL;
            return;
        }
    }
}

void producer(void) {
    while (true) {
        item = rand();
        sem_wait(&empty); // attente d'une place libre
        pthread_mutex_lock(&mutex);// section critique
        insert_item();
        pthread_mutex_unlock(&mutex);
        sem_post(&full); // une place remplie en plus  
    }
}

void consumer(void) {
    while (true) {
        sem_wait(&full); // attente d'une place remplie
        pthread_mutex_lock(&mutex);// section critique
        remove();
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // une place libre en plus
    }
    while(rand() > RAND_MAX/10000);{}
}

int main(int argc, char *argv[]) {
    //Specifie le nombre de threads demandés par l'utilisateur, le nombre de threads par défaut est 2.
    int Nprod = 2;
    int Ncons = 2;
    if (strcmp(argv[1], "-N") == 0) {
        if (atoi(argv[2]) > 0) {
            Nprod = atoi(argv[2]);
        }
        if (atoi(argv[3]) > 0) {
            Ncons = atoi(argv[3]);
        }
    }
    pthread_mutex_t mutex;
    sem_t empty;
    sem_t full;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, N);  // buffer vide
    sem_init(&full, 0, 0);
    return 0;
}
