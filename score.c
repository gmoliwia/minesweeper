#include <stdio.h>
#include <stdlib.h>
#include "score.h"
#include "game.h"
int isTestMode = 0;
#define MAX_TOP_RESULT 5
//zapisywanie wyniku do pliku
void saveScore(int score){
    FILE* file = fopen("wyniki.txt", "a");
    if (file == NULL){
        printf("Błąd otwierania pliku\n");
        return;
    }
    fprintf(file, "%d\n", score);
    fclose(file);
    if( !isTestMode){
        printf("Miłej kolejnej gierki!:)\n");
    }
}
//wypisywanie 5 najlepszych wyników
void printScore(const char* filename){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Błąd otwierania pliku\n");
        return;
    }
    int TOP[MAX_TOP_RESULT] = {0};
    int scores;
    while(fscanf(file, "%d", &scores) == 1){
        for(int i = 0; i<MAX_TOP_RESULT; i++){
            if(scores > TOP[i]){
                for(int j = MAX_TOP_RESULT - 1;j>i; j-- ){
                    TOP[j] = TOP[j-1];
                }
                TOP[i] = scores;
                break;
            }
        }
    }
    fclose(file);
    printf("Top %d wyników:\n", MAX_TOP_RESULT);
    for(int i = 0; i<MAX_TOP_RESULT; i++){
        if(TOP[i]>0){
            printf("%d\n", TOP[i]);
        }
    }
}

