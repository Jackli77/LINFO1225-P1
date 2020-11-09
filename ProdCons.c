#include<stdio.h>

int main(int argc, char *argv[]){
    //Specifie le nombre de threads demandés par l'utilisateur, mets le nombre de threads par défaut à 2
    if(atoi(argv[1])>0){
        Nprod = atoi(argv[1]);
    }
    else{
        Nprod = 2;
    }
    if(atoi(argv[2])>0){
        Ncons = atoi(argv[2]);
    }
    else{
        Ncons = 2;
    }

