#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int odkrytePola = 0;
int gameMode;

//wypisywanie aktualnego wyniku na końcu gry
void koniec(){
    int score = odkrytePola*gameMode;
    printf("Twój wynik: %d\n", score);
    saveScore(score);
}