#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include"semsem.h"
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
#define MAX 1024
#define N 8
/*Ce fichier résout le problème des producteurs consommateurs pour un producteur qui génère un nombre aléatoire et un consommateur qui attend quelques cycles*/
struct csem mutex;
struct csem empty;
struct csem full;
int take = 0;
int give = 0;
int buffer[N];

void insert_item() {
    buffer[give] = rand();
    give = (1+give)%8;
}

void remove_item() {
    take = (1+take)%8;
}

void producer(void) {
    for(int i = 0;i<=MAX;i++) {
        post(&empty); // attente d'une place libre
        wait(&mutex);// section critique
        insert_item();
        post(&mutex);
        post(&full); // une place remplie en plus  
    }
}

void consumer(void) {
    for(int i = 0;i<=MAX;i++) {
        wait(&full); // attente d'une place remplie
        wait(&mutex);// section critique
        remove_item();
        while (rand() > RAND_MAX / 10000){}
        post(&mutex);
        post(&empty); // une place libre en plus
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
    c_init(&mutex,1);
    c_init(&empty,8);
    c_init(&full,0);

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
    return 0;
}
