#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    FILE * pFile, * nFile;
    int num;

    scanf("%d", &num);

    int nums[num];

    for(int i = 0; i < num; i++){
        scanf("%d", &nums[i]);
    }
    pFile = fopen("dodatnie.txt" , "a");
    if (!pFile){
         perror ("Cannot open liczby.txt");
    } 
    
    nFile = fopen("ujemne.txt" , "a");
    if (!pFile){
         perror ("Cannot open liczby.txt");
    } 
    
    for(int i = 0; i < num; i++){
        if(nums[i] > 0){
            fprintf(pFile, "%d\n", nums[i]);
        } else if (nums[i] < 0){
            fprintf(nFile, "%d\n", nums[i]);
        } else {
            perror ("0 is signless");
        }
    }
    fclose (pFile);
    fclose (nFile);
    return 0;
}