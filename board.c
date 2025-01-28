#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "game.h"

//Widok gracza
void printPlayerView(char** playerView, int rows, int cols){
    printf("  ");
    for (int nc = 0; nc < cols; nc++){
        if( nc<= 9){
            printf("  %d ", nc+1);
        }else{
            printf("  %d", nc+1);
        }
    }
    printf("\n");
    for(int nr = 0; nr < rows; nr++){
        if(nr<9){
            printf(" ");
        }
        printf("%d.", nr+1);
        for(int j = 0; j <= cols; j++){
            printf("| %c ", playerView[nr][j]);
        }
        printf("\n");
    }
}
//Inicjalizacja planszy
void initializeBoard(char** board, int rows, int cols, int mines) {
    // Inicjalizowanie planszy pustymi komórkami
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = '0'; // Pusta komórka (brak miny)
        }
    }
}
//WYświetlenie planszy na początku
void printBoard(char** board, int rows, int cols) {
    printf("  ");
    for (int nc = 0; nc < cols; nc++){
        if(nc<=9){
            printf("  %d ", nc+1); 
        }else{
            printf("  %d", nc+1);
        }
       
    }
    printf("\n");
    for (int i = 0; i < rows; i++) {
        if(i<9){
            printf(" ");
        }
        printf("%d.", i+1);
        for (int j = 0; j <= cols; j++) {
            printf("|   ", board[i][j]);
        }
        printf("\n");
    }
    
}
//Rozmieszczenie min losowo
void placeMines(char** board, int rows, int cols, int mines, int safeX, int safeY){
    int r, c;
    srand(time(NULL));
    int placedMines = 0;

    while (placedMines < mines) {
        r = rand() % rows; // Losowy wiersz
        c = rand() % cols; // Losowa kolumna
        if ((r == safeX && c == safeY) || 
            (r >= safeX - 1 && r <= safeX + 1 && c >= safeY - 1 && c <= safeY + 1) || 
            board[r][c] == 'X') {
            continue;
        }
            board[r][c] = 'X';
            placedMines++;
        }
    

    // Obliczanie liczb w sąsiedztwach
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == 'X') continue; // Pomiń komórki z minami

            int count = 0;
            // Sprawdzanie sąsiednich komórek
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    int nr = i + dr;
                    int nc = j + dc;
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && board[nr][nc] == 'X') {
                        count++;
                    }
                }
            }
            board[i][j] = '0' + count; // Liczba sąsiednich min
        }
    }
}
//Odkrywanie pól
void reveal(char** board, char** playerView, int rows, int cols, int x, int y) {
    int dx, dy; 
    if (x < 0 || x >= rows || y < 0 || y >= cols || playerView[x][y] != '.' || board[x][y] == 'X') {
        return;
    }
    playerView[x][y] = board[x][y];
    odkrytePola++;
    if (board[x][y] == '0') { // Jeśli pole jest puste, odkrywamy sąsiednie
        for (dx = -1; dx <= 1; dx++) {
            for (dy = -1; dy <= 1; dy++) {
                if (dx != 0 || dy != 0) {
                    reveal(board, playerView, rows, cols, x + dx, y + dy);
                }
            }
        }
    }
}
//Zwalnianie pamięci
void freeBoard(char** board, char** playerView, int rows, int cols, int x, int y){
    for (int i = 0; i < rows; i++) {
            free(board[i]);
            free(playerView[i]);
        }
        free(board);
        free(playerView);
}