#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

sem_t semPing, semPong, semPung;

pthread_mutex_t mutex;

#define PINGS 10
#define PONGS PINGS
#define PUNGS PONGS

void* ping(void* x){
     int pings = PINGS;
     int line_num = 1;
     while(pings-- > 0){
         sem_wait(&semPing);
         printf("%d) ", line_num);
         printf("ping");
         ++line_num;
         sem_post(&semPong);
     }
     return NULL;
}

void* pong(void* x){
     int pongs = PONGS;
     while(pongs-- > 0){
         sem_wait(&semPong);
         printf(" pong");
         printf(" pong");
         sem_post(&semPung);
         
     }
     return NULL;
}

void* pung(void* x){
     int pung = PUNGS;
     while(pung-- > 0){
         sem_wait(&semPung);
         printf(" pung\n");
         sem_post(&semPing);
     }
     return NULL;
}

int main(int argc, const char* argv[]){
    pthread_t pinger, ponger, punger;
    pthread_attr_t attr;
    sem_init(&semPing, 0, 1);
    sem_init(&semPong, 0, 0);
    sem_init(&semPung, 0, 0);
    pthread_attr_init(&attr);
    
    pthread_create(&pinger, &attr, ping, NULL);
    pthread_create(&ponger, &attr, pong, NULL);
    pthread_create(&punger, &attr, pung, NULL);

    pthread_join(pinger, NULL);
    pthread_join(ponger, NULL);
    pthread_join(punger, NULL);

    sem_destroy(&semPing);
    sem_destroy(&semPong);
    sem_destroy(&semPung);

    return 0;
}