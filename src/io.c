#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"

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