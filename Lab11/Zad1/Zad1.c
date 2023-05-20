#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <semaphore.h>

sem_t printer;
int num;
  
void* worker(void* arg){
    printf("Worker %d started working.\n", *(int*) arg);
    while(1){
        int random_num = (rand()%100);
        if(random_num%7 == 0){
            printf("Worker %d felt an urge to print something.\n", *(int*) arg);
            sem_wait(&printer);
            printf("Printing...\n");
        
            sleep(4);
            
            printf("%d is done printing.\n", *(int*) arg);
            sem_post(&printer);
       }
       sleep(1);
   }
    printf("Done printing\n");
    free(arg);
}

int main() {
    srand(time(NULL));
    sem_init(&printer, 0, 1);
    FILE * workers;
    workers = fopen("Workers.txt", "r");
    if(!workers){
        perror("Can't open Workers.txt");
        return 1;
    }
    fscanf(workers, "%d", &num);
    fclose(workers);
    pthread_t t[num];
    for(int i = 0; i < num; i++){
        int *a = malloc(sizeof(int));
        *a = i;
        if(pthread_create(t + i, NULL, worker, a) != 0){
            perror("Couldn't create a thread");
            return 1;
        } else {
            printf("Created thread: %d\n", i);
        }
    }
    for(int i = 0; i < num; i++){
        pthread_join(t[i],NULL);
    }

    sem_destroy(&printer);
    return 0;
}