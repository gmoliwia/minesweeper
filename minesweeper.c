#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int odkrytePola = 0;
int gameMode;
// Funkcja do tworzenia planszy Minesweepera
void initializeBoard(char** board, int rows, int cols, int mines) {
    // Inicjalizowanie planszy pustymi komórkami
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = '0'; // Pusta komórka (brak miny)
        }
    }
}

void koniec(){
    int score = odkrytePola*gameMode;
    printf("Twó wynik: %d\n", score);
    saveScore(score);
}

void saveScore(int score){
    FILE* file = fopen("wyniki.txt", "a");
    if (file == NULL){
        printf("Błąd otwierania pliku\n");
        return;
    }
    fprintf(file, "Punkty: %d\n", score);
    fclose(file);
    printf("Miłej kolejnej gierki!:)\n");
}

    // Losowe rozmieszczanie min
void placeMines(char** board, int rows, int cols, int mines, int safeX, int safeY){
    int r, c, i, j;
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
void printPlayerView(char** playerView, int rows, int cols){
    int j;
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
        for(j = 0; j < cols; j++){
            printf("| %c ", playerView[nr][j]);
        }
        printf("\n");
    }
}

// Funkcja do wyświetlania planszy na początku
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
// Funkcja odkrywająca pole
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
        for (int i = 0; i<cols; i++){
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