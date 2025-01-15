#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "board.h"

void print_modes() {
    printf("PLEASE CHOOSE THE GAME MODE:\n1) EASY MODE [9x9, 10 MINES]\n2) MEDIUM MODE [16x16, 40 MINES]\n3) HARD MODE [16x30, 99 MINES]\n4) CUSTOM BOARD\n5) SHOW SCOREBOARD\n6) QUIT GAME\n");
}

void print_logo() {
    char *logo[5] = {
        "   ___         _____      _____ ___ ___ ___ ___ ",
        "  / __|  ___  / __\\ \\    / / __| __| _ \\ __| _ \\",
        " | (__  |___| \\__ \\\\ \\/\\/ /| _|| _||  _/ _||   /",
        "  \\___|       |___/ \\_/\\_/ |___|___|_| |___|_|_\\",
        "                                                "
    };

    printf("                    WELCOME TO\n");

    for (int i = 0; i < 5; i++) {
        printf("%s\n", logo[i]);
    }

    printf("            MINESWEEPER INSPIRED GAME.\n");
}

void game() {
    int mode;
    int rows;
    int columns;
    int mines;
    int difficulty;
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

        init_board(&board, rows, columns, mines, difficulty);
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
    end_program:;
}