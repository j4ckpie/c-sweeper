#ifndef IO_H
#define IO_H

#include "board.h"

void save_scoreboard(char *filename, char *name, int score);

void print_scoreboard(char *filename);

void save_current_score(char *filename, char*name, int score);

void ask_for_nickname(int score);

void print_modes();

void print_logo();

void print_board(Board* b);

int get_number_width(int number);

#endif