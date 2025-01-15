#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
    char *name;
    int score;
} Player;

int comp(const void *a, const void *b);

#endif