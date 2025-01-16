#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "board.h"

#define BUFSIZE 8192

void game(char *file_path) {
    int mode;
    int rows;
    int columns;
    int mines;
    int difficulty;
    if(file_path == NULL) {
        // Keyboard input
        while(1){

            print_logo();
            printf("\n");
            print_modes();
            printf("PLAYER'S INPUT: ");

            // Check if input is number
            if(scanf("%d", &mode) != 1) {
                fprintf(stderr, "\n[!] Invalid input! Please enter a coressponding number.\n\n");
                while(getchar() != '\n'); // Clear buffer
                goto end_turn;
            }

            // Check if mode is correct
            if(mode < 1 || mode > 6) {
                fprintf(stderr, "\n[!] Invalid input! Please enter a coressponding number.\n\n");
                goto end_turn;        
            }

            Board board;

            switch(mode) {
                case 1:
                    rows = 9;
                    columns = 9;
                    mines = 10;
                    difficulty = 1;
                    break;
                case 2:
                    rows = 16;
                    columns = 16;
                    mines = 40;
                    difficulty = 2;
                    break;
                case 3:
                    rows = 16;
                    columns = 30;
                    mines = 99;
                    difficulty = 3;
                    break;
                case 4:
                    printf("Enter custom rows: ");
                    scanf("%d", &rows);
                    printf("Enter custom columns: ");
                    scanf("%d", &columns);
                    printf("Enter number of mines: ");
                    scanf("%d", &mines);
                    difficulty = 0;
                    break;
                case 5:
                    printf("\n");
                    print_scoreboard("data/scoreboard.txt");
                    goto end_turn;
                case 6:
                    goto end_program;
            }

            init_board(&board, rows, columns, mines, difficulty, 0);
            printf("\nGAME STARTED!\n");
            print_board(&board);    

            char command[256];
            int x, y;   
            while(1) {
                printf("\nEnter command: ");
                if(scanf("%s %d %d", command, &x, &y) != 3) {
                    fprintf(stderr, "[!] Invalid input.\n");
                    continue;
                }

                if (strcmp(command, "f") == 0) {
                    flag_cell(&board, x, y);
                } else if (strcmp(command, "r") == 0) {
                    board.score += board.difficulty * open_cell(&board, x, y, board.turn == 0);
                } else {
                    printf("[!] Invalid command.\n");
                    continue;
                }
                
                print_board(&board);

                if (is_game_lost(&board)) {
                    printf("[!] GAME OVER! You hit a mine.\n");
                    printf("[!] FINAL SCORE: %d\n", board.score);
                    ask_for_nickname(board.score);
                    goto end_program;
                }

                if (is_game_won(&board)) {
                    printf("[!] YOU WIN!\n");
                    printf("[!] FINAL SCORE: %d\n", board.score);
                    ask_for_nickname(board.score);
                    goto end_program;
                }
                board.turn++;
            }
            end_turn:;
        }
    } else {
        // File input
        FILE *file = fopen(file_path, "r");

        if(file == NULL) {
            fprintf(stderr, "[!] Error when trying to open file!\n");
            return;
        }

        char buf[BUFSIZE];
        int is_board = 1;
        int column_test = 0;

        // Analize input in order to initialize the board correctly
        while(fgets(buf, BUFSIZE, file) != NULL) {
            char *tmp = malloc(strlen(buf) + 1);
            strcpy(tmp, buf);

            // Check if whole board got read
            if(strlen(tmp) <= 2 && is_board == 1) {
                is_board = 0;
                continue;
            } else if(is_board == 1) {
                columns = strlen(tmp) - 2;
                column_test += columns;
                rows++;
                for(int i = 0; i < columns; i++) {
                    // Check if board syntax is correct
                    if(tmp[i] != '*' && tmp[i] != '0') {
                        fprintf(stderr, "[!] Invalid input syntax! Ending the script...\n");
                        goto end_program;
                    }
                    // Add mines
                    if(tmp[i] == '*') {
                        mines++;
                    }
                }
            } else if(is_board == 0) {
                break;
            }
        }

        // Check if board size is correct
        if(columns * rows != column_test) {
            fprintf(stderr, "[!] Invalid board size! Ending the script...\n");
            goto end_program;
        }

        // Initialize the board with collected data
        Board board;
        init_board(&board, rows, columns, mines, 0, 1);

        is_board = 1;
        char command[256];
        int x, y; 
        int j = 0;
        
        rewind(file);

        // Read the file again, now with moves
        while(fgets(buf, BUFSIZE, file) != NULL) {
            char *tmp = malloc(strlen(buf) + 1);
            strcpy(tmp, buf);

            // Check if whole board got read
            if(strlen(tmp) <= 2 && is_board == 1) {
                is_board = 0;
                continue;
            } else if(is_board == 1) {
                for(int i = 0; i < columns; i++) {
                    // Set mines
                    if(tmp[i] == '*') {
                        set_mine(&board, i, j);
                    }
                }
                j++;
            } else if(is_board == 0) {
                calculate_surrounding_mines(&board);
                command[0] = tmp[0];
                x = (int)tmp[2] - (int)'0';
                y = (int)tmp[4] - (int)'0';

                // Check if input is correct
                if(x < 0 || x > columns) {
                    fprintf(stderr, "[!] Invalid X value! Ending the script...\n");
                    goto end_program;
                } else if(y < 0 || y > rows) {
                    fprintf(stderr, "[!] Invalid Y value! Ending the script...\n");
                    goto end_program;
                } else if(command[0] != 'f' && command[0] != 'r') {
                    fprintf(stderr, "[!] Invalid input syntax! Ending the script...\n");
                    goto end_program;
                }

                // Play the move
                if (strcmp(command, "f") == 0) {
                    flag_cell(&board, x, y);
                } else if (strcmp(command, "r") == 0) {
                    board.score += board.difficulty * open_cell(&board, x, y, 0);
                } else {
                    printf("[!] Invalid command.\n");
                    continue;
                }

                // Check whether the game is lost or won
                if (is_game_lost(&board)) {
                    printf("[ ] Ending move sequence!\nMOVES: %d | POINTS: %d | SUCCESS: %d\n", board.turn, board.score, 0);
                    goto end_program;
                }

                if (is_game_won(&board)) {
                    printf("[ ] Ending move sequence!\nMOVES: %d | POINTS: %d | SUCCESS: %d\n", board.turn, board.score, 1);
                    goto end_program;
                }
                board.turn++;
            }
        }   
    }
    end_program:;
}