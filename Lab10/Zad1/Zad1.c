#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100

int main(){
    FILE * pFile;
    int nums [SIZE];

    pFile = fopen("liczby.txt" , "r");
    if (!pFile){
         perror ("Cannot open liczby.txt");
    } else {
        for(int i = 0; i < SIZE; i++){
            fscanf(pFile, "%d", &nums[i]);
        }
        int max = -214738902;
        int min = 214738902;
        for(int i = 0; i < SIZE; i++){
            if(nums[i] > max){
                max = nums[i];
            } else if (nums[i] < min){
                min = nums[i];
            }
        }
        printf("Max: %d\nMin: %d\n", max, min);
    }
    fclose (pFile);
    return 0;
}