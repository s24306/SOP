#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <signal.h>

pid_t laneId = 1;
int lane = 1;
int lane_traffic[50] = {};
bool is_light_green = 0;
bool na_kazdy_accident_znajdzie_sie_konfident = false;
bool pionowy_lane_accident = false;
bool poziomy_lane_accident = false;

void handleSigusr1Signal(int s) {
    for(int i = 0; i < 50; i++){
        if(lane_traffic[i] == 0){
            lane_traffic[i] = 50;
            break;
        } else if(lane_traffic[i] == 50){
            printf("Crash na pasie %d. Matka zjadła trójkę dzieci.\n", getpid());
            na_kazdy_accident_znajdzie_sie_konfident = true;
            break;
        }
    }
}

void handleSigusr2Signal(int s) {
    printf("Lane %d, Light: %s, cars: [ ", getpid(), is_light_green ? "green" : "red");
        for(int i = 0; i < 50; i++){
            printf("%d, ", lane_traffic[i]);
        }
        printf("]\n");
}

void handlePionowy_lane_accident(int s){
    pionowy_lane_accident = !pionowy_lane_accident;
}

void handlePoziomy_lane_accident(int s){
    poziomy_lane_accident = !poziomy_lane_accident;
}

void *signalistaion(void *arg) {
    while(!na_kazdy_accident_znajdzie_sie_konfident){
        if(is_light_green){
            is_light_green = false;
        } else {
            is_light_green = true;
        }
        sleep(5/1000);
    }
    return 0;
}

void *traffic(void *arg) {
    while(!na_kazdy_accident_znajdzie_sie_konfident){

        int min = 50;
        for(int i = 0; i < 50; i++){
            if((lane_traffic[i] != 0) && (lane_traffic[i] < min)){
                min = lane_traffic[i];
            }
        }
        if(min >= 20 || is_light_green){
            for(int i = 0; i < 50; i++){
                if((lane_traffic[i] != 0)){
                    lane_traffic[i]--;
                }
            }
        }
        if(min < 10){
            if(lane & 1){
                kill(getppid(), SIGUSR1);
            } else {
                kill(getppid(), SIGUSR2);
            }
        }

        sleep(1/1000);
    }
    return 0;
}

void start_lane(int i){
    pthread_t threadId1, threadId2;

    signal(SIGUSR1, handleSigusr1Signal);
    signal(SIGUSR2, handleSigusr2Signal);

    lane = i;

    is_light_green = lane & 1;

    pthread_create(&threadId1, NULL, signalistaion, NULL);
    pthread_create(&threadId2, NULL, traffic, NULL);

    while(!na_kazdy_accident_znajdzie_sie_konfident){
        pause();
    }
}

int main() {
    srand(time(NULL));
    int lanes[4];
    for(int i = 0; i < 4; i++){
        laneId = fork();
        if(laneId != 0){
            lanes[i] = laneId;
            printf("Created lane with id: %d\n", laneId);
        } else if (laneId == 0){
            start_lane(i);
            kill(0, SIGTERM);
        } else {
            printf("Failed to create one of the lanes. Terminating program.");
            kill(0, SIGTERM);
        }

        sleep(1);
    }

    signal(SIGUSR1, handlePionowy_lane_accident);
    signal(SIGUSR2, handlePoziomy_lane_accident);

    if (lane != 0){
        while(1){
            int pid = lanes[rand()%4];
            kill(pid, SIGUSR1);
            printf("Dodano wóz do %d\n", pid);
            for(int i = 0; i < 4; i++){
                kill(lanes[i], SIGUSR2);
            }
            printf("\n");
            printf("Pionowy lane mniej niż 10: %d\n", pionowy_lane_accident);
            printf("Poziomy lane mniej niż 10: %d\n", poziomy_lane_accident);

            if(pionowy_lane_accident && poziomy_lane_accident){
                printf("Crash pomiędzy lane'ami.  Niech im ziemia lepką Będzin\n");
                break;
            }

            pionowy_lane_accident = false;
            poziomy_lane_accident = false;


            sleep(5/1000);
        }
        kill(0, SIGTERM);
    }

    return 0;
}