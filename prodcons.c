#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include<string.h>
#include<stdbool.h>

#define N 8
/*Ce fichier résout le problème des producteurs consommateurs pour un producteur qui génère un nombre aléatoire et un consommateur qui attend quelques cycles*/
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int buffer[N];

void insert_item() {
    for (int i = 0; i < N; i++) {
        if (buffer[i] == NULL) {
            buffer[i] = rand();
            return;
        }
    }
}

void remove_item() {
    for (int i = 0; i < N; i++) {
        if (buffer[i] != NULL) {
            buffer[i] = NULL;
            return;
        }
    }
}

void producer(void) {
    while (true) {
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
        remove_item();
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // une place libre en plus
    }
    while (rand() > RAND_MAX / 10000) {}
}

int main(int argc, char *argv[]) {
    //Specifie le nombre de threads demandés par l'utilisateur, le nombre de threads par défaut est 2.
    int Nprod = 2;
    int Ncons = 2;
    if (argc == 3){
        if (atoi(argv[1]) > 0) {
            Nprod = atoi(argv[1]);
        }
        if (atoi(argv[2]) > 0) {
            Ncons = atoi(argv[2]);
        }
    }
    pthread_t pro[Nprod], con[Ncons];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);

    int a[5] = {1, 2, 3, 4, 5}; //Just used for numbering the producer and consumer

    for (int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, (void *) producer, (void *) &a[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, (void *) consumer, (void *) &a[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
