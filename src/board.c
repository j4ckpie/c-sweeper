#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

// Function to initialize the board
void init_board(Board* b, int rows, int cols, int mines, int difficulty, int mode) {
    b->rows = rows;
    b->cols = cols;
    b->total_mines = mines;
    b->difficulty = difficulty;
    b->score = 0;
    b->turn = 0;

    // Initialization of all fields as closed, no mines
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            b->board[i][j].x = i;
            b->board[i][j].y = j;
            b->board[i][j].is_mine = false;
            b->board[i][j].surrounding_mines = 0;
            b->board[i][j].state = CLOSED;
        }
    }

    if(mode != 1) {
        generate_mines(b);
        calculate_surrounding_mines(b);
    }
}

// Function for generating mines on the board
void generate_mines(Board* b) {
    srand(time(NULL));

    int mines_placed = 0;
    while (mines_placed < b->total_mines) {
        int x = rand() % b->rows;
        int y = rand() % b->cols;

        // Checking if there are no mines in this field
        if (!b->board[x][y].is_mine) {
            b->board[x][y].is_mine = true;
            mines_placed++;
        }
    }
}

// Function for setting the mines manually - input from a file
void set_mine(Board* b, int x, int y) {
    b->board[x][y].is_mine = true;
}

// Function to calculate the number of mines around each field
void calculate_surrounding_mines(Board* b) {
    int dirs[8][2] = { {-1, -1}, {-1, 0}, {-1, 1},
                       {0, -1},          {0, 1},
                       {1, -1}, {1, 0}, {1, 1} };

    for (int i = 0; i < b->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            if (b->board[i][j].is_mine) continue;

            int mine_count = 0;
            for (int k = 0; k < 8; k++) {
                int nx = i + dirs[k][0];
                int ny = j + dirs[k][1];
                if (nx >= 0 && ny >= 0 && nx < b->rows && ny < b->cols) {
                    if (b->board[nx][ny].is_mine) mine_count++;
                }
            }
            b->board[i][j].surrounding_mines = mine_count;
        }
    }
}

// Function to reveal the cell
int open_cell(Board* b, int x, int y, bool firstclick, bool alreadylost) {
    if(0 > x || x >= b->rows || 0 > y || y >= b->cols){
        fprintf(stderr, "[!] Invalid input\n");
        return 0;
    }
    if (b->board[x][y].state != CLOSED) return 0;
    if (b->board[x][y].is_mine && firstclick){
        while (1) {
            int potx = rand() % b->rows;
            int poty = rand() % b->cols;

            if (!b->board[potx][poty].is_mine) {
                b->board[potx][poty].is_mine = true;
                break;
            }
        }
        b->board[x][y].is_mine = false;
        calculate_surrounding_mines(b);
    }
    if(b->board[x][y].is_mine) alreadylost = true;
    b->board[x][y].state = OPEN;
    int cnt = !b->board[x][y].is_mine;
    if ((b->board[x][y].surrounding_mines == 0 && !b->board[x][y].is_mine) || alreadylost) {
        int dirs[8][2] = { {-1, -1}, {-1, 0}, {-1, 1},
                           {0, -1},          {0, 1},
                           {1, -1}, {1, 0}, {1, 1} };

        for (int i = 0; i < 8; i++) {
            int nx = x + dirs[i][0];
            int ny = y + dirs[i][1];
            if (nx >= 0 && ny >= 0 && nx < b->rows && ny < b->cols) {
                cnt += open_cell(b, nx, ny, false, alreadylost);
            }
        }
    }
    return (alreadylost ? 0 : cnt);
}

// Function to flag a cell
void flag_cell(Board* b, int x, int y) {
    if(0 > x || x >= b->rows || 0 > y || y >= b->cols){
        fprintf(stderr, "[!] Invalid input\n");
        return;
    }
    if (b->board[x][y].state == CLOSED) {
        b->board[x][y].state = FLAGGED;
    } else if (b->board[x][y].state == FLAGGED) {
        b->board[x][y].state = CLOSED;
    }
}

// Function to check whether the game is won
int is_game_won(Board *board) {
    int flagsonminescnt = 0;
    int revealdcnt = 0;
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            if (board->board[i][j].state == FLAGGED && board->board[i][j].is_mine) {
                flagsonminescnt++;
            }
            if(board->board[i][j].state == OPEN) revealdcnt++;
        }
    }

    return ((flagsonminescnt == board->total_mines) || revealdcnt == (board->rows * board->cols - board->total_mines));
}

// Function to check whether the game is lost
int is_game_lost(Board *board) {
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            if (board->board[i][j].state == OPEN && board->board[i][j].is_mine) {
                return 1;
            }
        }
    }
    return 0;
}

