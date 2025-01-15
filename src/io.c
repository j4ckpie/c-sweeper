#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "board.h"

#define BUFSIZE 8192
char buf[BUFSIZE];

// Saving scoreboard including current player
void save_scoreboard(char *filename, char *name, int score) {
    FILE *file = fopen(filename, "r");
    Player players[6];
    int lines = 0;

    if(file == NULL) {
        fprintf(stderr, "[!] Error when trying to save scoreboard!\n");
        return;
    }

    // Read current scoreboard
    while(fgets(buf, BUFSIZE, file) != NULL) {
        char temp_name[BUFSIZE];
        int temp_score;
        if(sscanf(buf, "%d %s", &temp_score, temp_name) == 2) {
            players[lines].score = temp_score;
            players[lines].name = strdup(temp_name);
        }
        lines++;
    }

    fclose(file);
    // Add new player if score is high enough and save
    if(players[lines].score < score) {
        players[lines].score = score;
        players[lines].name = name;
        lines++;
        qsort(players, lines, sizeof(Player), comp);
        file = fopen(filename, "w");
        if(file == NULL) {
            fprintf(stderr, "[!] Error when trying to save scoreboard!\n");
            return;
        }
        if(lines > 5) {
            for(int i = 0; i < 5; i++) {
               fprintf(file, "%d %s\n", players[i].score, players[i].name);
            }
        } else {
            for(int i = 0; i < lines; i++) {
                fprintf(file, "%d %s\n", players[i].score, players[i].name);
            }
        }
        printf("[ ] Scoreboard updated successfully!\n");
        fclose(file);
        return;
    } else return;

}

// Print scoreboard
void print_scoreboard(char *filename) {
    FILE *file = fopen(filename, "r");

    if(file == NULL) {
        fprintf(stderr, "[!] Error when trying to print scoreboard!\n");
        return;
    }

    // Read current scoreboard
    printf("SCOREBOARD:\n");
    while(fgets(buf, BUFSIZE, file) != NULL) {
        printf("%s", buf);
    }
    
    fclose(file);
    return;
}

// Save current score
void save_current_score(char *filename, char *name, int score) {
    FILE *file = fopen(filename, "a");

    if(file == NULL) {
        fprintf(stderr, "[!] Error when trying to save current score!\n");
        return;
    }

    fprintf(file, "%d %s\n", score, name);
    save_scoreboard("data/scoreboard.txt", name, score);
    printf("[ ] Current score saved successfully!\n");

    fclose(file);
    return;
}

void ask_for_nickname(int score) {
    char name[256];
    printf("\nEnter your name: ");
    scanf("%s", name);
    save_current_score("data/all_scores.txt", name, score + 1);
}

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

// Funkcja do wypisywania planszy
void print_board(Board* b) {
    printf("TURN: %d\n", b->turn);
    printf("SCORE: %d\n", b->score);
    for (int i = 0; i < b->rows; i++) {
        if(i == 0){
            printf(" ");
            for (int j = 0; j < b->cols; j++) printf("  %d ", j);
            printf("\n");
        }
        for (int j = 0; j < b->cols; j++) {
            if(j == 0) printf("%d ", i);
            if (b->board[i][j].state == CLOSED) {
                printf("[ ] ");
            } else if (b->board[i][j].state == FLAGGED) {
                printf("[F] ");
            } else if (b->board[i][j].is_mine) {
                printf("[*] ");
            } else {
                printf("[%d] ", b->board[i][j].surrounding_mines);
            }
        }
        printf("\n");
    }
}