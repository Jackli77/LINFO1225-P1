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
int buffer[N];
int pdced = 0;
int csmed = 0;

void insert_item() {
    buffer[pdced%N] = rand();
    pdced++;
}

void remove_item() {
	buffer[csmed%N] = 0;
    csmed++;
    while (rand() > RAND_MAX / 10000){}
}

void producer(void) {
    while(pdced < MAX) {
        sem_wait(&empty); // attente d'une place libre
        pthread_mutex_lock(&mutex);// section critique
        if(pdced == MAX){
			pthread_mutex_unlock(&mutex);
			sem_post(&full);
		}
        insert_item();
        pthread_mutex_unlock(&mutex);
        sem_post(&full); // une place remplie en plus  
    }
}

void consumer(void) {
    while(csmed < MAX) {
        sem_wait(&full); // attente d'une place remplie
        pthread_mutex_lock(&mutex);// section critique
        if(csmed == MAX){
			pthread_mutex_unlock(&mutex);
			sem_post(&empty);
		}
        remove_item();
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
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);

    for (int i = 0; i < Nprod; i++) {
        pthread_create(&pro[i], NULL, (void *) producer, (void*) &i);
    }
    for (int i = 0; i < Ncons; i++) {
        pthread_create(&con[i], NULL, (void *) consumer, (void*) &i);
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
