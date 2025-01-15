#ifndef IO_H
#define IO_H

void save_scoreboard(char *filename, char *name, int score);

void print_scoreboard(char *filename);

void save_current_score(char *filename, char*name, int score);

void ask_for_nickname(int score);

#endif