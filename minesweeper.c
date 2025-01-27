#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "board.h"
#include "score.h"
#define MAX_TOP_RESULT  5
int odkrytePola = 0;
int gameMode;
//wypisywanie aktualnego wyniku na końcu gry
void koniec(){
    int score = odkrytePola*gameMode;
    printf("Twój wynik: %d\n", score);
    saveScore(score);
}

int main() {
    int rows, cols, mines, x, y;
    char command;
    bool firstMove = true;
    printf("Wbierz tryb gry:\n 1 - łatwy (9x9 i 10 min)\n 2 - średni (16x16 i 40 min)\n 3 - trudny (16x30 i 99 min)\n 4 - Niestandardowy (własny wybór)\n Wybór:\n"); //Wybór trybu gry
    scanf("%d", &gameMode);
    switch (gameMode){
        case 1:
            rows = 9;
            cols = 9;
            mines = 10;
        break;
        case 2:
            rows = 16;
            cols = 16;
            mines = 40;
        break;
        case 3:
            rows = 16;
            cols = 30;
            mines = 99;
        break;
        case 4: 
            printf("Podaj liczbę wierszy, kolum i min\n");
            scanf("%d %d %d", &rows, &cols, &mines);
            if (mines >= rows*cols){
            printf("Zbyt dużo min jak na tą planszę!\n");
            return 1;
            }
            
        break;
    }
    char** board = (char**)malloc(rows * sizeof(char*));
    char** playerView = (char**)malloc(rows * sizeof(char*));
        for (int i = 0; i<rows; i++){
            board[i] = (char*)malloc(cols * sizeof(char));
            playerView[i] = (char*)malloc(cols * sizeof(char));
            for (int j = 0; j < cols; j++) {
                playerView[i][j] = '.';  // Wszystkie pola są początkowo ukryte
            }
        }
    

    // Inicjalizacja planszy
    initializeBoard(board, rows, cols, mines);

    // Wyświetlanie planszy
    printf("Plansza:\n");
    printBoard(board, rows, cols);
    printf("Pora zacząć grę!\n");
    bool gameOver = false;
    while (!gameOver){
        printf("Aktualny stan planszy:\n");
        printPlayerView(playerView, rows, cols);

        printf("Podaj polecenie (f x y - flaga, r x y - odkryj): ");
        scanf(" %c %d %d", &command, &x, &y);

        if (x < 0 || x > rows || y < 0 || y > cols) {
            printf("Nieprawidłowe współrzędne!\n");
            continue;
        }
         if (command == 'f') {
            x--;
            y--;
            if (playerView[x][y] == '.') {
                playerView[x][y] = 'F';  // Postawienie flagi
                printf("Flaga postawiona na (%d, %d)\n", x+1, y+1);
            } else if (playerView[x][y] == 'F'){
                playerView[x][y] = '.';
                printf("Flaga została usunięta z %d %d\n", x+1, y+1);
            } else {
                printf("Nie możesz postawić flagi na tym polu!\n");
            }
        } else if (command == 'r') {
            x--;
            y--;
            if (firstMove) {
                placeMines(board, rows, cols, mines, x, y); //??
                firstMove = false;
            }
           

            if (board[x][y] == 'X') {
                printf("Trafiłeś na minę! Koniec gry:(\n");
                gameOver = true;
            } else if (playerView[x][y] == '.') {
                reveal(board, playerView, rows, cols, x, y);
            } else {
                printf("To pole zostało już odkryte!\n");
            }
        } else {
            printf("Złe polecenie, użyj: r x y aby odkryć pole lub f x y aby postawić (lub zdjąć już postawioną) fl\n");
        }
    }

    printf("\nOstateczny stan planszy:\n");
    printf("  ");
    for (int nrc=0; nrc < cols; nrc++){
        if( nrc<=9){
            printf("  %d ", nrc+1);
        }else{
            printf("  %d", nrc+1);
        }
    }
    printf("\n");
    for (int i = 0; i < rows; i++) {
        if(i<9){
            printf(" ");
        }
        printf("%d.", i+1);
        for (int j = 0; j <= cols; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("\n");
    }
    const char *filename = "wyniki.txt";
    printScore(filename);
    koniec();
     // Zwalnianie pamięci
    for (int i = 0; i < rows; i++) {
        free(board[i]);
        free(playerView[i]);
    }
    free(board);
    free(playerView);
    return 0;
}