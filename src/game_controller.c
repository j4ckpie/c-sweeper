#include <stdio.h>
#include <stdlib.h>

#include "io.h"

void print_modes() {
    printf("PLEASE CHOOSE THE GAME MODE:\n1) EASY MODE [9x9, 10 MINES]\n2) MEDIUM MODE [16x16, 40 MINES]\n3) HARD MODE [16x30, 99 MINES]\n4) CUSTOM BOARD\n5) SHOW SCOREBOARD\n");
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

void new_game() {
    int mode;
    int rows;
    int columns;
    int mines;

    print_logo();
    printf("\n");
    print_modes();
    printf("PLAYER'S INPUT: ");

    // Check if input is number
    if(scanf("%d", &mode) != 1) {
        fprintf(stderr, "\n[!] Invalid input! Please enter a coressponding number.\n\n");
        while(getchar() != '\n'); // Clear buffer
        new_game();
    }

    // Check if mode is correct
    if(mode < 1 || mode > 5) {
        fprintf(stderr, "\n[!] Invalid input! Please enter a coressponding number.\n\n");
        new_game();        
    }

    switch(mode) {
        case 1:
            rows = 9;
            columns = 9;
            mines = 10;
            break;
        case 2:
            rows = 16;
            columns = 16;
            mines = 40;
            break;
        case 3:
            rows = 16;
            columns = 30;
            mines = 99;
            break;
        case 4:
            break;
        case 5:
            printf("\n");
            print_scoreboard("data/scoreboard.txt");
            break;
    }
}