#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#define MAX_ROWS 250
#define MAX_COLS 250

// Typy pól
typedef enum { CLOSED, OPEN, FLAGGED } CellState;

// Struktura reprezentująca pole gry
typedef struct {
    int x, y;          // współrzędne pola
    int surrounding_mines;  // liczba min wokół tego pola
    bool is_mine;      // czy to pole zawiera minę
    CellState state;    // stan pola (zamknięte, otwarte, flagowane)
} Cell;

// Struktura reprezentująca planszę gry
typedef struct {
    Cell board[MAX_ROWS][MAX_COLS];  // tablica pól
    int rows, cols;  // liczba wierszy i kolumn
    int total_mines; // liczba min
    int difficulty, turn, score;
} Board;

void init_board(Board* b, int rows, int cols, int mines, int difficulty);
void print_board(Board* b);
void generate_mines(Board* b);
void calculate_surrounding_mines(Board* b);
int open_cell(Board* b, int x, int y, bool firstclick);
void flag_cell(Board* b, int x, int y);
int is_game_won(Board *board);
int is_game_lost(Board *board);

#endif
