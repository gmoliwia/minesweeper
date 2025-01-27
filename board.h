#ifndef BOARD_H
#define BOARD_H

void initializeBoard(char** board, int rows, int cols, int mines);
void printBoard(char** board, int rows, int cols);
void printPlayerView(char** playerView, int rows, int cols);
void placeMines(char** board, int rows, int cols, int mines, int safeX, int safeY);
void reveal(char** board, char** playerView, int rows, int cols, int x, int y);
void freeBoard(char** board, char** playerView, int rows, int cols, int x, int y);

#endif