#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "board.h"
#include "score.h"

void test_initializeBoard() {
    int rows = 5, cols = 5;
    char** board = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        board[i] = (char*)malloc(cols * sizeof(char));
    }

    initializeBoard(board, rows, cols, 0);

    // Sprawdzenie czy wszystkie pola są inicjalizowane jako '0'
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            assert(board[i][j] == '0');
        }
    }

    printf("test_initializeBoard PASSED\n");

    for (int i = 0; i < rows; i++) {
        free(board[i]);
    }
    free(board);
}

void test_saveScore() {
    int testScore = 50;
    isTestMode = 1;
    saveScore(testScore); // Funkcja zapisuje wynik do pliku

    // Sprawdzenie czy plik wynikowy zawiera ten wynik
    FILE *file = fopen("wyniki.txt", "r");
    bool found = false;
    int score;
    while (fscanf(file, "%d", &score) != EOF) {
        if (score == testScore) {
            found = true;
            break;
        }
    }
    fclose(file);

    assert(found);
    printf("test_saveScore PASSED\n");
}

void test_reveal() {
    int rows = 5, cols = 5;
    char** board = (char**)malloc(rows * sizeof(char*));
    char** playerView = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        board[i] = (char*)malloc(cols * sizeof(char));
        playerView[i] = (char*)malloc(cols * sizeof(char));
        for (int j = 0; j < cols; j++) {
            board[i][j] = '0';
            playerView[i][j] = '.';
        }
    }

    // Dodanie miny i test rekurencyjnego odkrycia
    board[2][2] = 'X';
    reveal(board, playerView, rows, cols, 0, 0);

    // Sprawdzenie, czy pole zostało odkryte
    assert(playerView[0][0] == '0');

    printf("test_reveal PASSED\n");

    for (int i = 0; i < rows; i++) {
        free(board[i]);
        free(playerView[i]);
    }
    free(board);
    free(playerView);
}

int main() {
    test_initializeBoard();
    test_saveScore();
    test_reveal();
    printf("Wszystkie testy zakończone sukcesem!\n");
    return 0;
}
