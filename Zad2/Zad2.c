#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <semaphore.h>

#define THREAD_NUM 8

sem_t buffer;
  
void* consumer(void* arg){
    printf("Consumer %d started consuming.\n", *(int*) arg);
    while(1){
        int random_num = (rand()%100);
        if(random_num%20 == 0){
            printf("Consumer %d felt an urge to buy something.\n", *(int*) arg);
            sem_wait(&buffer);
            
            printf("Consumer %d got a banana.\n", *(int*) arg);
       }
       sleep(1);
   }
    printf("Done consuming\n");
    free(arg);
    return NULL;
}

void* producer(void* arg){
    printf("Producer %d started producing.\n", *(int*) arg);
    while(1){
        int random_num = (rand()%100);
        if(random_num%5 == 0){
            printf("Producer %d felt an urge to produce something.\n", *(int*) arg);
            int current_sem_val;
            while(1){
                sem_getvalue(&buffer, &current_sem_val);
                if(current_sem_val < 5){
                    sem_post(&buffer);
                    
                    printf("Producer %d made a product. Products in stock: %d\n", *(int*) arg, current_sem_val);
                    break;
                }
            }
       }
       sleep(1);
   }
    printf("Done producing\n");
    free(arg);
    return NULL;
}

int main() {
    srand(time(NULL));
    sem_init(&buffer, 0, 0);
    pthread_t threads[THREAD_NUM];
    for(int i = 0; i < THREAD_NUM; i++){
        int *a = malloc(sizeof(int));
        *a = i;
        if(pthread_create(threads + i, NULL, i%4 == 0 ? producer : consumer, a) != 0){
            perror("Couldn't create a thread");
            return 1;
        } else {
            printf("Created thread: %d\n", i);
        }
    }
    for(int i = 0; i < THREAD_NUM; i++){
        pthread_join(threads[i],NULL);
    }

    sem_destroy(&buffer);
    return 0;
}