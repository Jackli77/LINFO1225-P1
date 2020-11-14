#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
#define MAX 1024
#define N 8
/*Ce fichier résout le problème des producteurs consommateurs pour un producteur qui génère un nombre aléatoire et un consommateur qui attend quelques cycles*/
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int take = 0;
int give = 0;
int buffer[N];

void insert_item() {
    buffer[give] = rand();
    give = (1+give)%8;
}

int remove_item() {
    int temp = buffer[take];
    take = (1+take)%8;
    return temp;
}

void producer(void) {
    for(int i = 0;i<MAX;i++) {
        sem_wait(&empty); // attente d'une place libre
        pthread_mutex_lock(&mutex);// section critique
        insert_item();
        pthread_mutex_unlock(&mutex);
        sem_post(&full); // une place remplie en plus  
    }
}

void consumer(void) {
    int item;
    for(int i = 0;i<MAX;i++) {
        sem_wait(&full); // attente d'une place remplie
        pthread_mutex_lock(&mutex);// section critique
        int item = remove_item();
        while (item > RAND_MAX / 10000){}
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // une place libre en plus
    }
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

    for (int i = 0; i < Nprod; i++) {
        pthread_create(&pro[i], NULL, (void *) producer, i);
    }
    for (int i = 0; i < Ncons; i++) {
        pthread_create(&con[i], NULL, (void *) consumer, i);
    }

    for (int i = 0; i < Nprod; i++) {
        pthread_join(pro[i], NULL);
    }
    for (int i = 0; i < Ncons; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
